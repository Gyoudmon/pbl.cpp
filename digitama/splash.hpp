#include <gydm_stem/game.hpp>

namespace WarGrey::STEM {
    class TheCosmos : public WarGrey::STEM::Cosmos {
    public:
        TheCosmos(int fps) : WarGrey::STEM::Cosmos(fps) {}
        virtual ~TheCosmos();

    public:  // 覆盖游戏基本方法
        void construct(int argc, char* argv[]) override;
        bool can_exit() override;

    protected:
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;

    protected:
        void on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) override;
        void on_unhandled_event(uint32_t type, SDL_Event& self) override;

    protected:
        virtual void parse_cmdline_options(int argc, char* argv[]) {}

    private:
        WarGrey::STEM::IPlane* splash;
    };
}
