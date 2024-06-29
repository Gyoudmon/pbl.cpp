#include "game_of_life.hpp"

#include <filesystem>

using namespace GYDM;
using namespace Linguisteen;
using namespace std::filesystem;

/*************************************************************************************************/
#define DEFAULT_CONWAY_DEMO digimon_path("demo/conway/typical", ".gof")

static const int default_frame_rate = 8;
static const char* generation_fmt = "Generation: %d";

/*************************************************************************************************/
static const char AUTO_KEY = 'a';
static const char STOP_KEY = 's';
static const char PACE_KEY = 'p';
static const char EDIT_KEY = 'e';
static const char LOAD_KEY = 'l';
static const char RAND_KEY = 'r';
static const char RSET_KEY = 'z';
static const char WRTE_KEY = 'w';

static const char ordered_keys[] = { AUTO_KEY, STOP_KEY, PACE_KEY, EDIT_KEY, LOAD_KEY, WRTE_KEY, RAND_KEY, RSET_KEY };
static const uint32_t colors_for_auto[] = { GRAY, GREEN, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY };
static const uint32_t colors_for_stop[]  = { GREEN, GRAY, GREEN, GREEN, GRAY, GRAY, GRAY, GRAY };
static const uint32_t colors_for_edit[] = { GREEN, GRAY, GREEN, GRAY, GREEN, GREEN, GREEN, GREEN };

/*************************************************************************************************/
void Linguisteen::GameOfLifeWorld::load(float width, float height) {
    TheBigBang::load(width, height);

    this->load_gameboard(width, height);
    this->load_instructions(width, height);

    this->set_local_fps(default_frame_rate);
    this->load_conway_demo();
}

void Linguisteen::GameOfLifeWorld::load_gameboard(float width, float height) {
    float board_height = height - this->get_titlebar_height() * 2.0F;
    float board_width = width - this->get_titlebar_height();
    int col = fl2fxi(board_width / this->gridsize) - 1;
    int row = fl2fxi(board_height / this->gridsize) - 1;

    this->gameboard = this->insert(new ConwayLifelet(row, col, this->gridsize));
    this->generation = this->insert(new Labellet(GameFont::math(), GREEN, generation_fmt, this->gameboard->get_generation()));
}

