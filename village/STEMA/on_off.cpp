#include <iostream>

/*************************************************************/
bool is_light_on_remainder(int m) {
    return (m % 2 == 1);
}

bool is_light_on_simulation(int m) {
    if (m <= 0) {
        return false;
    } else {
        return !is_light_on_simulation(m - 1);
    }
}

void print_status(bool is_on) {
    if (is_on) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }
}

/*************************************************************/
int main(int argc, char* argv[]) {
    int m;
    bool is_on;

    std::cin >> m;
    is_on = is_light_on_remainder(m);
    print_status(is_on);
    
    return 0;
}
