#pragma once // 确保只被 include 一次

#include <gydm/bang.hpp>

namespace Linguisteen {
    class DrunkardWalkWorld : public GYDM::TheBigBang {
    public:
        DrunkardWalkWorld() : TheBigBang("醉汉漫步") {}
        
    public:
        void load(float width, float height) override;
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;
        void reflow(float width, float height) override;

    public:
        void on_mission_start(float width, float height) override;

    public: // 为演示角色边界框，运行游戏里的物体可以被选中
        bool can_select(GYDM::IMatter* m) override { return true; }

    private: // 漫步策略
        void random_walk(GYDM::Bracer* who);
        void drunkard_walk(GYDM::Bracer* who);

    private: // 本游戏世界中的物体
        GYDM::Bracer* drunkard;
        GYDM::Bracer* partner;
        GYDM::Sprite* beach;
        GYDM::SpriteGridSheet* tent;
        GYDM::Tracklet* track;
    };
}
