#include <iostream> /* C++ 标准输入输出头文件 */

int main(int argc, char* argv[]) {
    // 直接赋值
    bool t = true;
    bool f = false;

    // 数值类型到布尔类型的隐式类型转换
    bool pi = 3.14;
    bool zero = 0.0;

    std::cout << std::boolalpha; // 不要将布尔值转化为数字
    std::cout << "变量 t 的值是" << t << std::endl;
    std::cout << "变量 f 的值是" << f << std::endl;
    std::cout << "变量 pi 的值是" << pi << std::endl;
    std::cout << "变量 zero 的值是" << zero << std::endl;

    return 0;
}
