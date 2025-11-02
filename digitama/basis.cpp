#include "basis.hpp"

// 导入一个个任务世界
#include "basis/shape.hpp"                // 几何图形
#include "basis/paddleball.hpp"           // 托球游戏
#include "basis/angry_bird.hpp"           // 愤怒小鸟

#include "basis/color_mixture.hpp"        // 混色模型
#include "basis/color_wheel.hpp"          // 色相环
#include "basis/drunkard.hpp"             // 醉汉漫步

#include "basis/self_avoiding_walk.hpp"   // 自回避随机游走
#include "basis/game_of_life.hpp"         // 生命游戏
#include "basis/evolution.hpp"            // 演化游戏

// 导入教师演示程序
#include <pltmos/stream.hpp>
#include <pltmos/carry.hpp>
#include <stemos/schematics/optics/chromaticity.hpp>

using namespace Plteen;
using namespace JrLab;

using namespace WarGrey::STEM;
using namespace WarGrey::PLT;

/*************************************************************************************************/
// 定义和实现 BasisCosmos::construct 函数，构造本地宇宙，执行初始化，加载任务世界    
void JrLab::BasisCosmos::construct(int argc, char* argv[]) {
    TheCosmos::construct(argc, argv);
    this->set_window_size(1200, 0);
            
    // 按顺序加载各个任务世界
    // 第一阶段
    this->spawn<ShapeWorld>();
    this->spawn<PaddleBallWorld>();
    this->spawn<TheBigBang>();

    // 第二阶段
    this->spawn<DotAndCarryOnePlane>(this->number);
    this->spawn<ColorMixtureWorld>();
    this->spawn<ColorWheelWorld>();
    this->spawn<TheBigBang>();
    this->spawn<DrunkardWalkWorld>();
    this->spawn<ChromaticityDiagramPlane>();
            
    // 第三阶段
    this->spawn<SelfAvoidingWalkWorld>();
    this->spawn<GameOfLifeWorld>(this->life_source);

#ifdef __windows__
    this->spawn<TheBigBang>();
#else
    this->spawn<EvolutionWorld>();
#endif

    this->spawn<StreamPlane>(this->stream_source.c_str());
}

void JrLab::BasisCosmos::parse_cmdline_options(int argc, char* argv[]) {
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
        case CmdlineOps::CarryNumber: {
            this->number = std::strtoull(argv[idx], nullptr, 10);
            opt = CmdlineOps::_;
        }; break;
        default: {
            if (strncmp("--life", argv[idx], 7) == 0) {
                opt = CmdlineOps::GameOfLifeDemo;
            } else if (strncmp("--pipe", argv[idx], 7) == 0) {
                opt = CmdlineOps::StreamFile;
            } else if (strncmp("--carry", argv[idx], 8) == 0) {
                opt = CmdlineOps::CarryNumber;
            }
        }
        }
    }
}
