#include <iostream> /* C++ 标准输入输出头文件 */

/**************************************************************************************************/
enum class WeekDay {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

static const char* weekday_name(WeekDay day) {
    switch (day) {
        case WeekDay::Sunday: return "Sunday"; break;
        case WeekDay::Monday: return "Monday"; break;
        case WeekDay::Tuesday: return "Tuesday"; break;
        case WeekDay::Wednesday: return "Wednesday"; break;
        case WeekDay::Thursday: return "Thursday"; break;
        case WeekDay::Friday: return "Friday"; break;
        case WeekDay::Saturday: return "Saturday"; break;
        default: return "[Error]"; break;
    }
}

/**************************************************************************************************/
int main(int argc, char* argv[]) {
    WeekDay day = WeekDay::Tuesday;

    if (argc > 1) {
        day = static_cast<WeekDay>(std::stoi(argv[1]));
    }
    
    std::cout << "今天是 " << weekday_name(day) << "，";
    std::cout << "它的整型值是" << static_cast<int>(day) << std::endl;
    
    return 0;
}
