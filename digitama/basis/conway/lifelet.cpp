#include "lifelet.hpp"

#include <gydm_stem/graphics/image.hpp>
#include <gydm_stem/physics/random.hpp>

using namespace WarGrey::STEM;

/*************************************************************************************************/
static inline int count_in_neighbor(int* world[], int row, int col, int r, int c) {
    return ((r >= 0) && (r < row)
            && (c >= 0) && (c < col)
            && (world[r][c] > 0))
        ? 1 : 0;
}

static inline int count_neighbors(int *world[], int row, int col, int r, int c) {
    return count_in_neighbor(world, row, col, r - 1, c + 0)  // up
         + count_in_neighbor(world, row, col, r + 1, c + 0)  // down
         + count_in_neighbor(world, row, col, r + 0, c - 1)  // left
         + count_in_neighbor(world, row, col, r + 0, c + 1)  // right
         + count_in_neighbor(world, row, col, r - 1, c - 1)  // left-up
         + count_in_neighbor(world, row, col, r + 1, c + 1)  // right-down
         + count_in_neighbor(world, row, col, r + 1, c - 1)  // left-down
         + count_in_neighbor(world, row, col, r - 1, c + 1); // right-up
}

/*************************************************************************************************/
WarGrey::STEM::GameOfLifelet::~GameOfLifelet() {
    if (this->world != nullptr) {
        for (int r = 0; r < this->row; r ++) {
            delete [] this->world[r];
        }

        delete [] this->world;
    }

    if (this->shadow != nullptr) {
        delete [] this->shadow;
    }
}

void WarGrey::STEM::GameOfLifelet::construct(SDL_Renderer* renderer) {
    IGraphlet::construct(renderer);

    this->shadow = new int[this->row * this->col];
    this->world = new int*[this->row];

    for (int r = 0; r < this->row; r ++) {
        this->world[r] = new int[this->col];
    }
}

void WarGrey::STEM::GameOfLifelet::feed_extent(float x, float y, float* width, float* height) {
    SET_BOX(width, this->gridsize * float(this->col) + 1.0F);
    SET_BOX(height, this->gridsize * float(this->row) + 1.0F);
}

void WarGrey::STEM::GameOfLifelet::draw(SDL_Renderer* renderer, float x, float y, float Width, float Height) {
    RGB_SetRenderDrawColor(renderer, this->color);

    game_draw_rect(renderer, x, y, Width, Height, this->color);

    // 绘制舞台的网格
    if (!this->hide_grid) {
        game_draw_grid(renderer, this->row, this->col, this->gridsize, this->gridsize, x, y);
    }

    // 绘制生命状态
    game_fill_grid(renderer, this->world, this->row, this->col, this->gridsize, this->gridsize, x, y);
}        

void WarGrey::STEM::GameOfLifelet::toggle_life_at_location(float x, float y) {
    int c = fl2fxi(flfloor(x / this->gridsize));
    int r = fl2fxi(flfloor(y / this->gridsize));

    this->world[r][c] = (this->world[r][c] == 0) ? 1 : 0;
    this->notify_updated();
}

void WarGrey::STEM::GameOfLifelet::show_grid(bool yes) {
    if (this->hide_grid == yes) {
        this->hide_grid = !yes;
        this->notify_updated();
    }
}

void WarGrey::STEM::GameOfLifelet::set_color(uint32_t hex) {
    if (this->color != hex) {
        this->color = hex;
        this->notify_updated();
    }
}

bool WarGrey::STEM::GameOfLifelet::pace_forward() {
    bool evolved = false;

    // 应用演化规则
    this->evolve(this->world, this->shadow, this->row, this->col);

    // 同步舞台状态
    for (int r = 0; r < this->row; r ++) {
        for (int c = 0; c < this->col; c ++) {
            int state = this->shadow[r * this->col + c];

            if (this->world[r][c] != state) {
                this->world[r][c] = state;
                evolved = true;
            }
        }
    }

    if (evolved) {
        this->generation ++;
    }

    return evolved;
}

void WarGrey::STEM::GameOfLifelet::reset() {
    this->generation = 0;

    for (int r = 0; r < this->row; r ++) {
        for (int c = 0; c < this->col; c ++) {
            this->world[r][c] = 0;
        }
    }
}

void WarGrey::STEM::GameOfLifelet::construct_random_world() {
    for (int r = 0; r < this->row; r++) {
        for (int c = 0; c < this->col; c++) {
            this->world[r][c] = ((random_raw() % 2 == 0) ? 1 : 0);
        }
    }

    this->generation = 0;
}

void WarGrey::STEM::GameOfLifelet::load(const std::string& life_world, std::ifstream& golin) {
    std::string rowline;
    int r = 0;

    this->reset();

    while ((r < this->row) && std::getline(golin, rowline)) {
        for (int c = 0; c < rowline.size() && c < this->col; c ++) {
            this->world[r][c] = (rowline[c] == '0') ? 0 : 1;
        }

        r ++;
    }
}

void WarGrey::STEM::GameOfLifelet::save(const std::string& life_world, std::ofstream& golout) {
    if (world != nullptr) {
        for (int r = 0; r < this->row; r++) {
            for (int c = 0; c < this->col; c++) {
                golout << this->world[r][c];
            }
            
            golout << std::endl;
        }
    }
}

/*************************************************************************************************/
void WarGrey::STEM::ConwayLifelet::evolve(int** world, int* shadow, int row, int col) {
    for (int r = 0; r < row; r ++) {
        for (int c = 0; c < col; c ++) {
            int n = count_neighbors(world, row, col, r, c);
            int i = r * col + c;

            if (n < 2) {            // 孤独死(离群索居)
                shadow[i] = 0;
            } else if (n > 3) {     // 内卷死(过度竞争)
                shadow[i] = 0;
            } else if (n == 3) {    // 无性繁殖
                shadow[i] = 1;
            } else {                // 安居乐业
                shadow[i] = world[r][c];
            }
        }
    }
}

void WarGrey::STEM::HighLifelet::evolve(int** world, int* shadow, int row, int col) {
    for (int r = 0; r < row; r ++) {
        for (int c = 0; c < col; c ++) {
            int n = count_neighbors(world, row, col, r, c);
            int i = r * col + c;

            switch (n) {
            case 2: shadow[i] = world[r][c]; break;
            case 3: case 6: shadow[i] = 1; break;
            default: shadow[i] = 0;
            }
        }
    }
}
