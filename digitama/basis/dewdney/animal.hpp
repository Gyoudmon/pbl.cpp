#pragma once // 确保只被 include 一次

#include "../../big_bang/bang.hpp"

#include <vector>

namespace WarGrey::STEM {
    static const int MOVING_WAYS = 8;

    /*********************************************************************************************/
    class IToroidalMovingAnimal : public WarGrey::STEM::IMatterMetadata {
    public:
        IToroidalMovingAnimal(int row, int col, const int gene[MOVING_WAYS], double duration, int cycle, int energy);
        virtual ~IToroidalMovingAnimal() {}

        std::string description();

    public:
        void draw(SDL_Renderer* renderer, float x, float y, float width, float height);

    public:
        void turn();
        void move(int* dr = nullptr, int* dc = nullptr);
        void eat(int food_energy);
        IToroidalMovingAnimal* asexually_reproduce();

    public:
        bool is_alive() const { return this->energy > 0; }
        bool can_reproduce() const { return (this->energy >= this->reproduce_energy) && (this->countdown <= 0); }
        double pace_duration() { return this->duration; }
        int current_generation() { return this->generation; }
        int current_row() { return r; }
        int current_col() { return c; }

    public:
        void on_time_fly(int day);

    private:
        int angle(int idx0, int rnd);

    private:
        double duration;
        int full_energy;
        int reproduce_energy;
        int gene[MOVING_WAYS];
        int breeding_cycle;
        int row;
        int col;

    private:
        int bio_clock;
        int generation;
        int countdown;
    
    private:
        int direction;
        int energy;
        int r;
        int c;
    };

    /*********************************************************************************************/
    class TMRooster : public WarGrey::STEM::Rooster {
    public:
        TMRooster(int row, int col, int cycle = 30, int energy = 300);
        TMRooster(WarGrey::STEM::IToroidalMovingAnimal* self);
        virtual ~TMRooster() {}

        const char* name() override { return "公鸡"; }

    public:
        void draw(SDL_Renderer* renderer, float x, float y, float width, float height) override;

    public:
        Animal* asexually_reproduce() override;
    };

    class TMPigeon : public WarGrey::STEM::Pigeon {
    public:
        TMPigeon(int row, int col, int cycle = 30, int energy = 300);
        TMPigeon(WarGrey::STEM::IToroidalMovingAnimal* self);
        virtual ~TMPigeon() {}

        const char* name() override { return "鸽子"; }

    public:
        void draw(SDL_Renderer* renderer, float x, float y, float width, float height) override;

    public:
        Animal* asexually_reproduce() override;
    };

    class TMCow : public WarGrey::STEM::Cow {
    public:
        TMCow(int row, int col, int cycle = 365, int energy = 600);
        TMCow(WarGrey::STEM::IToroidalMovingAnimal* self);
        virtual ~TMCow() {}

        const char* name() override { return "奶牛"; }

    public:
        void draw(SDL_Renderer* renderer, float x, float y, float width, float height) override;

    public:
        Animal* asexually_reproduce() override;
    };

    class TMCat : public WarGrey::STEM::Cat {
    public:
        TMCat(int row, int col, int cycle = 58, int energy = 1000);
        TMCat(WarGrey::STEM::IToroidalMovingAnimal* self);
        virtual ~TMCat() {}

        const char* name() override { return "食草猫"; }

    public:
        void draw(SDL_Renderer* renderer, float x, float y, float width, float height) override;

    public:
        Animal* asexually_reproduce() override;
    };
}
