#include "self_avoiding_walk.hpp"

using namespace GYDM;
using namespace Linguisteen;

/*************************************************************************************************/
static const double pace_duration = 0.5;

static const GroundBlockType steppe_tile_type = GroundBlockType::Dirt;
static const GroundBlockType jungle_tile_type = GroundBlockType::Soil;
static const GroundBlockType maze_wall_type = GroundBlockType::Grass;

/*************************************************************************************************/
static inline bool is_dead_end(bool maze[MAZE_SIZE][MAZE_SIZE], int row, int col) {
    return maze[row + 0][col - 1]  // left
        && maze[row + 0][col + 1]  // right
        && maze[row - 1][col + 0]  // up
        && maze[row + 1][col + 0]; // down
}

static inline bool is_inside_maze(int row, int col) {
    return ((row >= 1) && (row < (MAZE_SIZE - 1))
             && (col >= 1) && (col < (MAZE_SIZE - 1)));
}

static void backtracking_pace(bool maze[MAZE_SIZE][MAZE_SIZE], int& row, int& col) {
    int btr = row;
    int btc = col;

    do {
        row = btr;
        col = btc;

        switch (random_uniform(0, 3) % 4) {
            case 0: row -= 1; break;
            case 1: col -= 1; break;
            case 2: row += 1; break;
            case 3: col += 1; break;
        }
    } while (maze[row][col]);
}

/*************************************************************************************************/
void Linguisteen::SelfAvoidingWalkWorld::load(float width, float height) {
    float cx = width * 0.5F;
    float cy = height * 0.5F;

    // 初始化世界
    for (int row = 0; row < MAZE_SIZE; row ++) {
        for (int col = 0; col < MAZE_SIZE; col ++) {
            this->tiles[row][col] = this->insert(new PlanetCuteTile(steppe_tile_type), cx, cy, MatterAnchor::CC);
        }
    }

    // 添加漫步者
    this->walkers[0] = this->insert(new Estelle());
    this->walkers[1] = this->insert(new Joshua());
    this->walkers[2] = this->insert(new Scherazard());
    this->walkers[3] = this->insert(new Olivier());
    this->walkers[4] = this->insert(new Agate());
    this->walkers[5] = this->insert(new Klose());
    this->walkers[6] = this->insert(new Tita());
    this->walkers[7] = this->insert(new Zin());

    /* locating */ {
        Margin margin = this->tiles[0][0]->get_map_overlay();

        this->cell_region = this->tiles[0][0]->get_bounding_box();
        this->cell_region.rbdot.x -= margin.horizon();
        this->cell_region.rbdot.y -= margin.vertical();
    }

    TheBigBang::load(width, height);
}

void Linguisteen::SelfAvoidingWalkWorld::reflow(float width, float height) {
    size_t walker_count = sizeof(this->walkers) / sizeof(Bracer*);
    float y0 = this->get_titlebar_height();
    float maze_x, maze_y;

    TheBigBang::reflow(width, height);
    this->create_grid(int(walker_count), 1, 16.0F, y0, 64.0F, float(MAZE_SIZE) * this->cell_region.height());

    // 确保游戏世界被绘制在屏幕中心
    maze_x = flround((width - float(MAZE_SIZE) * this->cell_region.width()) * 0.5F);
    maze_y = flround(((height - y0) - float(MAZE_SIZE) * this->cell_region.height()) * 0.5F + y0);

    for (int row = 0; row < MAZE_SIZE; row ++) {
        for (int col = 0; col < MAZE_SIZE; col ++) {
            float dx = maze_x + float(col + 1) * this->cell_region.width();
            float dy = maze_y + float(row + 1) * this->cell_region.height();

            this->glide_to(pace_duration, this->tiles[row][col], { dx, dy }, MatterAnchor::RB);
        }
    }
}

void Linguisteen::SelfAvoidingWalkWorld::on_mission_start(float width, float height) {
    this->reset_walkers(false);
    this->reset_maze();
    this->row = -1;
}

void Linguisteen::SelfAvoidingWalkWorld::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    if (this->row >= 0) {
        if (this->walker->current_mode() == BracerMode::Run) {
            if (this->walker->motion_stopped()) {
                // 移动, 直到走出地图或走进死胡同
                if (is_inside_maze(this->row, this->col)) {
                    if (!is_dead_end(this->maze, this->row, this->col)) {
                        int cur_r = this->row;
                        int cur_c = this->col;

                        backtracking_pace(this->maze, this->row, this->col);
                        this->maze[this->row][this->col] = true;
                        this->glide(pace_duration, this->walker,
                                        { float(this->col - cur_c) * this->cell_region.width(),
                                          float(this->row - cur_r) * this->cell_region.height() });
                    } else {
                        this->walker->switch_mode(BracerMode::Lose);                        
                    }
                } else {
                    this->walker->switch_mode(BracerMode::Win, 1);
                }
            } else if (this->is_colliding(this->walker, this->tiles[this->row][this->col], MatterAnchor::CC)) {
                if (is_inside_maze(this->row, this->col)) {
                    this->tiles[this->row][this->col]->set_type(jungle_tile_type);
                }
            }
        } else if (!this->walker->in_playing()) {
            this->row = -1;
        }
    }
}

/**************************************************************************************************/
bool Linguisteen::SelfAvoidingWalkWorld::can_select(IMatter* m) {
    return (this->row < 0) || (m == this->agent);
}

void Linguisteen::SelfAvoidingWalkWorld::after_select(IMatter* m, bool yes) {
    if (yes) {
        Bracer* bracer = dynamic_cast<Bracer*>(m);

        if (bracer != nullptr) {
            Margin margin;

            this->row = MAZE_SIZE / 2;
            this->col = MAZE_SIZE / 2;

            this->walker = bracer;
            this->walker->switch_mode(BracerMode::Run);
            this->reset_maze();

            margin = this->tiles[this->row][this->col]->get_map_overlay();
            this->move_to(this->walker, { this->tiles[this->row][this->col], MatterAnchor::CC },
                            MatterAnchor::CC, { 0.0F, -margin.bottom });
            
            this->tiles[this->row][this->col]->set_type(jungle_tile_type);
            this->maze[this->row][this->col] = true;

            this->no_selected();
        }
    }
}

void Linguisteen::SelfAvoidingWalkWorld::reset_walkers(bool keep_mode) {
    int walker_count = int(sizeof(this->walkers) / sizeof(Bracer*));
    
    for (int idx = 0; idx < walker_count; idx++) {
        this->move_to_grid(this->walkers[idx], idx, 0, MatterAnchor::CB);
        this->walkers[idx]->set_heading(90.0);

        if (!keep_mode) {
            this->walkers[idx]->switch_mode(BracerMode::Walk);
        }
    }
}

void Linguisteen::SelfAvoidingWalkWorld::reset_maze() {
    for (int row = 0; row < MAZE_SIZE; row++) {
        for (int col = 0; col < MAZE_SIZE; col++) {
            this->maze[row][col] = false;
                
            if (is_inside_maze(row, col)) {
                this->tiles[row][col]->set_type(steppe_tile_type);
            } else {
                this->tiles[row][col]->set_type(maze_wall_type);
            }
        }
    }
}

/**************************************************************************************************/
bool Linguisteen::SelfAvoidingWalkWorld::update_tooltip(IMatter* m, float lx, float ly, float gx, float gy) {
    bool updated = false;
    auto bracer = dynamic_cast<Bracer*>(m);

    if (bracer != nullptr) {
        this->tooltip->set_text(" %s ", bracer->name());
        updated = true;
    }

    return updated;
}
