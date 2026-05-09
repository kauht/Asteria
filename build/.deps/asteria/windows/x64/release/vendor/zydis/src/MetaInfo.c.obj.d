{
    files = {
        [[vendor\zydis\src\MetaInfo.c]]
    },
    depfiles_format = "cl_json",
    depfiles = "{\
    \"Version\": \"1.2\",\
    \"Data\": {\
        \"Source\": \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\src\\\\metainfo.c\",\
        \"ProvidedModule\": \"\",\
        \"Includes\": [\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\include\\\\zydis\\\\metainfo.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\include\\\\zydis\\\\defines.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\dependencies\\\\zycore\\\\include\\\\zycore\\\\defines.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\assert.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\corecrt.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\vcruntime.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\sal.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\concurrencysal.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\vadefs.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\include\\\\zydis\\\\generated\\\\enuminstructioncategory.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\include\\\\zydis\\\\generated\\\\enumisaset.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\include\\\\zydis\\\\generated\\\\enumisaext.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\dependencies\\\\zycore\\\\include\\\\zycore\\\\types.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\stdint.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\stddef.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\stdlib.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\corecrt_malloc.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\corecrt_search.h\",\
            \"c:\\\\program files (x86)\\\\windows kits\\\\10\\\\include\\\\10.0.26100.0\\\\ucrt\\\\corecrt_wstdlib.h\",\
            \"c:\\\\program files\\\\microsoft visual studio\\\\18\\\\community\\\\vc\\\\tools\\\\msvc\\\\14.50.35717\\\\include\\\\limits.h\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\src\\\\generated\\\\enuminstructioncategory.inc\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\src\\\\generated\\\\enumisaset.inc\",\
            \"c:\\\\users\\\\macin\\\\desktop\\\\asteria\\\\vendor\\\\zydis\\\\src\\\\generated\\\\enumisaext.inc\"\
        ]\
    }\
}",
    values = {
        [[C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.35717\bin\HostX64\x64\cl.exe]],
        {
            "-nologo",
            "-MD",
            "-O2",
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