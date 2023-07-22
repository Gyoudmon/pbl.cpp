#pragma once // 确保只被 include 一次

#include <gydm_stem/bang.hpp>

namespace WarGrey::STEM {
    class DrunkardWalkWorld : public WarGrey::STEM::TheBigBang {
        public:
            DrunkardWalkWorld() : TheBigBang("醉汉漫步") {}
        
        public:
            void load(float width, float height) override;
            void update(uint64_t count, uint32_t interval, uint64_t uptime) override;
            void reflow(float width, float height) override;

        public:
            void on_mission_start(float width, float height) override;

        public: // 为演示角色边界框，运行游戏里的物体可以被选中
            bool can_select(WarGrey::STEM::IMatter* m) override { return true; }

        private: // 漫步策略
            void random_walk(WarGrey::STEM::Bracer* who);
            void drunkard_walk(WarGrey::STEM::Bracer* who);

        private: // 本游戏世界中的物体
            WarGrey::STEM::Bracer* drunkard;
            WarGrey::STEM::Bracer* partner;
            WarGrey::STEM::Sprite* beach;
            WarGrey::STEM::SpriteGridSheet* tent;
    };
}
