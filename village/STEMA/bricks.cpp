#include <iostream>
#include <vector>
#include <tuple>

/*************************************************************/
int count_bricks_loop(int n) {
    int 该层砖块数 = 0;
    int 总砖块数 = 0;

    for (int 层数 = 1; 层数 <= n; 层数++) {
        该层砖块数 += 层数;
        总砖块数 += 该层砖块数;
    }

    return 总砖块数;
}

std::vector<int> count_bricks_recursion(int n) {
    if (n <= 0) {
        return { 0, 0 };
    } else {
        std::vector<int> 上层结果 = count_bricks_recursion(n - 1);
        int 该层砖块数 = 上层结果[0] + n;
        int 总砖块数 = 上层结果[1] + 该层砖块数;
        
        return { 该层砖块数, 总砖块数 };
    }
}

std::tuple<int, int> count_bricks_recursion_tuple(int n) {
    if (n <= 0) {
        return { 0, 0 };
    } else {
        std::tuple<int, int> 上层结果 = count_bricks_recursion_tuple(n - 1);
        int 该层砖块数 = std::get<0>(上层结果) + n;
        int 总砖块数 = std::get<1>(上层结果) + 该层砖块数;
        
        return { 该层砖块数, 总砖块数 };
    }
}


/*************************************************************/
int main(int argc, char* argv[]) {
    std::vector<int> vs;
    int n;

    std::cin >> n;
    vs = count_bricks_recursion(n);
    std::cout << vs[1] << std::endl;

    return 0;
}

