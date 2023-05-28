#include <iostream> /* C++ 标准输入输出头文件 */

/*************************************************************************************************/
int main(int argc, char* argv[]) {
    int coding_age = 2; /* 在定义 int 型变量的同时将变量赋值为 2 */

    std::cout << "假如你已经学了" << coding_age << "年编程。" << std::endl;

    /* 注意：跟在数学中的意义不同，"=" 在程序语言中一般表示"赋值"，而不是"两边相等" */
    coding_age = coding_age + 3; /* coding_age 自增三年 */
    std::cout << "那么再过三年，你就已经学了" << coding_age << "年编程啦！" << std::endl;

    return 0;
}


