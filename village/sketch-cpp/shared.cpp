#include <iostream> /* C++ 标准输入输出头文件 */
#include <memory>

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

typedef std::shared_ptr<PObject> shared_object_t;
static shared_object_t invalid_object = std::make_shared<PObject>(0);

/**************************************************************/
int main(int argc, char* argv[]) {
    shared_object_t zero = nullptr;
    shared_object_t invalids[3] = { invalid_object, invalid_object, invalid_object };

    printf("%ld\n", zero.use_count());
    printf("%ld\n", invalids[0].use_count());

    return 0;
}
