#include <iostream>

typedef const char* cstring;

// 定义函数：
void 踢(cstring 猫, cstring 谁, cstring 哪只) {
    // 根据函数签名，还原自然语言描述
    // kick the cat with one's this foot
    printf("踢%s, 用%s的%s脚, %s很气愤\n", 猫, 谁, 哪只, 猫);
}

// 门槛不算高，但是极其折磨人
int main(int argc, char* argv[]) {
    踢("员工", "老板", "右");
    踢("小孩", "员工", "右");
    踢("猫", "小孩", "左");
    
    return 0;
}
