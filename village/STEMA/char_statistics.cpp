#include <iostream>
#include <map>

/*************************************************************/
std::map<std::string, int> init_stat_dict() {
    return { { "英文字母", 0 }, { "空格", 0 }, { "数字", 0 }, { "其他字符", 0 } };
}

void categorize_char(std::map<std::string, int>& ds, char c) {
    if (isalpha(c)) {
        ds["英文字母"] += 1;
    } else if (isspace(c)) {
        ds["空格"] += 1;
    } else if (isdigit(c)) {
        ds["数字"] += 1;
    } else {
        ds["其他字符"] += 1;
    }
}

void display_stats(std::map<std::string, int>& ds) {
    std::string keys[] = { "英文字母", "空格", "数字", "其他字符" };

    for (int i = 0; i < sizeof(keys) / sizeof(std::string); i++) {
        std::cout << ds[keys[i]] << std::endl;
    }
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::map<std::string, int> ds;
    std::string raw;

    std::getline(std::cin, raw);
    ds = init_stat_dict();
    for (auto c = raw.begin(); c != raw.end(); ++c) {
        categorize_char(ds, (*c));
    }
    display_stats(ds);

    return 0;
}

