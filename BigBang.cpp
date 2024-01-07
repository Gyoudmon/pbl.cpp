#include "digitama/basis/cosmos.hpp"  // 导入语言基础课的 Cosmos

using namespace Linguisteen;

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
