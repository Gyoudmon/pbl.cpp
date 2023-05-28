#pragma once // 确保只被 include 一次

#include "../big_bang/bang.hpp"

namespace WarGrey::STEM {
#define MAZE_SIZE 15    // 方格单边数量

    class SelfAvoidingWalkWorld : public WarGrey::STEM::TheBigBang {
        public:
            SelfAvoidingWalkWorld() : TheBigBang("自回避游走") {}
        
        public:
            void load(float width, float height) override;
            void reflow(float width, float height) override;
            void update(uint64_t count, uint32_t interval, uint64_t uptime) override;
            void on_mission_start(float width, float height) override;

        public:
            bool can_select(WarGrey::STEM::IMatter* m) override;

        protected:
            void after_select(WarGrey::STEM::IMatter* m, bool yes) override;
            bool update_tooltip(WarGrey::STEM::IMatter* m, float lx, float ly, float gx, float gy) override;

        private:
            void reset_walkers(bool keep_mode);
            void reset_maze();
            
        private:
            WarGrey::STEM::PlanetCuteTile* tiles[MAZE_SIZE][MAZE_SIZE];
            WarGrey::STEM::Bracer* walkers[8];

        private:
            bool maze[MAZE_SIZE][MAZE_SIZE];
            float cell_width = 0.0F;
            float cell_height = 0.0F;

        private:
            WarGrey::STEM::Bracer* walker = nullptr;
            int row = -1;
            int col = 0;
    };
}
