#include <iostream> /* C++ 标准输入输出头文件 */

static void display_the_truth_table(bool a, bool b) {
    std::cout << a << "\t\t" << b << "\t\t";
    std::cout << !a << "\t\t" << (!b) << "\t\t";
    std::cout << (a&&b) << "\t\t" << (a||b) << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << std::boolalpha; // 不要将布尔值转化为数字
    std::cout << "a\t\tb\t\t!a\t\t!b\t\ta&&b\t\ta||b" << std::endl;

    display_the_truth_table(false, false);
    display_the_truth_table(false, true);
    display_the_truth_table(true, false);
    display_the_truth_table(true, true);

    return 0;
}
