#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace rendering
{
    bool load_texture_from_file(
        const char* filename,
        ID3D11Device* device,
        ID3D11ShaderResourceView** out_srv,
        int* out_width,
        int* out_height)
    {
        // Load image using stb_image
        int width, height, channels;
        unsigned char* image_data = stbi_load(filename, &width, &height, &channels, 4); // Force RGBA
        
        if (!image_data)
            return false;
        
        // Create texture
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        
        D3D11_SUBRESOURCE_DATA subresource = {};
        subresource.pSysMem = image_data;
        subresource.SysMemPitch = width * 4;
        
        ID3D11Texture2D* texture = nullptr;
        HRESULT hr = device->CreateTexture2D(&desc, &subresource, &texture);
        
        if (FAILED(hr))
        {
            stbi_image_free(image_data);
            return false;
        }
        
        // Create shader resource view
        D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
        srv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srv_desc.Texture2D.MipLevels = 1;
        
        hr = device->CreateShaderResourceView(texture, &srv_desc, out_srv);
        texture->Release();
        
        if (FAILED(hr))
        {
            stbi_image_free(image_data);
            return false;
        }
        
        *out_width = width;
        *out_height = height;
        
        stbi_image_free(image_data);
        return true;
    }
}
