#pragma once

#include "../splash.hpp"

/*************************************************************************************************/
namespace WarGrey::STEM {
    enum class CmdlineOps { GameOfLifeDemo, StreamFile, _ };

    /* 定义本地宇宙类，并命名为 BigBangCosmos，继承自 TheCosmos 类 */
    class BigBangCosmos : public TheCosmos {
    public:
        BigBangCosmos(int fps = 60) : TheCosmos(fps) {}
        virtual ~BigBangCosmos() {}

    public:
        // 定义 BigBangCosmos::construct 函数，执行初始化，加载任务世界    
        void construct(int argc, char* argv[]) override;

    protected:
        void parse_cmdline_options(int argc, char* argv[]) override;

    private:
        std::string life_source;
        std::string stream_source;
    };
}
