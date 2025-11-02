// 导入语言基础课的大爆炸宇宙(BigBangCosmos)
#include "digitama/basis.hpp"

using namespace JrLab;

int main(int argc, char* args[]) {
    /* 混沌初开，宇宙诞生 */
    BasisCosmos universe;

    /* 创造游戏世界 */
    universe.construct(argc, args);

    /**
     * 宇宙大爆炸
     * 开启游戏主循环，直到玩家关闭游戏
     **/
    universe.big_bang();

    /**
     * C++ 心满意足地退出
     * 操作系统随后销毁游戏宇宙，回归虚无
     **/
    return 0;
}
