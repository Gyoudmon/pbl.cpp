#include "angry_bird.hpp"

using namespace GYDM;
using namespace Linguisteen;

const float ball_speed = 6.0F;
const float paddle_speed = ball_speed * 1.5F;

/*************************************************************************************************/
// 实现 AngryBirdWorld::load 方法，加载场景和角色
void Linguisteen::AngryBirdWorld::load(float width, float height) {
    TheBigBang::load(width, height);

    this->set_background(LIGHTBLUE);

    this->ground = this->insert(new MarioGroundAtlas(0U, 3, 75));
    this->catapult = this->insert(new Sprite(digimon_path("assets/catapult", ".png")));

    this->catapult->scale(0.20F);
}

// 实现 AngryBirdWorld::reflow 方法，布置场景
void Linguisteen::AngryBirdWorld::reflow(float width, float height) {
    this->move_to(this->ground, { width * 0.5F, height }, MatterAnchor::CB);
    this->move_to(this->catapult, { this->ground, { 0.12F, 0.01F }}, MatterAnchor::LB);
}

// 实现 AngryBirdWorld::update 方法，根据球和桨的当前位置判断是否有碰撞，无需考虑运动细节
void Linguisteen::AngryBirdWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
}

// 实现 AngryBirdWorld::on_char 方法，处理键盘事件，用于控制桨的移动
void Linguisteen::AngryBirdWorld::on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) {
}
