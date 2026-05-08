#pragma once

#include <d3d11.h>
#include <string>

namespace rendering
{
    // Load a texture from a PNG file
    bool load_texture_from_file(
        const char* filename,
        ID3D11Device* device,
        ID3D11ShaderResourceView** out_srv,
        int* out_width,
        int* out_height
    );
}
