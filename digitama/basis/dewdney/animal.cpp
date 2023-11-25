#include "animal.hpp"

#include <gydm_stem/datum/fixnum.hpp>
#include <gydm_stem/graphics/brush.hpp>

#include <sstream>

using namespace WarGrey::STEM;

/*************************************************************************************************/
static const float lifebar_height = 2.0F;
static const double lifebar_alpha = 0.64;

static inline void random_gene_initialize(int gene[MOVING_WAYS]) {
    for (int idx = 0; idx < MOVING_WAYS; idx ++) {
        gene[idx] = random_uniform(1, 10);
    }
}

static inline void gene_mutate(int gene[MOVING_WAYS]) {
    int which = random_uniform(1, MOVING_WAYS) - 1;

    gene[which] = fxmax(1, gene[which] + random_uniform(-1, 1));
}

/*************************************************************************************************/
WarGrey::STEM::IToroidalMovingAnimal::IToroidalMovingAnimal(int row, int col, const int gene[MOVING_WAYS], double duration, int cycle, int energy)
        : duration(duration), breeding_cycle(cycle), row(row), col(col), energy(energy) {
    this->direction = random_uniform(0, MOVING_WAYS - 1);
    this->r = row >> 1;
    this->c = col >> 1;
    this->countdown = cycle;
    this->bio_clock = 0;

    this->full_energy = energy;
    this->reproduce_energy = energy / 5;
    this->generation = 1;

    if (gene == nullptr) {
        random_gene_initialize(this->gene);
    } else {
        for (int idx = 0; idx < MOVING_WAYS; idx ++) {
            this->gene[idx] = gene[idx];
        }
    }
}

std::string WarGrey::STEM::IToroidalMovingAnimal::description() {
    std::stringstream s;

    s << "子代: " << this->generation << ";";
    s << " 生命: " << fl2fxi(float(this->energy) / float(this->full_energy) * 10000.0F) / 100.0F << "%;";
    s << " 繁殖倒计时: " << this->countdown << ";";

    s << " 基因: [" << this->gene[0];
    for (size_t idx = 1; idx < MOVING_WAYS; idx ++) {
        s << ", " << this->gene[idx];
    }
    s << "].";

    return s.str();
}

void WarGrey::STEM::IToroidalMovingAnimal::draw(SDL_Renderer* render, float x, float y, float width, float height) {
    float lifebar_width = float(this->energy) / float(this->full_energy);
    float breed_width = 1.0F - float(fxmax(this->countdown, 0)) / float(this->breeding_cycle);

    if (this->energy >= this->reproduce_energy) {
        Brush::draw_rect(render, x, y, lifebar_width * width, lifebar_height, ROYALBLUE, lifebar_alpha);
        Brush::draw_line(render, x, y + lifebar_height, x + breed_width * width, y + lifebar_height, ORANGE, lifebar_alpha);
    } else {
        Brush::draw_rect(render, x, y, lifebar_width * width, lifebar_height, CRIMSON, lifebar_alpha);
    }
}

void WarGrey::STEM::IToroidalMovingAnimal::turn() {
    int sum = 0, rnd;

    for (int idx = 0; idx < MOVING_WAYS; idx ++) {
        sum += this->gene[idx];
    }

    rnd = random_uniform(0, sum - 1);
    this->direction = (this->direction + this->angle(0, rnd)) % MOVING_WAYS;
}

int WarGrey::STEM::IToroidalMovingAnimal::angle(int idx0, int rnd) {
    int next = rnd - this->gene[idx0];

    if (next < 0) {
        return 0;
    } else {
        return this->angle(idx0 + 1, next) + 1;
    }
}

void WarGrey::STEM::IToroidalMovingAnimal::move(int* delta_row, int* delta_col) {
    int orow = this->r;
    int ocol = this->c;
    int dr = 0;
    int dc = 0;
    
    switch (this->direction) {
    case 0: dr = -1; break;
    case 1: dr = -1; dc = +1; break;
    case 2: dc = +1; break;
    case 3: dc = dr = +1; break;
    case 4: dr = +1; break;
    case 5: dr = +1; dc = -1; break;
    case 6: dc = -1; break;
    case 7: dr = dc = -1; break;
    default: /* deadcode */;
    }

    this->r = safe_index(orow + dr, this->row);
    this->c = safe_index(ocol + dc, this->col);

    SET_BOX(delta_row, this->r - orow);
    SET_BOX(delta_col, this->c - ocol);
}

void WarGrey::STEM::IToroidalMovingAnimal::eat(int food_energy) {
    int gain_energy = food_energy * random_uniform(10, 20) / 100;

    this->energy = fxmin(this->full_energy, this->energy + gain_energy);
}

void WarGrey::STEM::IToroidalMovingAnimal::on_time_fly(int day) {
    if (this->bio_clock != day) {
        if (day > this->bio_clock) {
            int diff = (day - this->bio_clock);

            this->countdown -= diff;
            this->energy -= diff;
        } else { // 世界被重制了
            this->countdown = this->breeding_cycle;
            this->energy = this->full_energy;
        }
    
        this->bio_clock = day;
    }
}

IToroidalMovingAnimal* WarGrey::STEM::IToroidalMovingAnimal::asexually_reproduce() {
    auto offspring = new IToroidalMovingAnimal(this->row, this->col, this->gene, this->duration, this->breeding_cycle, this->full_energy);

    gene_mutate(offspring->gene);
    offspring->generation = this->generation + 1;
    offspring->energy = this->energy >> 1;
    offspring->r = this->r;
    offspring->c = this->c;
    offspring->bio_clock = this->bio_clock;
    
    this->countdown = this->breeding_cycle;

    return offspring;
}

/*************************************************************************************************/
WarGrey::STEM::TMRooster::TMRooster(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.5, direction, energy));
}

WarGrey::STEM::TMRooster::TMRooster(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void WarGrey::STEM::TMRooster::draw(SDL_Renderer* render, float x, float y, float width, float height) {
    Rooster::draw(render, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(render, x, y, width, height);
}

Animal* WarGrey::STEM::TMRooster::asexually_reproduce() {
    return new TMRooster(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
WarGrey::STEM::TMCow::TMCow(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 2.0, direction, energy));
}

WarGrey::STEM::TMCow::TMCow(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void WarGrey::STEM::TMCow::draw(SDL_Renderer* render, float x, float y, float width, float height) {
    Cow::draw(render, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(render, x, y, width, height);
}

Animal* WarGrey::STEM::TMCow::asexually_reproduce() {
    return new TMCow(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
WarGrey::STEM::TMCat::TMCat(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.4, direction, energy));
}

WarGrey::STEM::TMCat::TMCat(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void WarGrey::STEM::TMCat::draw(SDL_Renderer* render, float x, float y, float width, float height) {
    Cat::draw(render, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(render, x, y, width, height);
}

Animal* WarGrey::STEM::TMCat::asexually_reproduce() {
    return new TMCat(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
WarGrey::STEM::TMPigeon::TMPigeon(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.3, direction, energy));
}

WarGrey::STEM::TMPigeon::TMPigeon(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void WarGrey::STEM::TMPigeon::draw(SDL_Renderer* render, float x, float y, float width, float height) {
    Pigeon::draw(render, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(render, x, y, width, height);
}

Animal* WarGrey::STEM::TMPigeon::asexually_reproduce() {
    return new TMPigeon(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}
