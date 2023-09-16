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
    // kick the cat with one's this foot
    printf("踢%s, 用%s的%s脚, %s很气愤\n", 猫, 谁, 哪只, 猫);
}

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    printf("Kick the Cat Effect: %s\n", 参数小组[0]);

    int idx = 0;

    参数小组[0] = const_cast<char*>("Cat");
    while (idx < 参数数量) {
        踢(参数小组[idx + 1], 参数小组[idx], "右");
        idx = idx + 1;
    }

    /* 体验类型的威力 */
    // 踢(12, "我", 3.0);
    
    return 0;
}
