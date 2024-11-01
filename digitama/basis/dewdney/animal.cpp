#include "animal.hpp"

#include <plteen/datum/fixnum.hpp>

#include <sstream>

using namespace Plteen;
using namespace Linguisteen;

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
Linguisteen::IToroidalMovingAnimal::IToroidalMovingAnimal(int row, int col, const int gene[MOVING_WAYS], double duration, int cycle, int energy)
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

std::string Linguisteen::IToroidalMovingAnimal::description() {
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

void Linguisteen::IToroidalMovingAnimal::draw(dc_t* dc, float x, float y, float width, float height) {
    float lifebar_width = float(this->energy) / float(this->full_energy);
    float breed_width = 1.0F - float(fxmax(this->countdown, 0)) / float(this->breeding_cycle);

    if (this->energy >= this->reproduce_energy) {
        dc->draw_rect(x, y, lifebar_width * width, lifebar_height, RGBA(ROYALBLUE, lifebar_alpha));
        dc->draw_line(x, y + lifebar_height, x + breed_width * width, y + lifebar_height, RGBA(ORANGE, lifebar_alpha));
    } else {
        dc->draw_rect(x, y, lifebar_width * width, lifebar_height, RGBA(CRIMSON, lifebar_alpha));
    }
}

void Linguisteen::IToroidalMovingAnimal::turn() {
    int sum = 0, rnd;

    for (int idx = 0; idx < MOVING_WAYS; idx ++) {
        sum += this->gene[idx];
    }

    rnd = random_uniform(0, sum - 1);
    this->direction = (this->direction + this->angle(0, rnd)) % MOVING_WAYS;
}

int Linguisteen::IToroidalMovingAnimal::angle(int idx0, int rnd) {
    int next = rnd - this->gene[idx0];

    if (next < 0) {
        return 0;
    } else {
        return this->angle(idx0 + 1, next) + 1;
    }
}

void Linguisteen::IToroidalMovingAnimal::move(int* delta_row, int* delta_col) {
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

void Linguisteen::IToroidalMovingAnimal::eat(int food_energy) {
    int gain_energy = food_energy * random_uniform(10, 20) / 100;

    this->energy = fxmin(this->full_energy, this->energy + gain_energy);
}

void Linguisteen::IToroidalMovingAnimal::on_time_fly(int day) {
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

IToroidalMovingAnimal* Linguisteen::IToroidalMovingAnimal::asexually_reproduce() {
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
Linguisteen::TMRooster::TMRooster(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.5, direction, energy));
}

Linguisteen::TMRooster::TMRooster(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void Linguisteen::TMRooster::draw(dc_t* dc, float x, float y, float width, float height) {
    Rooster::draw(dc, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(dc, x, y, width, height);
}

Animal* Linguisteen::TMRooster::asexually_reproduce() {
    return new TMRooster(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
Linguisteen::TMCow::TMCow(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 2.0, direction, energy));
}

Linguisteen::TMCow::TMCow(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void Linguisteen::TMCow::draw(dc_t* dc, float x, float y, float width, float height) {
    Cow::draw(dc, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(dc, x, y, width, height);
}

Animal* Linguisteen::TMCow::asexually_reproduce() {
    return new TMCow(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
Linguisteen::TMCat::TMCat(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.4, direction, energy));
}

Linguisteen::TMCat::TMCat(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void Linguisteen::TMCat::draw(dc_t* dc, float x, float y, float width, float height) {
    Cat::draw(dc, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(dc, x, y, width, height);
}

Animal* Linguisteen::TMCat::asexually_reproduce() {
    return new TMCat(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}

/*************************************************************************************************/
Linguisteen::TMPigeon::TMPigeon(int row, int col, int direction, int energy) {
    this->attach_metadata(new IToroidalMovingAnimal(row, col, nullptr, 0.3, direction, energy));
}

Linguisteen::TMPigeon::TMPigeon(IToroidalMovingAnimal* self) {
    this->attach_metadata(self);
}

void Linguisteen::TMPigeon::draw(dc_t* dc, float x, float y, float width, float height) {
    Pigeon::draw(dc, x, y, width, height);
    this->unsafe_metadata<IToroidalMovingAnimal>()->draw(dc, x, y, width, height);
}

Animal* Linguisteen::TMPigeon::asexually_reproduce() {
    return new TMPigeon(this->unsafe_metadata<IToroidalMovingAnimal>()->asexually_reproduce());
}
