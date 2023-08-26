#include <iostream>

// 场景：胡克定律

// 实验得出关系表达式：Δl = 2m

// 定义函数：
float l(float m, float 初始长度, float 限度) {
    if (m <= 限度) {
        return 0.16 * m + 初始长度;
    } else {
        printf("Ahhhhhhh, the spring is broken.\n");
        return 0;
    }
}

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    printf("Hooke's Law: %s\n", 参数小组[0]);

    printf("%f\n", l(20.0F, 5.0F, 100.0F));
    printf("%f\n", l(128.0F, 5.0F, 100.0F));

    return 0;
}
