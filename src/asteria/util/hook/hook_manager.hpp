#include <vector>

namespace asteria::util {

    struct HookRecord;

    class hook_manager {
    public:
        void install_all();
        void uninstall_all();

    private:
        hook_manager() = default;
        ~hook_manager() = default;

        std::vector<HookRecord> hooks_;
    };

} // namespace asteria::util
