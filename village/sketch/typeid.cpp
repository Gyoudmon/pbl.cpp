#include <iostream> /* C++ 标准输入输出头文件 */
#include <typeinfo> /* C++ 运行时类型信息头文件 */

/**************************************************************************************************/
int main(int argc, char* argv[]) {
    std::string name; /* 字符串变量，姓名 */
    int coding_age;   /* 整数变量，已经学了多长时间编程 */

    /*（注意，在 Windows 系统里，现在还不能输入输出中文名字) */
    std::cout << "请告诉我你的英文名字：";
    std::cin >> name;

    std::cout << "你好，" << name << "(" << typeid(name).name() << ")。你学编程几年啦？";
    std::cin >> coding_age;
    std::cout << "好棒，已经 " << coding_age << "(" << typeid(coding_age).name() << ")" << " 年了呀。";
    std::cout << "那么请继续精益求精！" << std::endl;

    return 0;
}


