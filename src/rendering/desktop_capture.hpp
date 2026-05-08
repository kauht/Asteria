#pragma once

#include <d3d11.h>
#include <Windows.h>

namespace rendering
{
    class DesktopCapture
    {
    public:
        bool init(ID3D11Device* device, HWND hwnd, int width, int height);
        void cleanup();
        
        // Capture the desktop area behind the window
        ID3D11ShaderResourceView* capture();
        
    private:
        ID3D11Device* m_device = nullptr;
        ID3D11DeviceContext* m_context = nullptr;
        HWND m_hwnd = nullptr;
        
        ID3D11Texture2D* m_capture_texture = nullptr;
        ID3D11ShaderResourceView* m_capture_srv = nullptr;
        
        int m_width = 0;
        int m_height = 0;
        
        HDC m_screen_dc = nullptr;
        HDC m_mem_dc = nullptr;
        HBITMAP m_bitmap = nullptr;
        HBITMAP m_old_bitmap = nullptr;
    };
}
