#include <iostream>

typedef const char* cstring;

// 用 class 关键字定义类
class BadPerson {
public:
    // 构造函数
    BadPerson(cstring name) {
        this->name = name;
    }

    // 坏人会踢人
    void 踢(cstring 弱者, cstring 哪只) {
        // 根据函数签名，还原自然语言描述
        printf("%s kicks the %s with %s foot, %s is annoyed\n", this->name, 弱者, 哪只, 弱者);
    }

public:
    // 坏人应该有个名字，方便通报批评
    cstring name;
};

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    int idx = 0;

    printf("Kick the Cat Effect: %s\n", 参数小组[0]);
    
    参数小组[0] = const_cast<char*>("Boss");
    while (idx < 参数数量) {
        BadPerson who(参数小组[idx]);
        
        who.踢(参数小组[idx + 1], "right");
        idx = idx + 1;
    }
    
    return 0;
}
