#pragma once // 确保只被 include 一次

#include "../big_bang/game.hpp"

#include "digitama/plt.hpp"

#include <fstream>
#include <deque>

namespace WarGrey::PLT {
    /******************************************* 声明游戏物体 ******************************************/
    class StreamSprite : public WarGrey::STEM::Sprite {
    public:
        StreamSprite(const char* action, float width = 0.0F, float ratio = 3.0F);

    public:
        void construct(SDL_Renderer* renderer) override;

    public:
        void close();
        void open();
        void flow();
        void pause();

    private:
        std::string action;
        float width;
        float ratio;
    };
    
    /******************************************* 声明游戏世界 ******************************************/
    class StreamPlane : public WarGrey::PLT::ThePLTPlane {
    public:
        StreamPlane(const char* spath = "");
        virtual ~StreamPlane() {}

    public:  // 覆盖游戏基本方法
        void load(float width, float height) override;
        void reflow(float width, float height) override;
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;

    public:
        bool can_select(WarGrey::STEM::IMatter* m) override;
        void after_select(WarGrey::STEM::IMatter* m, bool yes) override;

    public:
        bool update_tooltip(WarGrey::STEM::IMatter* m, float x, float y, float gx, float gy) override;

    protected:
        void on_mission_start(float width, float height) override;

    private:
        bool update_pipe_status(std::ifstream& in, WarGrey::STEM::MarioVPipe* pipe, WarGrey::STEM::MarioPipeColor closed_color);
        bool update_progress(std::ifstream& in, const char* message);
        void agent_rest();

    private: // 本游戏世界中的物体
        WarGrey::STEM::MarioGroundAtlas* ground;
        WarGrey::STEM::MarioGroundAtlas* underground;
        WarGrey::PLT::StreamSprite* char_port;
        WarGrey::PLT::StreamSprite* line_port;
        WarGrey::PLT::StreamSprite* char_fall;
        WarGrey::PLT::StreamSprite* line_fall;
        WarGrey::STEM::Labellet* char_label;
        WarGrey::STEM::Labellet* line_label;
        WarGrey::STEM::Sprite* char_cloud;
        WarGrey::STEM::Sprite* line_cloud;
        WarGrey::STEM::Sprite* char_sign;
        WarGrey::STEM::Sprite* line_sign;
        WarGrey::STEM::Sprite* char_filter;
        WarGrey::STEM::Sprite* line_filter;
        WarGrey::STEM::MarioVPipe* char_pipe;
        WarGrey::STEM::MarioVPipe* line_pipe;
        std::deque<WarGrey::STEM::Labellet*> chars;
        std::deque<WarGrey::STEM::Labellet*> line_chars;
        std::deque<WarGrey::STEM::Labellet*> lines;

    private:
        std::string stream_source;
        float stream_source_size;
        std::string stream_buffer;
        std::ifstream charin;
        std::ifstream linein;
    };
}
