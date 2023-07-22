#include <iostream> /* C++ 标准输入输出头文件 */

/**
 * 程序入口必须命名为 `main`
 * @param argc, "argument count" 的缩写，即"参数个数"的意思
 * @param argv, "argument vector" 的缩写, 即"参数数组"的意思
 */
int main(int argc, char* argv[]) {
    /* 注意: 第一个参数一定是正在运行的程序的路径 */
    std::cout << "Running: " << argv[0] << std::endl;
    std::cout << "  Received " << (argc - 1);
    std::cout << " arguments from user: " << std::endl;

    /* 显示所有的用户输入参数，一行一个 */
    for (int i = 1; i < argc; i++) {
        printf("    argv[%d]: %s\n", i, argv[i]);
    }
	
    return 0;
}
