#include "desktop_capture.hpp"

namespace rendering
{
    bool DesktopCapture::init(ID3D11Device* device, HWND hwnd, int width, int height)
    {
        m_device = device;
        m_hwnd = hwnd;
        m_width = width;
        m_height = height;
        
        device->GetImmediateContext(&m_context);
        
        // Create texture for captured desktop
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        
        if (FAILED(device->CreateTexture2D(&desc, nullptr, &m_capture_texture)))
            return false;
        
        if (FAILED(device->CreateShaderResourceView(m_capture_texture, nullptr, &m_capture_srv)))
            return false;
        
        // Create GDI resources for screen capture
        m_screen_dc = GetDC(nullptr);
        m_mem_dc = CreateCompatibleDC(m_screen_dc);
        m_bitmap = CreateCompatibleBitmap(m_screen_dc, width, height);
        m_old_bitmap = (HBITMAP)SelectObject(m_mem_dc, m_bitmap);
        
        return true;
    }
    
    void DesktopCapture::cleanup()
    {
        if (m_old_bitmap) SelectObject(m_mem_dc, m_old_bitmap);
        if (m_bitmap) DeleteObject(m_bitmap);
        if (m_mem_dc) DeleteDC(m_mem_dc);
        if (m_screen_dc) ReleaseDC(nullptr, m_screen_dc);
        
        if (m_capture_srv) { m_capture_srv->Release(); m_capture_srv = nullptr; }
        if (m_capture_texture) { m_capture_texture->Release(); m_capture_texture = nullptr; }
        if (m_context) { m_context->Release(); m_context = nullptr; }
    }
    
    ID3D11ShaderResourceView* DesktopCapture::capture()
    {
        // Get window position
        RECT window_rect;
        GetWindowRect(m_hwnd, &window_rect);
        
        // Capture the screen area behind the window
        BitBlt(m_mem_dc, 0, 0, m_width, m_height,
               m_screen_dc, window_rect.left, window_rect.top, SRCCOPY);
        
        // Copy bitmap data to D3D11 texture
        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = m_width;
        bmi.bmiHeader.biHeight = -m_height;  // Top-down
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        
        // Allocate temporary buffer for GetDIBits
        unsigned char* temp_buffer = new unsigned char[m_width * m_height * 4];
        GetDIBits(m_mem_dc, m_bitmap, 0, m_height, temp_buffer, &bmi, DIB_RGB_COLORS);
        
        // Map texture and copy row by row to handle pitch correctly
        D3D11_MAPPED_SUBRESOURCE mapped;
        if (SUCCEEDED(m_context->Map(m_capture_texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
        {
            unsigned char* dest = (unsigned char*)mapped.pData;
            unsigned char* src = temp_buffer;
            
            for (int y = 0; y < m_height; y++)
            {
                memcpy(dest + y * mapped.RowPitch, src + y * m_width * 4, m_width * 4);
            }
            
            m_context->Unmap(m_capture_texture, 0);
        }
        
        delete[] temp_buffer;
        
        return m_capture_srv;
    }
}
