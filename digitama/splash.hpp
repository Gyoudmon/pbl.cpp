#include <plteen/game.hpp>

namespace JrLab {
    class TheSplashCosmos : public Plteen::Cosmos {
    public:
        TheSplashCosmos(int fps) : Plteen::Cosmos(fps) {}
        virtual ~TheSplashCosmos();

    public:  // 覆盖游戏基本方法
        void construct(int argc, char* argv[]) override;
        bool can_exit() override;

    protected:
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;

    protected:
        virtual void parse_cmdline_options(int argc, char* argv[]) {}

    private:
        Plteen::IPlane* splash;
    };
}
