#include <iostream>
#include <fstream>

/*************************************************************************************************/
void cat_by_line(std::istream& src) {
    std::string line;

    while (std::getline(src, line)) {
        std::cout << line << std::endl;
    }
}

/*************************************************************************************************/
int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::ifstream src(argv[1]);

        if (src.is_open()) {
            cat_by_line(src);
            src.close();
        }
    } else {
        cat_by_line(std::cin);
    }

    return 0;
}
