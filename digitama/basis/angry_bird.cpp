#include "angry_bird.hpp"

using namespace GYDM;
using namespace Linguisteen;

/*************************************************************************************************/
// 实现 AngryBirdWorld::load 方法，加载场景和角色
void Linguisteen::AngryBirdWorld::load(float width, float height) {
    TheBigBang::load(width, height);

    this->set_background(LIGHTBLUE);

    this->ground = this->insert(new MarioGroundAtlas(0U, 3, 75));
    this->catapult = this->insert(new Sprite(digimon_path("assets/catapult", ".png")));

    this->angry_bird = this->insert(new SpriteGridSheet(digimon_path("assets/AngryBirds", ".png"), 1, 5));
    this->king_pig = this->insert(new SpriteGridSheet(digimon_path("assets/Pigs", ".png"), 1, 9));
    
    this->catapult->scale(0.20F);
    this->king_pig->scale(0.40F);
    this->king_pig->switch_to_random_costume();
}

// 实现 AngryBirdWorld::reflow 方法，布置场景
void Linguisteen::AngryBirdWorld::reflow(float width, float height) {
    this->move_to(this->ground, { width * 0.5F, height }, MatterPort::CB);
    this->move_to(this->catapult, { this->ground, { 0.12F, 0.01F }}, MatterPort::LB);

    this->move_to(this->angry_bird, { this->catapult, { 0.5F, 0.25F }}, MatterPort::CC);
    this->move_to(this->king_pig, { width * 0.618F, height * 0.5F }, MatterPort::CC);
}

// 实现 AngryBirdWorld::update 方法，根据球和桨的当前位置判断是否有碰撞，无需考虑运动细节
void Linguisteen::AngryBirdWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
}

// 实现 AngryBirdWorld::on_char 方法，处理键盘事件，用于控制桨的移动
void Linguisteen::AngryBirdWorld::on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) {
}
