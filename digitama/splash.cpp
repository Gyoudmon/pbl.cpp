#include "splash.hpp"

#include <gydm/bang.hpp>

#include <gydm/datum/string.hpp>
#include <gydm/datum/path.hpp>

using namespace Linguisteen;
using namespace GYDM;

/*************************************************************************************************/
static const float tux_speed_walk_x = 2.4F;
static const float tux_speed_jump_x = tux_speed_walk_x;
static const float tux_speed_jump_y = -12.0F;
static const float tux_speed_dy = 1.0F;

static const std::vector<std::pair<int, int>> tux_spots = {
    /* { row, col } */
    { 6, 4 },
    { 6, 14 }, { 12, 24 },
    { 17, 34 }, { 22, 44 }
};

static const std::vector<std::vector<std::pair<int, int>>> task_info = {
    { /* { row, col } */ },
    { { 11, 15 }, { 10, 18 }, { 12, 18 } },
    { { 16, 23 }, { 16, 25 }, { 16, 27 }, { 16, 29 }, { 18, 24 } },
    { { 21, 34 }, { 20, 37 }, { 22, 37 }, { 19, 40 } }
};

/*************************************************************************************************/
namespace {
    class SplashPlane : public TheBigBang {
    public:
        SplashPlane(Cosmos* master) : TheBigBang("宇宙大爆炸", GHOSTWHITE), master(master) {}

    public:  // 覆盖游戏基本方法
        void load(float width, float height) override {
            this->splash = this->insert(new GridAtlas("splash.png"));

            TheBigBang::load(width, height);
            
            this->load_tasks(width, height);
            this->tux = this->insert(new Tuxmon());

            this->tooltip = this->insert(make_label_for_tooltip(GameFont::Tooltip()));
            this->set_tooltip_matter(this->tooltip);

            this->splash->create_logic_grid(28, 45);
            // this->splash->set_logic_grid_color(DIMGRAY);

            this->set_background(BLACK);
        }
        
        void reflow(float width, float height) override {
            TheBigBang::reflow(width, height);

            this->move_to(this->title, { this->agent, MatterPort::RB }, MatterPort::LB);
            this->move_to(this->splash, { width * 0.5F, height * 0.5F }, MatterPort::CC);
            
            this->reflow_tasks(width, height);
            this->tux_home();
        }

        void update(uint64_t count, uint32_t interval, uint64_t uptime) override {
            this->tux_step(count, interval, uptime);

            if (this->target_plane > 0) {
                if (!this->agent->in_playing()) {
                    this->master->transfer_to_plane(this->target_plane);
                    this->target_plane = 0;
                }
            }
        }

        void on_mission_start(float width, float height) override {
            this->tux->set_speed(tux_speed_walk_x, 0.0F);
            this->no_selected();
        }

    public:
        bool can_select(IMatter* m) override {
            return isinstance(m, Coinlet)
                    || (m == this->tux)
                    || (m == this->agent);
        }

        void after_select(IMatter* m, bool yes) override {
            if (yes) {
                Coinlet* coin = dynamic_cast<Coinlet*>(m);

                if (coin != nullptr) {
                    if (coin->in_playing()) {
                        this->target_plane = coin->get_index();
                        this->agent->play("Hide", 1);
                    }
                }

                this->no_selected();
            }
        }

        bool update_tooltip(IMatter* m, float x, float y, float gx, float gy) override {
            bool updated = false;
            auto coin = dynamic_cast<Coinlet*>(m);

            if ((coin != nullptr) && !this->tooltip->visible()) {
                this->tooltip->set_text(coin->in_playing() ? ROYALBLUE : BLACK, " %s ", coin->name());
                updated = true;
            }

            return updated;
        }

    private:
        void load_tasks(float width, float height) {
            int task_idx = 0;

            for (int seg = 0; seg < task_info.size(); seg ++) {
                std::vector<Coinlet*> subcoins;
                std::vector<Labellet*> subnames;

                for (int idx = 0; idx < task_info[seg].size(); idx ++) {
                    const char* tooltip = this->master->plane_name(++ task_idx);

                    if (tooltip == nullptr) {
                        this->load_task(subcoins, unknown_plane_name, task_idx);
                    } else {
                        this->load_task(subcoins, tooltip, task_idx);
                    }
                }

                this->coins.push_back(subcoins);
            }

            for (int idx = task_idx + 1; idx < this->master->plane_count(); idx ++) {
                this->load_task(this->bonus_coins, this->master->plane_name(idx), idx);
            }
        }

