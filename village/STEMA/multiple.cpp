#include <iostream>

/*************************************************************/
bool is_divisible(int z, int n) {
    return z % n == 0;
}

void print_datum(int z, int i, int M) {
    if (i > 0) {
        std::cout << ",";
    }

    std::cout << z;
}

/*************************************************************/
int main(int argc, char* argv[]) {
    int M, N;
    int i = 0;

    std::cin >> M;
    std::cin >> N;

    for (int c = M; c <= N; c ++) {
        if (is_divisible(c, 7) && !is_divisible(c, 5)) {
            print_datum(c, i, M);
            i += 1;
        }
    }

    std::cout << std::endl;

    return 0;
}

