#include <iostream> /* C++ 标准输入输出头文件 */

/**
 * 程序入口必须命名为 `main`
 * @param argc, "argument count" 的缩写，即"参数个数"的意思
 * @param argv, "argument vector" 的缩写, 即"参数数组"的意思，包含命令行的所有输入参数
 */
int main(int argc, char* argv[]) {
    /* 注意: 第一个参数一定是程序的名字(可执行文件的名字，可用 g++ 的 -o 参数指定) */
    std::cout << "正在运行: " << argv[0] << std::endl;
    std::cout << "    接收到了" << (argc - 1) << "个来自用户的输入: " << std::endl;

    /* 显示所有的用户输入参数，一行一个 */
    for (int i = 1; i < argc; i++) {
        std::cout<<"    argv["<< i <<"]: "<<argv[i]<<std::endl;
    }
	
    return 0;
}