        void load_task(std::vector<Coinlet*>& subcoins, const char* tooltip, int task_idx) {
            subcoins.push_back(this->insert(new Coinlet(tooltip, task_idx)));
            
            if (strcmp(tooltip, unknown_plane_name) == 0) {
                subcoins.back()->stop();
            }
        }

        void reflow_tasks(float width, float height) {
            for (int seg = 0; seg < task_info.size(); seg ++) {
                auto subinfos = task_info[seg];
                auto subcoins = this->coins[seg];
                
                for (int idx = 0; idx < subinfos.size(); idx ++) {
                    auto pos = subinfos[idx];

                    this->splash->move_to_logic_tile(subcoins[idx], pos.first, pos.second, MatterPort::CC, MatterPort::CC);
                }
            }

            for (size_t idx = this->bonus_coins.size(); idx > 0; idx --) {
                if (idx == this->bonus_coins.size()) {
                    this->move_to(this->bonus_coins[idx - 1], { this->splash, MatterPort::LB }, MatterPort::LB);
                } else {
                    this->move_to(this->bonus_coins[idx - 1], { this->bonus_coins[idx], MatterPort::RC }, MatterPort::LC);
                }
            }
        }
    
    private:
        void tux_home() {
            int row = tux_spots[0].first;
            int col = tux_spots[0].second;
            
            this->splash->move_to_logic_tile(this->tux, row, col, MatterPort::LB, MatterPort::CB);
            this->tux_walk_segment = 1;
            this->tux_start_walk();
        }

        void tux_start_walk() {
            this->tux->set_speed(tux_speed_walk_x, 0.0F);
            this->tux->set_delta_speed(0.0F, 0.0F);
            this->tux_target_y = 0.0F;
        }

        void tux_step(uint64_t count, uint64_t interval, uint64_t uptime) {
            Dot tdot = this->get_matter_location(this->tux, MatterPort::RB);
            Dot dot0 = this->get_matter_location(this->splash, MatterPort::LT);
            
            tdot -= dot0;

            if (this->tux_target_y == 0.0F) {
                float gx = this->get_splash_location(this->tux_walk_segment).x;

                if (tdot.x >= gx) {
                    this->tux_walk_segment += 1;
                    
                    if (this->tux_walk_segment < tux_spots.size()) {
                        this->tux_target_y = this->get_splash_location(this->tux_walk_segment).y;
                        this->tux->set_speed(tux_speed_jump_x, tux_speed_jump_y);
                        this->tux->set_delta_speed(0.0F, tux_speed_dy);
                    } else {
                        this->tux_home();
                    }
                }
            } else if (tdot.y >= this->tux_target_y) {
                this->tux_start_walk();
            }
        }

        Dot get_splash_location(size_t idx) {
            return this->splash->get_logic_tile_location(
                        tux_spots[idx].first, tux_spots[idx].second,
                        MatterPort::LB);
        }

    private:
        std::vector<std::vector<Coinlet*>> coins;
        std::vector<Coinlet*> bonus_coins;
        Labellet* tooltip;
        Sprite* tux;
        GridAtlas* splash;

    private:
        int tux_walk_segment = 1;
        float tux_target_y = 0.0F;
        
    private:
        Cosmos* master;
        int target_plane = 0;
    };
}

/*************************************************************************************************/
Linguisteen::TheCosmos::~TheCosmos() {
    imgdb_teardown();
}

void Linguisteen::TheCosmos::construct(int argc, char* argv[]) {
    GameFont::fontsize(21);
    
    enter_digimon_zone(argv[0]);

    imgdb_setup(digimon_subdir("stone"));
    
#ifdef __windows__
    digimon_appdata_setup("C:\\opt\\GYDMstem\\");
    digimon_mascot_setup("C:\\opt\\GYDMstem\\stone\\mascot");
#else
    digimon_appdata_setup("/opt/GYDMstem/");
    digimon_mascot_setup("/opt/GYDMstem/stone/mascot");
#endif
    
    this->parse_cmdline_options(argc, argv);
    
    this->splash = this->push_plane(new SplashPlane(this));
}

void Linguisteen::TheCosmos::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    if (this->has_current_mission_completed()) {
        this->transfer_to_plane(0);
    }
}

bool Linguisteen::TheCosmos::can_exit() {
    return this->splash->has_mission_completed();
}
