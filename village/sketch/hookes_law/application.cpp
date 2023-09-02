#include <iostream>

// 场景：胡克定律

// 定义函数:
double l(double m, double 初始长度, double 限度) {
    if (m <= 限度) {
        return 0.16 * m + 初始长度;
    } else {
        printf("Ahhhhhhh, the spring is broken.\n");
        return 0.0;
    }
}

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    printf("Hooke's Law: %s\n", 参数小组[0]);

    // 最终程序
    int idx = 1;
    
    while (idx < 参数数量) {
        double mass = strtod(参数小组[idx], nullptr);
        double length = l(mass, 5.0, 100.0);

        printf("mass = %lfg, length = %lfcm\n", mass, length);

        idx = idx + 1;
    }

    return 0;
}
