#include "steppe.hpp"

#include <gydm/datum/fixnum.hpp>

using namespace GYDM;
using namespace Linguisteen;

/*************************************************************************************************/
static const GroundBlockType seed_tile_type = GroundBlockType::Dirt;
static const GroundBlockType fertile_tile_type = GroundBlockType::Soil;
static const GroundBlockType steppe_tile_type = GroundBlockType::Plain;
static const GroundBlockType plant_tile_type = GroundBlockType::Grass;
    
static const int plant_energy = 120;
static const int plant_max_energy = plant_energy * 4;

/*************************************************************************************************/
Linguisteen::SteppeAtlas::SteppeAtlas(int row, int col) : PlanetCuteAtlas(row, col, steppe_tile_type) {
    this->jungle_row = 8 + row % 2;
    this->jungle_col = 6 + col % 2;

    this->jungle_r = (row - this->jungle_row) / 2;
    this->jungle_c = (col - this->jungle_col) / 2;
}

Linguisteen::SteppeAtlas::~SteppeAtlas() noexcept {
    if (this->energies != nullptr) {
        for (int r = 0; r < this->map_row; r ++) {
            delete [] this->energies[r];
        }

        delete [] this->energies;
    }
}

int Linguisteen::SteppeAtlas::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    this->random_plant(this->jungle_r, this->jungle_c, this->jungle_row, this->jungle_col);
    this->random_plant(0, 0, this->map_row, this->map_col);

    this->day += 1;
    
    return 0;
}

void Linguisteen::SteppeAtlas::random_plant(int r0, int c0, int row_size, int col_size) {
    int r = random_uniform(0, row_size - 1) + r0;
    int c = random_uniform(0, col_size - 1) + c0;

    this->plant_grow_at(r, c);
}

void Linguisteen::SteppeAtlas::on_tilemap_load(shared_texture_t atlas) {
    PlanetCuteAtlas::on_tilemap_load(atlas);

    this->energies = new int*[this->map_row];
    for (int r = 0; r < this->map_row; r ++) {
        this->energies[r] = new int[this->map_col];
    }

    this->reset();
}

void Linguisteen::SteppeAtlas::reset() {
    for (int r = 0; r < this->map_row; r ++) {
        for (int c = 0; c < this->map_col; c ++) {
            this->set_tile_type(r, c, steppe_tile_type);
            this->energies[r][c] = 0;
        }
    }

    this->total_energy = 0;
    this->day = 0;
}

/*************************************************************************************************/
int Linguisteen::SteppeAtlas::get_plant_energy(int r, int c) {
    r = safe_index(r, this->map_row);
    c = safe_index(c, this->map_col);

    return this->energies[r][c];
}

void Linguisteen::SteppeAtlas::plant_grow_at(int r, int c) {
    r = safe_index(r, this->map_row);
    c = safe_index(c, this->map_col);
    
    int origin_energy = this->energies[r][c];

    this->energies[r][c] = fxmin(this->energies[r][c] + plant_energy, plant_max_energy);
    this->total_energy += (this->energies[r][c] - origin_energy);
    this->set_tile_type(r, c, plant_tile_type);
}

void Linguisteen::SteppeAtlas::plant_be_eaten_at(int r, int c) {
    r = safe_index(r, this->map_row);
    c = safe_index(c, this->map_col);

    this->total_energy -= this->energies[r][c];
    this->energies[r][c] = 0;
    this->set_tile_type(r, c, seed_tile_type);
}

void Linguisteen::SteppeAtlas::animal_die_at(int r, int c) {
    r = safe_index(r, this->map_row);
    c = safe_index(c, this->map_col);

    /** TODO
     * How to calculate the energy produced by dead body?
     * Meanwhile leaving the energy as-is.
     */

    this->set_tile_type(r, c, fertile_tile_type);
}
