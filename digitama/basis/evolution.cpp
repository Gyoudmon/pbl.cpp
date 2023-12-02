#include "evolution.hpp"

#include <gydm_stem/datum/fixnum.hpp>

#include <algorithm>

using namespace WarGrey::STEM;

/*************************************************************************************************/
static const char* matrics_fmt = "在线天数: %d    消费者总数: %d    生产者能量总和: %d";

/*************************************************************************************************/
void WarGrey::STEM::EvolutionWorld::load(float width, float height) {
    TheBigBang::load(width, height);
    
    float world_width = width;
    float world_height = height;
    float logic_width;
    
    this->col = fl2fxi(world_width / this->size_hint) - 1;
    this->row = fl2fxi(world_height / this->size_hint) - 1;

    // 初始化世界
    this->steppe = this->insert(new SteppeAtlas(this->row, this->col));
    this->world_info = this->insert(new Labellet(GameFont::serif(), BLACK, matrics_fmt, 0));
    this->phistory = this->insert(new Historylet(200.0F, 100.0F, ROYALBLUE));
    this->ehistory = this->insert(new Historylet(200.0F, 100.0F, ORANGE));

    this->animals.push_back(this->insert(new TMRooster(this->row, this->col)));
    this->animals.push_back(this->insert(new TMPigeon(this->row, this->col)));
    this->animals.push_back(this->insert(new TMCow(this->row, this->col)));
    this->animals.push_back(this->insert(new TMCat(this->row, this->col)));

    /* 简单配置物体 */
    this->steppe->feed_logic_tile_extent(&logic_width);
    this->steppe->scale_to(this->size_hint / logic_width);
}

void WarGrey::STEM::EvolutionWorld::reflow(float width, float height) {
    TheBigBang::reflow(width, height);
    float cx = width * 0.5F;
    float cy = (height + this->get_titlebar_height()) * 0.5F;
    float top_overlay;

    this->steppe->feed_map_overlay(&top_overlay);
    
    this->move_to(this->steppe, cx, cy, MatterAnchor::CC);
    this->move_to(this->world_info, this->steppe, MatterAnchor::RT, MatterAnchor::RB, 0.0F, top_overlay * 0.5F);
    this->move_to(this->ehistory, this->world_info, MatterAnchor::RT, MatterAnchor::RB);
    this->move_to(this->phistory, this->ehistory, MatterAnchor::LC, MatterAnchor::RC, -top_overlay);
}

void WarGrey::STEM::EvolutionWorld::on_mission_start(float width, float height) {
    float bottom_overlay;

    this->steppe->feed_map_overlay(nullptr, nullptr, &bottom_overlay);
    
    this->reset_world();
    this->phistory->clear();
    this->ehistory->clear();

    // Animals remain the same to simulate the natural disaster
    for (auto animal : this->animals) {
        auto self = animal->unsafe_metadata<IToroidalMovingAnimal>();

        this->steppe->glide_to_logic_tile(self->pace_duration(), animal,
            self->current_row(), self->current_col(), MatterAnchor::CC,
            MatterAnchor::CB, 0.0F, bottom_overlay);
    }
}

void WarGrey::STEM::EvolutionWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    if (this->animals.empty()) {
        this->world_info->set_text_color(FIREBRICK);
        this->phistory->set_pen_color(CRIMSON);
        this->ehistory->set_pen_color(CRIMSON);
    } else {
        std::vector<Animal*> offsprings;
        float tile_width, tile_height, bottom_overlay;
        bool has_death = false;
        
        this->steppe->feed_logic_tile_extent(&tile_width, &tile_height);
        this->steppe->feed_map_overlay(nullptr, nullptr, &bottom_overlay);

        for (auto animal : this->animals) {  
            auto self = animal->unsafe_metadata<IToroidalMovingAnimal>();
          
            self->on_time_fly(this->steppe->current_day());

            if (animal->motion_stopped()) {
                if (self->is_alive()) {
                    this->animal_try_eat(animal, self);
                    this->animal_try_reproduce(animal, self, offsprings, 0.0F, bottom_overlay);
                    this->animal_move(animal, self, tile_width, tile_height);
                    this->notify_updated(animal);
                } else {
                    has_death = true;
                }
            }
        }

        if (has_death) {
            this->clear_dead_animals();
        }

        if (!offsprings.empty()) {
            for (auto offspring : offsprings) {
                this->animals.push_back(offspring);
            }
            
            offsprings.clear();
        }
    }

    this->update_world_info();
}

