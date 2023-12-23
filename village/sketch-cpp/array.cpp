#include <iostream> /* C++ 标准输入输出头文件 */

int main(int argc, char* argv[]) {
    // 直接初始化
    int a2d[3][4] = {
        0, 1,  2,  3,
        4, 5,  6,  7,
        8, 9, 10, 11
    };
    
    // 遍历二维数组需要两层 for 循环
    for (int r = 0; r < 3; r++) { 
        for (int c = 0; c < 4; c++) {
            std::cout << a2d[r][c] << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
