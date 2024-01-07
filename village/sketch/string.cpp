#include <iostream> /* C++ 标准输入输出头文件 */
#include <cstring>  /* C++ 字符串头文件 */

/*************************************************************************************************/
#define VSNPRINT(retval, fmt) \
    const int DEFAULT_POOL_SIZE = 1024; \
    char chpool[DEFAULT_POOL_SIZE]; \
    int bigSize = DEFAULT_POOL_SIZE - 1; \
    char* pool; \
    va_list argl; \
    do { \
	pool = (bigSize < DEFAULT_POOL_SIZE) ? chpool : (new char[bigSize + 1]); \
    	va_start(argl, fmt); \
    	int status = vsnprintf(pool, bigSize + 1, fmt, argl); \
	va_end(argl); \
        if ((status == -1) || (status > bigSize)) { \
	    bigSize = ((status > 0) ? status : (bigSize * 2)) + 1; \
	    if (pool != chpool) delete[] pool; \
	    pool = nullptr; \
	} \
    } while (pool == nullptr); \
    std::string retval(pool); \
    if (pool != chpool) delete[] pool;

static std::string game_create_string(const char* fmt, ...) {
    VSNPRINT(s, fmt);

    return s;
}

/*************************************************************************************************/
int main(int argc, char* argv[]) {
    // 字符
    char a = 'a';
    char tab = '\t';
    char back_slash = '\'';
    
    // 字符串
    std::string char_tab = "a\t";
    std::string backslash_newline = "\'\n";

    // 字符串操作符
    std::string literal = char_tab + backslash_newline;

    std::cout << a << tab << back_slash << '\n';
    std::cout << literal;

    // 修改字符串
    literal[0] = 'b';
    std::cout << literal[0] << literal[1] << literal[2] << literal[3];

    // 中文字符和字符串
    char chinese_char_array[] = "我是一个汉字字符数组";
    std::string chinese_string = "我是一个汉字字符串";
    std::cout << "chinese_char_array" << ": " << chinese_char_array << std::endl;
    std::cout << "chinese_string" << ": " << chinese_string << std::endl;

    // 字符串插值
    std::string sentence = game_create_string("%s to grid(%d, %d)", "move", 3, 2);
    std::cout << sentence << std::endl;
    printf("%s to grid(%f, %f)\n", "move", 3.14159, 2.71728);

    return 0;
}

