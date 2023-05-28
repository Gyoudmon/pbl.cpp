#include <iostream>

/*************************************************************/
int strlen_loop(std::string& s) {
    int size = 0;
    
    for (auto c : s) {
        size ++;
    }

    return size;
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::string src;

    std::getline(std::cin, src);
    int size = strlen_loop(src);
    
    std::cout << size << std::endl;

    return 0;
}
