#include "cosmos.hpp"

// 倒入一个个任务世界
#include "shape.hpp"                // 几何图形
#include "paddleball.hpp"           // 托球游戏

#include "color_mixture.hpp"        // 混色模型
#include "color_wheel.hpp"          // 色相环
#include "drunkard.hpp"             // 醉汉漫步

#include "self_avoiding_walk.hpp"   // 自回避随机游走
#include "game_of_life.hpp"         // 生命游戏
#include "evolution.hpp"            // 演化游戏

// 倒入教师演示程序
#include <pltmos/stream.hpp>
#include <scsmos/schematics/optics/chromaticity.hpp>

using namespace WarGrey::STEM;
using namespace WarGrey::PLT;
using namespace WarGrey::SCSM;

/*************************************************************************************************/
// 定义和实现 BigBangCosmos::construct 函数，构造本地宇宙，执行初始化，加载任务世界    
void WarGrey::STEM::BigBangCosmos::construct(int argc, char* argv[]) {
    TheCosmos::construct(argc, argv);
    this->set_window_size(1200, 0);
            
    // 按顺序加载各个任务世界
    // 第一阶段
    this->push_plane(new ShapeWorld());
    this->push_plane(new PaddleBallWorld());
    this->push_plane(new TheBigBang());

    // 第二阶段
    this->push_plane(new ColorMixtureWorld());
    this->push_plane(new ColorWheelWorld());
    this->push_plane(new TheBigBang());
    this->push_plane(new DrunkardWalkWorld());
    this->push_plane(new ChromaticityDiagramPlane());
            
    // 第三阶段
    this->push_plane(new SelfAvoidingWalkWorld());
    this->push_plane(new GameOfLifeWorld(this->life_source));
    this->push_plane(new TheBigBang());
    this->push_plane(new StreamPlane(this->stream_source.c_str()));
}

void WarGrey::STEM::BigBangCosmos::parse_cmdline_options(int argc, char* argv[]) {
    CmdlineOps opt = CmdlineOps::_;
            
    for (int idx = 1; idx < argc; idx ++) {
        switch (opt) {
        case CmdlineOps::GameOfLifeDemo: {
            this->life_source = argv[idx];
            opt = CmdlineOps::_;
        }; break;
        case CmdlineOps::StreamFile: {
            this->stream_source = argv[idx];
            opt = CmdlineOps::_;
        }; break;
        default: {
            if (strncmp("--life", argv[idx], 7) == 0) {
                opt = CmdlineOps::GameOfLifeDemo;
            } else if (strncmp("--pipe", argv[idx], 7) == 0) {
                opt = CmdlineOps::StreamFile;
            }
        }
        }
    }
}
