#include <iostream>

/** 场景：邹忌讽齐王纳谏
 * 邹忌修八尺有余，而形貌昳丽。
 * 朝服衣冠，窥镜，谓其妻曰：“我孰与城北徐公美？” 其妻曰：“君美甚，徐公何能及君也？”
 * 城北徐公，齐国之美丽者也。
 * 忌不自信，而复问其妾曰：“吾孰与徐公美？”妾曰：“徐公何能及君也？”
 * 旦曰，客从外来，与坐谈，问之：“吾与徐公孰美？”客曰：“徐公不若君之美也。”
 * 明日，徐公来，孰视之，自以为不如；
 * 窥镜而自视，又弗如远甚。
 * 
 * 暮寝而思之，曰：“吾妻之美我者，私我也；妾之美我者，畏我也；客之美我者，欲有求于我也。”
 */

// 定义类和方法
struct Person {
    Person(const char* name, unsigned char good_looking = 6) {
        this->name = name;
        this->颜值 = good_looking;
    }

    // 人会提关于颜值比较的问题
    void 问(const Person* 回答者, const Person* 比较者) const {
        printf("%s: 吾孰与%s美?\n", this->name, 比较者->name);
        回答者->曰(this, 比较者);
    }
    
    // 人会回答关于颜值比较的问题
    void 曰(const Person* 提问者, const Person* 比较者) const {
        printf("%s: 君美甚，%s何能及君也!\n", this->name, 比较者->name);
    }

    // 人会自省，但多少有点偏心，颜值相同时也会觉得自己更美
    void 自省(const Person* 比较者) const {
        if (this->颜值 < 比较者->颜值) {
            printf("[%s窥镜而自视: 吾诚知不如%s美!]\n", this->name, 比较者->name);
        } else {
            printf("[%s窥镜而自视: 吾诚知%s不若吾之美也!]\n", this->name, 比较者->name);
        }
    }

    const char* name;
    unsigned char 颜值;
};

int main(int 客人数量, char* 客人列表[]) {
    printf("邹忌讽齐王纳谏: %s\n", 客人列表[0]);

    // 角色就绪
    Person 邹忌("邹忌", 8), 徐公("徐公", 10);
    Person 妻("妻"), 妾("妾");

    // 还原情景
    邹忌.问(&妻, &徐公);
    邹忌.问(&妾, &徐公);

    for (int i = 1; i < 客人数量; i++) {
        auto 客 = new Person(客人列表[i]);

        printf("旦日, %s从外来, 与座谈.\n", 客->name);
        邹忌.问(客, &徐公);
        邹忌.自省(客);

        delete 客;
    }

    printf("明日, %s来, 孰视之.\n", 徐公.name);
    邹忌.自省(&徐公);

    return 0;
}
