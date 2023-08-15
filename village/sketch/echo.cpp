#include <iostream> /* C++ 标准输入输出头文件 */

/* 程序入口必须命名为 `main` */
int main(int 参数数量, char* 参数小组[]) {
    printf("Received %d arguments:\n", 参数数量);

    /* 显示所有参数，一行一个 */
    for (int i = 0; i < 参数数量; i++) {
        printf("    参数[%d]: %s\n", i, 参数小组[i]);
    }
	
    return 0;
}
