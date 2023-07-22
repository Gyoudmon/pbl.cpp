#include <gydm_stem/game.hpp>

using namespace WarGrey::STEM;

const float ball_radius = 8.0F;
const float paddle_width = 128.0F;
const float paddle_height = 8.0F;

const float ball_speed = 4.0F;
const float paddle_speed = ball_speed * 3.0F;

namespace {
    /************************************** 声明游戏宇宙里的物体 ***************************************/
    /* 定义一个类型，并命名为 Ball（球） */
    struct Ball {
        /* 球的位置 */
        float x = 0.0F;
        float y = 0.0F;
        
        /* 球位置的变化量 */
        float dx = 0.0F;
        float dy = 0.0F;

        /* 球的颜色 */
        uint32_t color = ORANGE;
    };

    /* 定义一个类型，并命名为 Paddle（桨） */
    class Paddle {
    public: /* <- class 定义的类型，其属性和方法默认为 private，必须明确指明为 public  */
        /* 桨的位置 */
        float x = 0.0F;
        float y = 0.0F;

        /* 桨的速度 */
        float speed = 0.0F;
    };

    /******************************************* 声明游戏世界 ******************************************/
    class PaddleBallWorld : public WarGrey::STEM::Universe {
    public:
        PaddleBallWorld() : Universe("Paddle Ball (Procedural)") { /* 什么都不做 */ }
        virtual ~PaddleBallWorld() { /* 什么都不做 */ }

    public: // 覆盖游戏基本方法
        // 定义和实现 PaddleBallWorld::reflow 方法，调整球和桨的初始位置
        void reflow(float width, float height) override {
            // 确保球产生于屏幕上方的中间
            this->ball.x = width / 2.0F;
            this->ball.y = ball_radius;

            this->ball.dx = 1.0F * ball_speed;
            this->ball.dy = 1.0F * ball_speed;

            // 确保桨产生在靠近屏幕下方的中间
            this->paddle.x = this->ball.x - paddle_width / 2.0F;
            this->paddle.y = height - paddle_height * 4.0F;
        }

        // 定义和实现 PaddleBallWorld::update 方法，刷新球和桨的位置，这就是“运动动画”的基本原理
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override {
            int width, height;
            
            this->feed_window_size(&width, &height);

            if (this->ball.y < height - ball_radius) { // 球未触底
                /* 移动球，碰到边界反弹 */ {
                    this->ball.x = this->ball.x + this->ball.dx;
                    this->ball.y = this->ball.y + this->ball.dy;

                    if ((this->ball.x <= ball_radius) || (this->ball.x >= width - ball_radius)) {
                        this->ball.dx = -this->ball.dx;
                    }
    
                    if (this->ball.y <= ball_radius) {
                        this->ball.dy = -this->ball.dy;
                    }
                }

                /* 移动桨，碰到边界停止 */ {
                    if (this->paddle.speed != 0.0F) {
                        this->paddle.x += this->paddle.speed;

                        if (this->paddle.x < 0.0F) {
                            this->paddle.x = 0.0F;
                        } else if (this->paddle.x + paddle_width > width) {
                            this->paddle.x = width - paddle_width;
                        }
                    }
                }

                /* 检测小球是否被捕获 */ {
                    if (this->ball.y + ball_radius >= this->paddle.y) {
                        if ((this->ball.x >= this->paddle.x) && (this->ball.x <= this->paddle.x + paddle_width)) {
                            this->ball.dy = -this->ball.dy;
                        } else {
                            ball.color = RED;
                        }
                    }
                }

                this->notify_updated(); // 更新有效，通知系统舞台需要重绘
            }
        }

        // 定义和实现 PaddleBallWorld::draw 方法，在舞台上绘制出当前位置的球和桨
        void draw(SDL_Renderer* renderer, int x, int y, int width, int height) override {
            game_fill_circle(renderer, this->ball.x, this->ball.y, ball_radius, this->ball.color);
            game_fill_rect(renderer, this->paddle.x, this->paddle.y, paddle_width, paddle_height, FORESTGREEN);
        }

    protected: // 覆盖键盘事件处理方法
        // 定义和实现 PaddleBallWorld::on_char 方法，处理键盘事件，用于控制桨的移动
        void on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) override {
            switch(key) {
                case 'a': this->paddle.speed = (pressed ? -paddle_speed : 0.0F); break;
                case 'd': this->paddle.speed = (pressed ? +paddle_speed : 0.0F); break;
            }
        }

    private:   // 本游戏世界中的物体
        Ball ball;
        Paddle paddle;
    };
}





/*************************************************************************************************/
int main(int argc, char* args[]) {
    PaddleBallWorld universe;

    universe.construct(argc, args);
    universe.big_bang();

    return 0;
}
