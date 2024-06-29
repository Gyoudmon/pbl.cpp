#include "paddleball.hpp"

using namespace GYDM;
using namespace Linguisteen;

const float ball_radius = 8.0F;
const float paddle_width = 128.0F;
const float paddle_height = 8.0F;

const float ball_speed = 6.0F;
const float paddle_speed = ball_speed * 1.5F;

/*************************************************************************************************/
// 实现 PaddleBallWorld::load 方法，加载球和桨，设置相关边界碰撞策略
void Linguisteen::PaddleBallWorld::load(float width, float height) {
    TheBigBang::load(width, height);

    this->ball = this->insert(new Circlet(ball_radius, CHOCOLATE));
    this->paddle = this->insert(new Rectanglet(paddle_width, paddle_height, ROYALBLUE));

    this->ball->set_border_strategy(BorderStrategy::BOUNCE, BorderStrategy::BOUNCE, BorderStrategy::STOP, BorderStrategy::BOUNCE);
    this->paddle->set_border_strategy(BorderStrategy::IGNORE, BorderStrategy::STOP);
}

// 实现 PaddleBallWorld::on_mission_start 方法，调整球和桨的位置
void Linguisteen::PaddleBallWorld::on_mission_start(float width, float height) {
    // 确保球产生于屏幕上方的中间
    this->move_to(this->ball, Position(width * 0.5F, ball_radius), MatterPort::CT);
    
    // 确保桨产生在靠近屏幕下方的中间
    this->move_to(this->paddle, Position(width * 0.5F, height - paddle_height * 4.0F), MatterPort::CC);

    // 设置球的速度
    this->ball->set_velocity(ball_speed, double(random_uniform(30, 150)));
}

// 实现 PaddleBallWorld::update 方法，根据球和桨的当前位置判断是否有碰撞，无需考虑运动细节
void Linguisteen::PaddleBallWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    if (this->is_colliding(this->ball, this->paddle)) {
        this->ball->motion_bounce(false, true); // 正常，反弹球
    }
}

// 实现 PaddleBallWorld::on_char 方法，处理键盘事件，用于控制桨的移动
void Linguisteen::PaddleBallWorld::on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) {
    if (key == 'a') {
        if (pressed) {
            this->paddle->set_velocity(paddle_speed, 180.0);
        } else {
            this->paddle->set_velocity(0.0, 180.0);
        }
    } else if (key == 'd') {
        if (pressed) {
            this->paddle->set_velocity(paddle_speed, 000.0);
        } else {
            this->paddle->set_velocity(0.0, 000.0);
        }
    }
}
