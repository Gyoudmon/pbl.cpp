// shape.cpp 文件
#include <gydm_stem/game.hpp> // 导入游戏模块

using namespace WarGrey::STEM; // 声明本模块的类和函数默认以 WarGrey::STEM 的名义使用

/*************************************************************************************************/
namespace {
    class ShapeWorld : public WarGrey::STEM::Universe {
    public:
        // 构造函数，默认什么都不做，除了通过父类构造函数设置窗口标题和帧频
        ShapeWorld() : Universe("Primitive Shapes") {}
            
        // 析构函数，默认什么都不做
        virtual ~ShapeWorld() {}

    public:
        // 定义和实现 ShapeWorld::construct 方法，设置窗口大小
        void construct(int argc, char* argv[]) override {
            this->set_window_size(800, 600);
        }

        // 定义和实现 ShapeWorld::draw 方法，本例中绘制一系列几何图形
        void draw(SDL_Renderer* renderer, int x, int y, int width, int height) override {
            game_draw_blended_text(GameFont::fangsong(), renderer,
                this->get_foreground_color(), 10, 10, "基本图形陈列馆(过程式)");

            /** 绘制椭圆院子 **/
            game_fill_ellipse(renderer, 400, 500, 200, 80, PALEGREEN);                  // 画苍绿色椭圆
            game_draw_ellipse(renderer, 400, 500, 200, 80, KHAKI);                      // 画卡其色轮廓

            /** 绘制(正)三角形屋顶 **/
            game_fill_regular_polygon(renderer, 3, 400, 260, 140, -90, DEEPSKYBLUE);    // 画深空篮正三角形
            game_draw_regular_polygon(renderer, 3, 400, 260, 140, -90, ROYALBLUE);      // 画皇家蓝轮廓

            /** 绘制矩形墙壁 **/
            game_fill_rect(renderer, 300, 330, 200, 180, WHITESMOKE);                   // 画烟雾白矩形
            game_draw_rect(renderer, 300, 330, 200, 180, SNOW);                         // 画雪白色边框

            /** 绘制矩形门 **/
            game_fill_rect(renderer, 324, 426, 42, 84, KHAKI);                          // 画卡其色矩形
            game_draw_rect(renderer, 324, 426, 42, 84, DARKKHAKI);                      // 画深卡其色边框

            /** 绘制门锁 **/
            game_fill_circle(renderer, 358, 468, 4, CHOCOLATE);                         // 画巧克力色圆
            game_draw_circle(renderer, 358, 468, 4, CHOCOLATE);                         // 画巧克力色轮廓

            /** 绘制窗户 **/
            game_fill_rect(renderer, 400, 388, 64, 64, LIGHTSKYBLUE);                   // 画淡天蓝色矩形
            game_draw_rect(renderer, 400, 388, 64, 64, SKYBLUE);                        // 画天蓝色边框
        }
    };
}

/*************************************************************************************************/
int main(int argc, char* args[]) {
    ShapeWorld universe;

    universe.construct(argc, args);
    universe.big_bang();

    return 0;
}
