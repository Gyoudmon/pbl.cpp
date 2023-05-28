#include <iostream>
#include <vector>

/*************************************************************/
std::vector<int> make_josephus_circle(int n) {
    std::vector<int> ls;

    for (int i = 1; i <= n; i++) {
        ls.push_back(i);
    }

    return ls;
}

bool can_finish(std::vector<int>& ls) {
    return ls.size() <= 1;
}

int count_off(std::vector<int>& ls, int idx) {
    return (idx + 3 - 1) % ls.size();
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::vector<int> ls;
    int idx = 0;
    int n = 0;

    std::cin >> n;
    ls = make_josephus_circle(n);

    while (!can_finish(ls)) {
        idx = count_off(ls, idx);
        ls.erase(ls.begin() + idx);
    }

    if (ls.size() > 0) {
        std::cout << ls[0] << std::endl;
    }

    return 0;
}

