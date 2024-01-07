#include <iostream> /* C++ 标准输入输出头文件 */

/**
 * 程序入口必须命名为 `main`
 * @param argc, "argument count" 的缩写，即"参数个数"的意思
 * @param argv, "argument vector" 的缩写, 即"参数数组"的意思，包含命令行的所有输入参数
 */
int main(int argc, char* argv[]) {
    std::string name;       /* 字符串变量，单个英文单词 */
    int age;                /* 整数变量，下划线连接两个英文单词 */
    std::string camelCase;  /* 字符串变量, 驼峰命名法 */
    int 5wrong_name;        /* 错误的变量名，数字开头 */

    std::cout<< "你的年龄是" <<age <<"岁。" << std::endl;

    return 0;
}