void WarGrey::STEM::EvolutionWorld::animal_try_eat(Animal* animal, IToroidalMovingAnimal* self) {
    int r = self->current_row();
    int c = self->current_col();
    int plant_energy = this->steppe->get_plant_energy(r, c);

    if (plant_energy > 0) {
        self->eat(plant_energy);
        this->steppe->plant_be_eaten_at(r, c);
    }
}

void WarGrey::STEM::EvolutionWorld::animal_try_reproduce(Animal* animal, IToroidalMovingAnimal* self, std::vector<Animal*>& offsprings, float dx, float dy) {
    if (self->can_reproduce()) {
        auto offspring = animal->asexually_reproduce();
        auto offself = offspring->unsafe_metadata<IToroidalMovingAnimal>();

        offsprings.push_back(this->insert(offspring));
        this->steppe->move_to_logic_tile(offspring,
                    offself->current_row(), offself->current_col(), MatterAnchor::CC,
                    MatterAnchor::CB, dx, dy);
    }
}

void WarGrey::STEM::EvolutionWorld::animal_move(Animal* animal, IToroidalMovingAnimal* self, float tile_width, float tile_height) {
    int dr, dc;

    self->turn();
    self->move(&dr, &dc);

    if ((fxabs(dr) > 1) || (fxabs(dc) > 1)) {
        this->move(animal, dc * tile_width, dr * tile_height);
    } else {
        this->glide(self->pace_duration(), animal, dc * tile_width, dr * tile_height);
    }
}

void WarGrey::STEM::EvolutionWorld::clear_dead_animals() {
    std::for_each(this->animals.begin(), this->animals.end(),
        [&, this](Animal*& animal) {
            auto self = animal->unsafe_metadata<IToroidalMovingAnimal>();
            
            if (!self->is_alive()) {
                int r = self->current_row();
                int c = self->current_col();

                this->steppe->animal_die_at(r, c);

                this->remove(animal);
                animal = nullptr;
            }
        });

    auto it = std::remove(this->animals.begin(), this->animals.end(), static_cast<Animal*>(nullptr));
    this->animals.erase(it, this->animals.end());
}

/**************************************************************************************************/
bool WarGrey::STEM::EvolutionWorld::can_select(IMatter* m) {
    return (m == this->agent);
}

void WarGrey::STEM::EvolutionWorld::after_select(IMatter* m, bool yes) {
}

void WarGrey::STEM::EvolutionWorld::reset_world() {
    this->steppe->reset();
    this->world_info->set_text_color(FORESTGREEN);
    this->phistory->set_pen_color(ROYALBLUE);
    this->ehistory->set_pen_color(ORANGE);
    this->update_world_info();
}

/**************************************************************************************************/
bool WarGrey::STEM::EvolutionWorld::update_tooltip(IMatter* m, float lx, float ly, float gx, float gy) {
    bool updated = false;
    auto animal = dynamic_cast<Animal*>(m);

    if (animal != nullptr) {
        auto self = animal->unsafe_metadata<IToroidalMovingAnimal>();

        this->tooltip->set_text(" %s: %s ", animal->name(), self->description().c_str());
        updated = true;
    }

    return updated;
}

void WarGrey::STEM::EvolutionWorld::update_world_info() {
    int day = this->steppe->current_day();
    int n = int(this->animals.size());
    int e = this->steppe->get_total_energy();
    
    this->world_info->set_text(MatterAnchor::RB, matrics_fmt, day, n, e);
    this->phistory->push_back_datum(float(day), float(n));
    this->ehistory->push_back_datum(float(day), float(e));
}
