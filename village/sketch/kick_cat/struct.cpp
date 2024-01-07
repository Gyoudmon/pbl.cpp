#include <iostream>

typedef const char* cstring;

// 用 struct 关键字定义【类】, 角色
struct BadPerson {
    cstring name; // 坏人应该有个名字，方便通报批评

    // 构造函数：名字(参数列表) { }
    // 实例化 的本质，调用类的构造函数
    BadPerson(cstring name) {
        // “我”的名字是 Boss
        this->name = name; // 赋值
        printf("%s is ready\n", name);
    }

    /** 坏人会踢人，【方法】令人不齿：欺软怕硬，欺负弱小
     * 不过，坏人一旦踢了人，大家就都知道坏人是谁了
     */
    // 函数：返回值类型 名字(参数列表) { }
    // 参数：参数类型 参数名字
    void kick(cstring 弱者, cstring 哪只) {
        // 根据方法签名，还原自然语言描述
        printf("%s kicks the %s with %s foot, %s is annoyed\n", this->name, 弱者, 哪只, 弱者);
    }
};

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    /* 注意区分这两种实例化方式 */
    // 实例化：找个人来扮演角色
    BadPerson 老板 = BadPerson("Boss");
    BadPerson* 员工 = new BadPerson("Employee");
    BadPerson* 孩子 = new BadPerson("Kid");

    /* 注意区分不同方式实例化的对象在调用方法时的不同 */
    老板.kick(员工->name, "left");
    员工->kick(孩子->name, "left");
    孩子->kick("Cat", "left");

    /* new 出来的对象需要 delete 掉 */
    delete 员工, 孩子;
    
    return 0;
}
