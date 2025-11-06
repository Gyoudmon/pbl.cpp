#pragma once

#include "splash.hpp"

/*************************************************************************************************/
namespace JrLab {
    enum class CmdlineOps { GameOfLifeDemo, StreamFile, CarryNumber, _ };

    /* 定义本地宇宙类，并命名为 JrLabCosmos，继承自 TheCosmos 类 */
    class JrLabCosmos : public TheSplashCosmos {
    public:
        JrLabCosmos(int fps = 60) : TheSplashCosmos(fps) {}
        virtual ~JrLabCosmos() {}

    public:
        // 定义 JrLabCosmos::construct 函数，执行初始化，加载任务世界    
        void construct(int argc, char* argv[]) override;

    protected:
        void parse_cmdline_options(int argc, char* argv[]) override;

    private:
        std::string life_source;
        std::string stream_source;
        size_t number = 0;
    };
}
