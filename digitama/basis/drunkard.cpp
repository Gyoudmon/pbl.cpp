#include "drunkard.hpp"

using namespace GYDM;
using namespace Linguisteen;

static const float step_size = 2.0F;
static const double step_duration = 0.2;

/*************************************************************************************************/
void Linguisteen::DrunkardWalkWorld::load(float width, float height) {
    this->beach = this->insert(new Sprite(digimon_path("assets/beach", ".png")));
    this->tent = this->insert(new SpriteGridSheet(digimon_path("assets/tents", ".png"), 1, 4));
    this->track = this->insert(new Tracklet(width, height));
    this->drunkard = this->insert(new Agate());
    this->partner = this->insert(new Tita());

    this->bind_canvas(this->drunkard, this->track, MatterPort::CB);
    this->bind_canvas(this->partner, this->track, MatterPort::CB);

    this->set_pen_color(this->drunkard, FIREBRICK);
    this->set_pen_color(this->partner, DODGERBLUE);

    TheBigBang::load(width, height);
}

void Linguisteen::DrunkardWalkWorld::reflow(float width, float height) {
    this->move_to(this->beach, { width * 0.5F, height }, MatterPort::CB);
    this->move_to(this->tent, { 0.0F, height }, MatterPort::LB);
    this->move_to(this->track, { width * 0.5F, height * 0.5F }, MatterPort::CC);
    
    TheBigBang::reflow(width, height);
}

void Linguisteen::DrunkardWalkWorld::on_mission_start(float width, float height) {
    this->drunkard->switch_mode(BracerMode::Walk);
    this->drunkard->set_heading(-180.0);

    this->move_to(this->drunkard, { width * 0.95F, height * 0.9F }, MatterPort::CC);
    this->move_to(this->partner, { width * 0.24F, height * 0.9F }, MatterPort::CC);
}

void Linguisteen::DrunkardWalkWorld::update(uint64_t interval, uint32_t count, uint64_t uptime) {
    if (!this->is_colliding(this->drunkard, this->partner)) {
        if (this->partner->motion_stopped()) {
            this->random_walk(this->partner);
        }

        this->drunkard_walk(this->drunkard);
    } else if (this->partner->current_mode() != BracerMode::Win) {
        this->partner->motion_stop();
        this->drunkard->switch_mode(BracerMode::Win, 1);
        this->partner->switch_mode(BracerMode::Win, 1);
    }
}

/*************************************************************************************************/
void Linguisteen::DrunkardWalkWorld::random_walk(Bracer* who) {
    Dot dot;
    
    // random_uniform(-1, 1) 产生一个位于区间 [-1, 1] 的随机整数
    dot.x = (random_uniform(-1, 1)); // 左右移动或不动
    dot.y = (random_uniform(-1, 1)); // 上下移动或不动

    this->pen_down(who);
    this->glide(step_duration, who, dot * step_size);
    this->pen_up(who);
}

void Linguisteen::DrunkardWalkWorld::drunkard_walk(Bracer* who) {
    // 产生位于区间 [0, 100] 的随机整数
    int chance = random_uniform(0, 100);
    Dot dot;
    
    if (chance < 10) {
        // no move
    } else if (chance < 58) {
        dot.x = -1.0F;
    } else if (chance < 60) {
        dot.x = +1.0F;
    } else if (chance < 80) {
        dot.y = +1.0F;
    } else {
        dot.y = -1.0F;
    }

    this->pen_down(who);
    this->move(who, dot);
    this->pen_up(who);
}
