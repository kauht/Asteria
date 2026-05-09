{
    files = {
        [[vendor\safetyhook\src\os.linux.cpp]]
    },
    depfiles_format = "cl_json",
    depfiles = "{\
    \"Version\": \"1.2\",\
    \"Data\": {\
        \"Source\": \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\safetyhook\\\\src\\\\os.linux.cpp\",\
        \"ProvidedModule\": \"\",\
        \"Includes\": [\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\safetyhook\\\\include\\\\safetyhook\\\\common.hpp\"\
        ],\
        \"ImportedModules\": [],\
        \"ImportedHeaderUnits\": []\
    }\
}",
    values = {
        [[C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.35717\bin\HostX64\x64\cl.exe]],
        {
            "-nologo",
            "-MD",
            "-O2",
            "-std:c++23preview",
            [[-Ivendor\minhook\include]],
            [[-Ivendor\imgui]],
            [[-Ivendor\imgui\backends]],
            [[-Ivendor\safetyhook\include]],
            [[-Ivendor\safetyhook\src]],
            [[-Ivendor\zydis\src]],
            [[-Ivendor\zydis]],
            [[-Ivendor\zydis\include]],
            [[-Ivendor\zydis\dependencies\zycore\include]],
            "-DZYDIS_STATIC_BUILD",
            "-DZYCORE_STATIC_BUILD",
            "/EHsc",
            "-DNDEBUG"
        }
    }
}