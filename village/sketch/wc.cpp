#include <iostream>
#include <fstream>

/*************************************************************************************************/
void wc_by_line(std::istream& src) {
    std::string line;
    int line_count = 0;

    while (std::getline(src, line)) {
        line_count ++;
    }

    std::cout << line_count;

    if (line_count == 1) {
        std::cout << " line";
    } else {
        std::cout << " lines";
    }

    std::cout << std::endl;
}



/*************************************************************************************************/
int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int idx = 1; idx < argc; idx++) {
            std::ifstream src(argv[idx]);

            if (src.is_open()) {
                wc_by_line(src);
                src.close();
            }
        }
    } else {
        wc_by_line(std::cin);
    }

    return 0;
}
