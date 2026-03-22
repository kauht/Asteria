// #include "practice_hook.hpp"
// #include <print>
// #include <cstdint>
// #include <cstring>
// #include <cstddef>
// #include <algorithm>

// namespace asteria::util {

// void insert_jmp(uint8_t* src, uint8_t* dest, std::size_t size) noexcept {
//     if (!src || !dest || size < 5) return;
//     change_protection(src, size, PROT_READ | PROT_WRITE | PROT_EXEC);
//     src[0] = 0xE9;
//     intptr_t rel = (intptr_t)dest - ((intptr_t)src + 5);
//     std::memcpy(src + 1, &rel, sizeof(rel));
//     if (size > 5) std::memset(src + 5, 0x90, size - 5);
//     change_protection(src, size, PROT_READ | PROT_EXEC);

// }

// bool install_hook(uint8_t* src, uint8_t* dest, std::size_t size, HookRecord& record) noexcept {
//     if (!src || !dest || size < 5) return false;

//     record.src = src;
//     record.size = size;
//     record.installed = false;

//     std::size_t save_len = std::min<std::size_t>(size, sizeof(record.original));
//     std::memcpy(record.original, src, save_len);
//     if (save_len < sizeof(record.original)) {
//         std::memset(record.original + save_len, 0, sizeof(record.original) - save_len);
//     }
//     if (!change_protection(src, size, PROT_READ | PROT_WRITE | PROT_EXEC))
//         return false;

//     src[0] = 0xE9;
//     intptr_t rel = (intptr_t)dest - ((intptr_t)src + 5);
//     std::memcpy(src + 1, &rel, sizeof(rel));
//     if (size > 5) std::memset(src + 5, 0x90, size - 5);
//     change_protection(src, size, PROT_READ | PROT_EXEC);

//     record.installed = true;
//     return true;
// }

// bool restore_jmp(uint8_t* src, const uint8_t* orig, std::size_t size) noexcept {
//     if (!src || !orig || size == 0) return false;
//     if (!change_protection(src, size, PROT_READ | PROT_WRITE | PROT_EXEC)) return false;
//     std::size_t copy_len = std::min<std::size_t>(size, 32);
//     std::memcpy(src, orig, copy_len);
//     if (size > copy_len) std::memset(src + copy_len, 0x90, size - copy_len);
//     change_protection(src, size, PROT_READ | PROT_EXEC);
//     return true;
// }

// bool uninstall_hook(HookRecord& record) noexcept {
//     if (!record.installed || !record.src || record.size == 0) return false;
//     bool ok = restore_jmp(record.src, record.original, record.size);
//     if (ok) record.installed = false;
//     return ok;
// }

// void remove_jmp(uint8_t* src, std::size_t size) noexcept {
//     if (!src || size == 0) return;
//     if (!change_protection(src, size, PROT_READ | PROT_WRITE | PROT_EXEC)) return;
//     std::memset(src, 0x90, size);
//     change_protection(src, size, PROT_READ | PROT_EXEC);
// }

// void restore_all_hooks() noexcept {
// }

// void hook() { std::println("Hooked!"); }
// void cool() { std::println("HOOK ME!"); }

// } // namespace asteria::util
