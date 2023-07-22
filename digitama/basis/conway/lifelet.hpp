#pragma once // 确保只被 include 一次

#include <gydm_stem/bang.hpp>

#include <map>

namespace WarGrey::STEM {
    /** 声明游戏物体 **/
    class GameOfLifelet : public WarGrey::STEM::IGraphlet {
    public:
        GameOfLifelet(int n, float gridsize) : GameOfLifelet(n, n, gridsize) {}
        GameOfLifelet(int row, int col, float gridsize) : row(row), col(col), gridsize(gridsize) {}
        virtual ~GameOfLifelet();

        void construct(SDL_Renderer* renderer) override;

    public:
        void feed_extent(float x, float y, float* width = nullptr, float* height = nullptr) override;
        void draw(SDL_Renderer* renderer, float x, float y, float Width, float Height) override;

    public:
        void show_grid(bool yes);
        void set_color(uint32_t hex);
        void toggle_life_at_location(float x, float y);
        int get_generation() { return this->generation; }

    public:
        void construct_random_world();
        bool pace_forward();
        void reset();

    public:
        void load(const std::string& life_world, std::ifstream& golin);
        void save(const std::string& life_world, std::ofstream& golout);

    protected: // 演化策略, 默认留给子类实现
        virtual void evolve(int** world, int* shadow, int row, int col) = 0;

    private:
        int row;
        int col;
        int generation;
        int** world = nullptr;
        int* shadow = nullptr;

    private:
        uint32_t color = BLACK;
        bool hide_grid;

    private:
        float gridsize;
    };

    /*********************************************************************************************/
    class ConwayLifelet : public WarGrey::STEM::GameOfLifelet {
        using GameOfLifelet::GameOfLifelet;

    protected:
        void evolve(int** world, int* shadow, int row, int col) override;
    };

    class HighLifelet : public WarGrey::STEM::GameOfLifelet {
        using GameOfLifelet::GameOfLifelet;

    protected:
        void evolve(int** world, int* shadow, int row, int col) override;
    };
}