void Linguisteen::GameOfLifeWorld::load_instructions(float width, float height) {
    this->instructions[AUTO_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 自行演化", AUTO_KEY));
    this->instructions[STOP_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 停止演化", STOP_KEY));
    this->instructions[EDIT_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 手动编辑", EDIT_KEY));
    this->instructions[RAND_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 随机重建", RAND_KEY));
    this->instructions[RSET_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 世界归零", RSET_KEY));
    this->instructions[PACE_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 单步跟踪", PACE_KEY));
    this->instructions[LOAD_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 载入范例", LOAD_KEY));
    this->instructions[WRTE_KEY] = this->insert(new Labellet(GameFont::monospace(), "%c. 保存范例", WRTE_KEY));
}

void Linguisteen::GameOfLifeWorld::reflow(float width, float height) {
    TheBigBang::reflow(width, height);

    this->move_to(this->gameboard, { width * 0.5F, (height + this->get_titlebar_height()) * 0.5F }, MatterPort::CC);
    this->move_to(this->generation, { this->gameboard, MatterPort::RT }, MatterPort::RB);

    this->move_to(this->instructions[ordered_keys[0]], { 0.0F, height }, MatterPort::LB);
    for (int idx = 1; idx < sizeof(ordered_keys) / sizeof(char); idx ++) {
        this->move_to(this->instructions[ordered_keys[idx]],
                        { this->instructions[ordered_keys[idx - 1]], MatterPort::RB },
                        MatterPort::LB, { 16.0F, 0.0F });
    }
}

void Linguisteen::GameOfLifeWorld::on_mission_start(float width, float height) {
    this->switch_game_state(GameState::Stop);
}

void Linguisteen::GameOfLifeWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    if (this->state == GameState::Auto) {
        this->pace_forward();
    }
}

/*************************************************************************************************/
bool Linguisteen::GameOfLifeWorld::can_select(IMatter* m) {
    Labellet* menu = dynamic_cast<Labellet*>(m);

    return m == this->agent
        || ((this->state == GameState::Edit)
            && (m == this->gameboard))
        || ((menu != nullptr)
            && (menu->get_foreground_color() == GREEN));
}

void Linguisteen::GameOfLifeWorld::on_tap(IMatter* matter, float x, float y) {
    if (isinstance(matter, GameOfLifelet)) {
        this->gameboard->toggle_life_at_location(x, y);
        this->instructions[WRTE_KEY]->set_text_color(GREEN);
    } else if (isinstance(matter, Labellet)) {
        for (size_t idx = 0; idx < sizeof(ordered_keys) / sizeof(char);  idx ++) {
            if (this->instructions[ordered_keys[idx]] == matter) {
                this->on_char(ordered_keys[idx], 0, 1, false);
                this->no_selected();
                break;
            }
        }
    }
}

void Linguisteen::GameOfLifeWorld::on_char(char key, uint16_t modifiers, uint8_t repeats, bool pressed) {
    if (!pressed) {
        if (this->instructions.find(key) != this->instructions.end()) {
            if (this->instructions[key]->get_foreground_color() == GREEN) {
                switch(key) {
                case AUTO_KEY: this->switch_game_state(GameState::Auto); break;
                case STOP_KEY: this->switch_game_state(GameState::Stop); break;
                case EDIT_KEY: this->switch_game_state(GameState::Edit); break;
                case RAND_KEY: this->agent->play_writing(1); this->gameboard->construct_random_world(); break;
                case RSET_KEY: this->agent->play_empty_trash(1); this->gameboard->reset(); break;
                case PACE_KEY: this->agent->play_processing(1); this->pace_forward(); break;
                case LOAD_KEY: this->agent->play_searching(1); this->load_conway_demo(); break;
                case WRTE_KEY: this->agent->play_print(1); this->save_conway_demo(); break;
                }

                this->notify_updated();
            } else {
                this->instructions[key]->set_text_color(CRIMSON);
            }
        }
    }
}

void Linguisteen::GameOfLifeWorld::on_save(const std::string& life_world, std::ofstream& golout) {
    this->gameboard->save(life_world, golout);
}

/*************************************************************************************************/
void Linguisteen::GameOfLifeWorld::pace_forward() {
    if (this->gameboard->pace_forward()) {
        this->generation->set_text_color(GREEN);
        this->generation->set_text(MatterPort::RB, generation_fmt, this->gameboard->get_generation());
    } else {
        this->generation->set_text_color(ORANGE);
        this->generation->set_text(MatterPort::RB, generation_fmt, this->gameboard->get_generation());
        
        if (this->state == GameState::Auto) {
            this->switch_game_state(GameState::Stop);
        }
    }
}

void Linguisteen::GameOfLifeWorld::load_conway_demo() {
    if (!exists(this->demo_path)) {
        this->demo_path = DEFAULT_CONWAY_DEMO;
    }
    
    try {
        std::ifstream golin;

        golin.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        golin.open(this->demo_path);
        this->gameboard->load(this->demo_path, golin);
        golin.close();
    } catch (std::ifstream::failure &e) {
        this->instructions[LOAD_KEY]->set_text_color(FIREBRICK);
        printf("Failed to load the demo: %s\n", e.what());
    }
}

void Linguisteen::GameOfLifeWorld::save_conway_demo() {
    if (!exists(this->demo_path)) {
        this->demo_path = DEFAULT_CONWAY_DEMO;
    }
    
    try {
        std::ofstream golout;

        golout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        golout.open(this->demo_path);
        this->gameboard->save(this->demo_path, golout);
        golout.close();
        this->instructions[WRTE_KEY]->set_text_color(ROYALBLUE);
    } catch (std::ifstream::failure &e) {
        this->instructions[WRTE_KEY]->set_text_color(FIREBRICK);
        printf("Failed to save the demo: %s\n", e.what());
    }
}

/*************************************************************************************************/
void Linguisteen::GameOfLifeWorld::switch_game_state(GameState new_state) {
    if (this->state != new_state) {
        switch (new_state) {
        case GameState::Auto: {
            this->gameboard->set_color(LIGHTSKYBLUE);
            this->gameboard->show_grid(false);
            this->agent->play_thinking(8);
            this->update_instructions_state(colors_for_auto);
        }; break;
        case GameState::Stop: {
            this->gameboard->set_color(DIMGRAY);
            this->agent->play_rest_pose(1);
            this->update_instructions_state(colors_for_stop);
        }; break;
        case GameState::Edit: {
            this->gameboard->set_color(ROYALBLUE);
            this->gameboard->show_grid(true);
            this->agent->play_writing(-1);
            this->update_instructions_state(colors_for_edit);
        }; break;
        default: /* 什么都不做 */; break;
        }

        this->state = new_state;
        this->notify_updated();
    }
}

void Linguisteen::GameOfLifeWorld::update_instructions_state(const uint32_t* colors) {
    for (size_t idx = 0; idx < sizeof(ordered_keys) / sizeof(char);  idx ++) {
        this->instructions[ordered_keys[idx]]->set_text_color(colors[idx]);
    }
}
