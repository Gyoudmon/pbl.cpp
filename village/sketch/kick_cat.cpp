#include <iostream>

/**
 * C++ 必须从一开始就引入类型，
 * 因此零基础初学者可以从 Racket 或 Python 等动态语言开始。
 * 趁学生对语言还没有形成概念，先借其他语言弄个有正反馈的版本，
 * 再开始繁琐的“编辑-编译-运行”流程。
 * 但类型安全方案要留到学生入门之后再说。
 */

// 定义函数：
void 踢(const char* 猫, const char* 谁, const char* 哪只) {
    // 根据函数签名，还原自然语言描述
    printf("kick the %s with %s's %s foot, %s is annoyed\n", 猫, 谁, 哪只, 猫);
}

// 定义类和方法(用 struct 可默认 public)
struct BadPerson {
    BadPerson(const char* name) : name(name) {}

    /** 坏人会踢人
     * 方法令人不齿：欺软怕硬，欺负弱小
     * 不过，坏人一旦踢了人，大家就都知道坏人是谁了
     */
    void 踢(const char* 弱者, const char* 哪只) {
        // 根据函数签名，还原自然语言描述
        printf("%s kicks the %s with %s foot, %s is annoyed\n", this->name, 弱者, 哪只, 弱者);
    }

    // 坏人应该有个名字，方便通报批评
    const char* name;
};

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    BadPerson Cpp{"C++"}, 老板{"Boss"}, 员工{"Employee"}, 孩子{"Kid"};

    printf("Kick the Cat Effect: %s\n", 参数小组[0]);

    Cpp.踢(老板.name, "right");
    老板.踢(员工.name, "left");
    员工.踢(孩子.name, "left");
    孩子.踢("Cat", "left");

    参数小组[0] = const_cast<char*>("Cat");
    for (int i = 0; i < 参数数量; i ++) {
        BadPerson(参数小组[i]).踢(参数小组[i + 1], "right");
    }
    
    return 0;
}
