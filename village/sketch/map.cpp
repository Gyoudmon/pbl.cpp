#include <iostream> /* C++ 标准输入输出头文件 */
#include <map>

/**************************************************************/
class PObject {
public:
    PObject(int v) : value(v) {}
    virtual ~PObject() noexcept {
        printf("destructing `%d`.\n", this->value);
    }

public:
    int value;
};

void print_map(std::map<int, std::map<int, PObject*>>& mp) {
    for (auto subms : mp) {
        printf("%d\n", subms.first);
        
        for (auto ms : subms.second) {
            printf("   %d:%d\n", ms.first, ms.second->value);
        }
    }
}

/**************************************************************/
int main(int argc, char* argv[]) {
    std::map<int, std::map<int, PObject*>> mp;

    mp[1][10] = new PObject(100);
    mp[2][10] = new PObject(210);
    mp[2][20] = new PObject(220);
    mp[3][10] = new PObject(310);
    mp[3][20] = new PObject(320);
    mp[3][30] = new PObject(330);
    mp[4][10] = new PObject(410);
    mp[4][20] = new PObject(420);
    mp[4][30] = new PObject(430);
    mp[4][40] = new PObject(430);
    mp[5][10] = new PObject(510);
    mp[5][20] = new PObject(520);
    mp[5][30] = new PObject(530);
    mp[5][40] = new PObject(540);
    mp[5][50] = new PObject(550);
    mp[6] = {};

    /* by-reference insertion */ {
        auto& lp = mp[6];

        lp[10] = new PObject(610);
        lp[20] = new PObject(620);
        lp[30] = new PObject(630);
        lp[40] = new PObject(640);
        lp[50] = new PObject(650);
        lp[60] = new PObject(660);
    }

    print_map(mp);

    printf("===\n");
    for (auto& subms : mp) {
        auto it = subms.second.begin();

        while (it != subms.second.end()) {
            if (it->first / 10 != subms.first) {
                it = subms.second.erase(it);
            } else {
                ++ it;
            }
        }
    }
    print_map(mp);

    return 0;
}
