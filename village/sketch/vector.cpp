#include <iostream> /* C++ 标准输入输出头文件 */
#include <vector>

/**************************************************************/
class PObject {
public:
    static bool remove_if_even(const PObject* obj) {
        bool okay = (obj->value % 2 == 0);

        if (okay) {
             delete obj;
        }

        return okay;
    }

public:
    PObject(int v) : value(v) {}
    virtual ~PObject() noexcept {
        printf("destructing `%d`.\n", this->value);
    }

public:
    int value;
};

void print_vector(std::vector<PObject*>& vs) {
    for (size_t idx = 0; idx < vs.size(); idx ++) {
        if (idx == 0) {
            printf("%d", vs[idx]->value);
        } else {
            printf(", %d", vs[idx]->value);
        }
    }

    printf("\n");
}

/**************************************************************/
int main(int argc, char* argv[]) {
    std::vector<PObject*> vs;

    vs.push_back(new PObject(1));
    vs.push_back(new PObject(2));
    vs.push_back(new PObject(3));
    vs.push_back(new PObject(4));
    vs.push_back(new PObject(5));

    std::for_each(vs.begin(), vs.end(), [](PObject*& obj) {
        if (obj->value % 2 == 1) {
            delete obj;
            obj = nullptr;
        }
    });

    vs.erase(std::remove(vs.begin(), vs.end(), static_cast<PObject*>(nullptr)), vs.end());
    print_vector(vs);
    
    vs.push_back(new PObject(6));
    vs.push_back(new PObject(7));
    vs.push_back(new PObject(8));
    vs.push_back(new PObject(9));
    vs.push_back(new PObject(10));

    for (int idx = int(vs.size()) - 1; idx >= 0; idx --) {
        if (vs[idx]->value % 2 == 0) {
            delete vs[idx];
            vs.erase(vs.begin() + idx);
        }
    }

    print_vector(vs);

    return 0;
}
