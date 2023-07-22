#pragma once // 确保只被 include 一次

#include <gydm_stem/bang.hpp>

namespace WarGrey::STEM {
    /*********************************************************************************************/
    class SteppeAtlas : public WarGrey::STEM::PlanetCuteAtlas {
    public:
        SteppeAtlas(int row, int col);
        virtual ~SteppeAtlas() noexcept;

    public:
        int preferred_local_fps() override { return 4; }
        int update(uint64_t count, uint32_t interval, uint64_t uptime) override;

    public:
        void animal_die_at(int r, int c);
        void plant_grow_at(int r, int c);
        void plant_be_eaten_at(int r, int c);
        int get_plant_energy(int r, int c);
        int get_total_energy() { return this->total_energy; }

    public:
        void reset();
        int current_day() { return this->day; }

    protected:
        void on_tilemap_load(WarGrey::STEM::shared_texture_t atlas) override;

    private:
        void random_plant(int r0, int c0, int row_size, int col_size);

    private:
        int** energies;
        int total_energy;

    private:
        int day;
        int jungle_r;
        int jungle_c;
        int jungle_row;
        int jungle_col;
    };
}
