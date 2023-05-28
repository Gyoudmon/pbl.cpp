#pragma once // 确保只被 include 一次

#include "../big_bang/bang.hpp"

#include "conway/lifelet.hpp"

#include <map>

namespace WarGrey::STEM {
    enum class GameState { Auto, Stop, Edit, _ };

    /** 声明游戏宇宙 **/
    class GameOfLifeWorld : public WarGrey::STEM::TheBigBang {
    public:
        GameOfLifeWorld(float gridsize = 8.0F) : GameOfLifeWorld("", gridsize) {}
        GameOfLifeWorld(const std::string& life_demo, float gridsize = 8.0F)
            : TheBigBang("生命游戏"), demo_path(life_demo), gridsize(gridsize) {}
        virtual ~GameOfLifeWorld() {}

    public:    // 覆盖游戏基本方法
        void load(float width, float height) override;
        void reflow(float width, float height) override;
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;
        void on_mission_start(float width, float height) override;

    public:
        bool can_select(WarGrey::STEM::IMatter* m) override;
            
    protected: // 覆盖输入事件处理方法
        void on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) override; // 处理键盘事件
        void on_tap(WarGrey::STEM::IMatter* m, float x, float y) override;                  // 处理鼠标事件

    protected: // 处理保存事件
        const char* usrdata_extension() override { return ".gol"; }
        void on_save(const std::string& life_world, std::ofstream& golout) override;

    private:
        void switch_game_state(WarGrey::STEM::GameState new_state);
        void update_instructions_state(const uint32_t* colors);
        void pace_forward(int repeats = 1);
        void load_conway_demo();
        void save_conway_demo();
            
    private: // 游戏物体
        WarGrey::STEM::GameOfLifelet* gameboard;
        WarGrey::STEM::Labellet* generation;
        std::map<char, WarGrey::STEM::Labellet*> instructions;

    private: // 游戏状态
        WarGrey::STEM::GameState state = GameState::_;

    private:
        std::string demo_path;
        float gridsize;
    };
}
