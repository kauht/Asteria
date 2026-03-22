// #pragma once

// #include <cstdint>
// #include <cstddef>
// #include <unistd.h>
// #include <sys/mman.h>

// namespace asteria::util {

//     inline bool change_protection(void* addr, std::size_t len, int prot) noexcept {
//         const std::size_t PAGE = sysconf(_SC_PAGESIZE);

//         // align 'addr_i' down to the start of its page
//         const std::uintptr_t page_start = reinterpret_cast<std::uintptr_t>(addr) & ~(PAGE - 1);

//         // compute end address and round up to the next page boundary
//         const std::uintptr_t end_i = reinterpret_cast<std::uintptr_t>(addr) + len;
//         const std::size_t full_len = ((end_i + PAGE - 1) & ~(PAGE - 1)) - page_start;

//         // call mprotect on the page-aligned region
//         return mprotect((void*)page_start, full_len, prot) == 0;
//     }


//     void insert_jmp(uint8_t* src, uint8_t* dest, std::size_t size) noexcept;

//     // Hook record: stores original bytes and metadata so hooks can be uninstalled cleanly.
//     // - `original` holds the saved bytes from the target function; size may be adjusted as needed.
//     // - `installed` indicates whether the hook is currently applied.
//     struct HookRecord {
//         uint8_t* src;
//         std::size_t size;
//         uint8_t original[32]; // reserve space for original bytes (up to 32). If larger needed, increase.
//         bool installed;
//     };

//     // High-level install/uninstall API that records original bytes into `record`.
//     // install_hook: saves original bytes and applies JMP hook (returns true on success).
//     // uninstall_hook: restores original bytes and marks record as uninstalled (returns true on success).
//     bool install_hook(uint8_t* src, uint8_t* dest, std::size_t size, HookRecord& record) noexcept;
//     bool uninstall_hook(HookRecord& record) noexcept;

//     // Low-level restore: restore `size` bytes at `src` from `orig` buffer.
//     bool restore_jmp(uint8_t* src, const uint8_t* orig, std::size_t size) noexcept;

//     void hook();
//     void cool();

// } // namespace asteria::util
