#include <iostream>

// 场景：胡克定律

// 实验得出关系表达式：Δl = 0.16m
double Δl1(double m) {
    return 0.16 * m;
}

double Δl2(double m) {
    return 0.20 * m;
}

double Δl3(double m) {
    return 0.15 * m;
}

// 门槛不算高，但是极其折磨人
int main(int 参数数量, char* 参数小组[]) {
    printf("Hooke's Law: %s\n", 参数小组[0]);

    // 数学建模阶段    
    printf("delta l1: %lf\n", Δl1(20.0));
    printf("delta l2: %lf\n", Δl2(40.0));
    printf("delta l3: %lf\n", Δl3(80.0));

    return 0;
}
