#include "digitama/splash.hpp"               // 导入欢迎界面
#include "digitama/gallery.hpp"

#include "digitama/basis/shape.hpp"          // 导入任务世界，几何图形
#include "digitama/basis/paddleball.hpp"     // 导入任务世界，托球游戏

#include "digitama/basis/color_mixture.hpp"
#include "digitama/basis/color_wheel.hpp"
#include "digitama/basis/chromaticity.hpp"
#include "digitama/basis/drunkard.hpp"

#include "digitama/basis/self_avoiding_walk.hpp"
#include "digitama/basis/game_of_life.hpp"
#include "digitama/basis/evolution.hpp"

// Additional Demos
#include "digitama/pltmos/stream.hpp"

using namespace WarGrey::STEM;
using namespace WarGrey::PLT;

/*************************************************************************************************/
namespace {
    enum class CmdlineOps { GameOfLifeDemo, StreamFile, _ };

    /* 定义本地宇宙类，并命名为 BigBangCosmos，继承自 TheCosmos 类 */
    class BigBangCosmos : public TheCosmos {
    public:
        BigBangCosmos(int fps = 60) : TheCosmos(fps) {}
        virtual ~BigBangCosmos() {}

    public:
        // 定义和实现 BigBangCosmos::construct 函数，执行初始化，加载任务世界    
        void construct(int argc, char* argv[]) override {
            TheCosmos::construct(argc, argv);
            this->set_window_size(1200, 0);
            
            // 按顺序加载各个任务世界
            // 第一阶段
            this->push_plane(new ShapeWorld());
            this->push_plane(new PaddleBallWorld());
            this->push_plane(new Gallery());

            // 第二阶段
            this->push_plane(new ColorMixtureWorld());
            this->push_plane(new ColorWheelWorld());
            this->push_plane(new TheBigBang());
            this->push_plane(new DrunkardWalkWorld());
            this->push_plane(new ChromaticityDiagramWorld());
            
            // 第三阶段
            this->push_plane(new SelfAvoidingWalkWorld());
            this->push_plane(new GameOfLifeWorld(this->life_source));
            this->push_plane(new EvolutionWorld());
            this->push_plane(new StreamPlane(this->stream_source.c_str()));
        }

    protected:
        void parse_cmdline_options(int argc, char* argv[]) override {
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

    private:
        std::string life_source;
        std::string stream_source;
    };
}

/*************************************************************************************************/
int main(int argc, char* args[]) {
    /* 混沌初开，宇宙诞生 */
    BigBangCosmos universe;

    /* 创造游戏世界 */
    universe.construct(argc, args);

    /**
     * 宇宙大爆炸
     * 开启游戏主循环，直到玩家关闭游戏
     **/
    universe.big_bang();

    /**
     * C++ 心满意足地退出
     * 顺便销毁游戏宇宙，回归虚无
     **/
    return 0;
}
