#include <iostream>
#include <map>

/*************************************************************/
std::map<int, int> make_square_dict(int n) {
    std::map<int, int> sd;

    for (int i = 1; i <= n; i++) {
        sd[i] = i * i;
    }

    return sd;
}

std::string to_string(std::map<int, int>& sd, int i) {
    std::string s;

    if (i > 1) {
        s.append(",");
    }

    s.append(std::to_string(i));
    s.append(":");
    s.append(std::to_string(sd[i]));

    return s;
}

void print_square_dict(std::map<int, int>& sd) {
    for (int i = 1; i <= sd.size(); i++) {
        std::cout<< to_string(sd, i);
    }

    std::cout << std::endl;
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::map<int, int> sd;
    int n;

    std::cin >> n;
    sd = make_square_dict(n);
    print_square_dict(sd);

    return 0;
}

