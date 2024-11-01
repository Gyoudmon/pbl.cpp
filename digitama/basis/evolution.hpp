#pragma once // 确保只被 include 一次

#include <plteen/bang.hpp>

#include "dewdney/steppe.hpp"
#include "dewdney/animal.hpp"

#include <vector>

namespace Linguisteen {
    /*********************************************************************************************/
    class EvolutionWorld : public Plteen::TheBigBang {
    public:
        EvolutionWorld(float size_hint = 32.0F) : TheBigBang("演化游戏"), size_hint(size_hint) {}
        virtual ~EvolutionWorld() {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;
        void update(uint64_t count, uint32_t interval, uint64_t uptime) override;
        void on_mission_start(float width, float height) override;

    public:
        bool can_select(Plteen::IMatter* m) override;

    protected:
        void after_select(Plteen::IMatter* m, bool yes) override;
        bool update_tooltip(Plteen::IMatter* m, float lx, float ly, float gx, float gy) override;

    private:
        void animal_try_eat(Plteen::Animal* animal, IToroidalMovingAnimal* self);
        void animal_try_reproduce(Plteen::Animal* animal, IToroidalMovingAnimal* self, std::vector<Plteen::Animal*>& offsprings, float dx, float dy);
        void animal_move(Plteen::Animal* animal, IToroidalMovingAnimal* self, float tile_width, float tile_height);
        void clear_dead_animals();

    private:
        void reset_world();
        void update_world_info();
            
    private: /* 本世界中的物体 */
        Linguisteen::SteppeAtlas* steppe;
        std::vector<Plteen::Animal*> animals;
        Plteen::Historylet* phistory;
        Plteen::Historylet* ehistory;
        Plteen::Labellet* world_info;
 
    private: /* 本世界的参数设定 */
        int row;
        int col;

    private:
        float size_hint;
    };
}
