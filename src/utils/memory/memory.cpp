#include "memory.hpp"
#include <windows.h>
#include <vector>
#include <sstream>
#include <iomanip>

uintptr_t memory::FindPattern(const std::string_view& pattern, const uintptr_t module_base) {
    if (!module_base) return 0;

    auto* base = reinterpret_cast<std::uint8_t*>(module_base);

    const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) return 0;

    const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(dos_header) + dos_header->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE) return 0;

    const size_t size = nt_headers->OptionalHeader.SizeOfImage;

    std::vector<int> bytes;
    {
        std::stringstream ss;
        ss << pattern;
        std::string word;
        while (ss >> word) {
            if (word == "?" || word == "??") {
                bytes.push_back(-1);
            } else {
                try {
                    bytes.push_back(static_cast<int>(std::stoul(word, nullptr, 16)));
                } catch (...) {
                    continue;
                }
            }
        }
    }

    if (bytes.empty()) return 0;

    const size_t pattern_size = bytes.size();
    const int* pattern_data = bytes.data();

    for (size_t i = 0; i <= size - pattern_size; ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern_size; ++j) {
            if (pattern_data[j] != -1 && base[i + j] != static_cast<uint8_t>(pattern_data[j])) {
                found = false;
                break;
            }
        }
        if (found) {
            return reinterpret_cast<uintptr_t>(base + i);
        }
    }
    return 0;
}
