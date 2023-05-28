#include "stream.hpp"

#include "../big_bang/bang.hpp"
#include "../big_bang/graphics/text.hpp"

#include <filesystem>

using namespace WarGrey::STEM;
using namespace WarGrey::PLT;

using namespace std::filesystem;

/*************************************************************************************************/
#define WATERFALL_PATH digimon_path("scene/waterfall", "", "digitama/pltmos/stone")
#define CLOUD_PATH digimon_path("scene/cloud", ".png", "digitama/pltmos/stone")
#define SIGNS_PATH digimon_path("scene/signs", "", "digitama/pltmos/stone")
#define FILTER_PATH digimon_path("scene/filter", "", "digitama/pltmos/stone")

static const int FALL_FPS = 16;
static const float CHAR_FALL_SPEED = 8.0F;
static const float LINE_CHAR_FALL_SPEED = 16.0F;
static const float LINE_FALL_SPEED = 2.0F;

static const MarioPipeColor closed_char_pipe_color = MarioPipeColor::Gray;
static const MarioPipeColor open_char_pipe_color = MarioPipeColor::Green;
static const MarioPipeColor closed_line_pipe_color = MarioPipeColor::Gray;
static const MarioPipeColor open_line_pipe_color = MarioPipeColor::Blue;

static const char* file_closed_filter_tooltip = "请先“打开”输入流管道";
static const char* file_closed_pipe_tooltip = "打开输入流管道";
static const char* file_open_tooltip = "输入流管道就绪，已读取";
static const char* file_failure_tooltip = "输入流打开失败";
static const char* file_eof_tooltip = "管道流已见底，别忘了“关闭”它";

/*************************************************************************************************/
WarGrey::PLT::StreamPlane::StreamPlane(const char* spath) : ThePLTPlane("流"), stream_source(spath) {
    if (exists(path(spath))) {
        this->stream_source = spath;
    } else {
        this->stream_source = digimon_path("pltmos/tamer/stream", ".in", "digitama");
    }

    this->stream_source_size = float(file_size(this->stream_source));
    this->set_local_fps(FALL_FPS);
}

void WarGrey::PLT::StreamPlane::load(float width, float height) {
    this->ground = this->insert(new MarioGroundAtlas(1U, 3, 75));
    this->underground = this->insert(new MarioGroundAtlas(11U, 1, 75));

    this->char_port = this->insert(new StreamSprite("waterfall1", 0.0F, 0.67F));
    this->line_port = this->insert(new StreamSprite("waterfall1", 0.0F, 0.67F));
    this->char_fall = this->insert(new StreamSprite("waterfall0", 32.0F, 3.0F));
    this->line_fall = this->insert(new StreamSprite("waterfall0", 32.0F, 3.0F));

    this->char_pipe = this->insert(new MarioVPipe(5, MarioVPipeDirection::Both, closed_char_pipe_color));
    this->line_pipe = this->insert(new MarioVPipe(5, MarioVPipeDirection::Both, closed_line_pipe_color));

    this->char_cloud = this->insert(new Sprite(CLOUD_PATH));
    this->line_cloud = this->insert(new Sprite(CLOUD_PATH));
    this->char_sign = this->insert(new Sprite(SIGNS_PATH));
    this->line_sign = this->insert(new Sprite(SIGNS_PATH));
    this->char_filter = this->insert(new Sprite(FILTER_PATH));
    this->line_filter = this->insert(new Sprite(FILTER_PATH));

    this->char_label = this->insert(new Labellet(GameFont::Default(FontSize::small), GHOSTWHITE, "[raw]"));
    this->line_label = this->insert(new Labellet(GameFont::Default(FontSize::small), GHOSTWHITE, "getline"));

    ThePLTPlane::load(width, height);
    this->set_background(LIGHTSKYBLUE);
    this->char_port->scale(1.0F, -1.0F);
    this->line_port->scale(1.0F, -1.0F);
    this->char_cloud->scale(0.5F);
    this->line_cloud->scale(0.5F);
    this->char_filter->scale(-0.5F, 0.5F);
    this->line_filter->scale(0.5F, 0.5F);
}

void WarGrey::PLT::StreamPlane::reflow(float width, float height) {
    float distance = generic_font_size(FontSize::xx_large) * 4.0F;
    float char_pos = 0.25F;
    float line_pos = 1.0F - char_pos;

    this->move_to(this->ground, width * 0.5F, height * 0.32F, MatterAnchor::CC);
    this->move_to(this->underground, width * 0.5F, height, MatterAnchor::CB);

    this->move_to(this->char_pipe, this->ground, char_pos, 0.5F, MatterAnchor::CC);
    this->move_to(this->line_pipe, this->ground, line_pos, 0.5F, MatterAnchor::CC);
    this->move_to(this->char_sign, this->ground, char_pos - 0.07F, 0.00F, MatterAnchor::CB);
    this->move_to(this->line_sign, this->ground, line_pos + 0.07F, 0.00F, MatterAnchor::CB);

    this->move_to(this->char_filter, this->char_pipe, MatterAnchor::CB, MatterAnchor::CT, 0.0F, distance);
    this->move_to(this->line_filter, this->line_pipe, MatterAnchor::CB, MatterAnchor::CT, 0.0F, distance);
    this->move_to(this->char_label, this->char_filter, MatterAnchor::RC, MatterAnchor::LC);
    this->move_to(this->line_label, this->line_filter, MatterAnchor::LC, MatterAnchor::RC);

    this->move_to(this->char_fall, this->char_pipe, MatterAnchor::CT, MatterAnchor::CB);
    this->move_to(this->line_fall, this->line_pipe, MatterAnchor::CT, MatterAnchor::CB);
    
    this->move_to(this->char_port, this->char_fall, MatterAnchor::CT, MatterAnchor::CC);
    this->move_to(this->line_port, this->line_fall, MatterAnchor::CT, MatterAnchor::CC);
    this->move_to(this->char_cloud, this->char_fall, MatterAnchor::CT, MatterAnchor::CC);
    this->move_to(this->line_cloud, this->line_fall, MatterAnchor::CT, MatterAnchor::CC);
}

void WarGrey::PLT::StreamPlane::update(uint64_t count, uint32_t interval, uint64_t uptime) {
    /***************************************** chars *********************************************/
    if (this->char_port->in_playing()) {
        auto ch = this->charin.get();

        if (ch == EOF) {
            this->char_fall->close();
            this->char_port->pause();
            this->char_filter->switch_to_next_costume();
            this->agent_rest();
        } else {
            auto chlet = this->insert(new Labellet(GameFont::monospace(), CHOCOLATE, "%c", ch));

            this->move_to(chlet, this->char_pipe, MatterAnchor::CB, MatterAnchor::CT, 0.0F, -CHAR_FALL_SPEED);
            chlet->set_velocity(CHAR_FALL_SPEED, 90.0F);
            this->chars.push_back(chlet);
        }
    }

    while (!this->chars.empty()) {
        auto chlet = this->chars.front();

        if (this->is_colliding(chlet, this->underground)) {
           this->chars.pop_front();
           this->remove(chlet);
        } else {
            break;
        }
    }

    for (auto chlet : this->chars) {
        if (this->is_colliding(chlet, this->char_filter)) {
            this->move_to(chlet, this->char_filter, MatterAnchor::CB, MatterAnchor::CT, 0.0F, -CHAR_FALL_SPEED);
        }
    }

    /***************************************** lines *********************************************/
    if (this->line_fall->in_playing()) {
       auto ch = this->linein.get();

        if (ch == EOF) {
            this->line_fall->close();
            this->line_port->pause();
            this->line_filter->switch_to_next_costume();
            this->agent_rest();
        } else {
            auto chlet = this->insert(new Labellet(GameFont::monospace(), CHOCOLATE, "%c", ch));

            this->move_to(chlet, this->line_pipe, MatterAnchor::CB, MatterAnchor::CT, 0.0F, -LINE_CHAR_FALL_SPEED);
            chlet->set_velocity(LINE_CHAR_FALL_SPEED, 90.0F);
            this->line_chars.push_back(chlet);
        }
    }

    while (!this->lines.empty()) {
        auto linelet = this->lines.front();

        if (this->is_colliding(linelet, this->underground)) {
           this->lines.pop_front();
           this->remove(linelet);
        } else {
            break;
        }
    }

    while (!this->line_chars.empty()) {
        auto chlet = this->line_chars.front();

        if (this->is_colliding(chlet, this->line_filter)) {
            const char* ch = chlet->c_str();

            if ((ch[0] == '\r') || (ch[0] == '\n')) {
                if (!this->stream_buffer.empty()) {
                    auto linelet = this->insert(new Labellet(GameFont::Default(FontSize::small), CHOCOLATE, "%s", this->stream_buffer.c_str()));

                    this->stream_buffer.clear();
                    this->lines.push_back(linelet);
                    this->move_to(linelet, this->line_filter, MatterAnchor::CB, MatterAnchor::CT, 0.0F, -LINE_FALL_SPEED);
                    linelet->set_velocity(LINE_FALL_SPEED, 90.0F);
                }
            } else {
                this->stream_buffer.append(ch);
            }
            
            this->line_chars.pop_front();
            this->remove(chlet);
        } else {
            break;
        }
    }
}

void WarGrey::PLT::StreamPlane::on_mission_start(float width, float height) {
    this->char_port->close();
    this->char_fall->close();
    this->char_cloud->show(true);
    this->char_sign->switch_to_costume("rightdown");
    this->char_filter->switch_to_costume("off");
    this->char_pipe->set_color(closed_char_pipe_color);

    this->line_port->close();
    this->line_fall->close();
    this->line_cloud->show(true);
    this->line_sign->switch_to_costume("leftdown");
    this->line_filter->switch_to_costume("off");
    this->line_pipe->set_color(closed_line_pipe_color);
}

bool WarGrey::PLT::StreamPlane::can_select(IMatter* m) {
    return ThePLTPlane::can_select(m)
            || (dynamic_cast<MarioPipe*>(m) != nullptr)
            || (m == this->char_filter)
            || (m == this->line_filter);
}

void WarGrey::PLT::StreamPlane::after_select(IMatter* m, bool yes) {
    if (yes) {
        if (m == this->char_pipe) {
            switch (this->char_pipe->get_color()) {
                case closed_char_pipe_color: {
                    this->char_port->open();
                    this->char_fall->open();
                    this->char_cloud->show(false);

                    this->charin.open(this->stream_source);

                    if (!this->charin.fail()) {
                        this->char_pipe->set_color(open_char_pipe_color);
                    } else {
                        this->char_pipe->set_color(MarioPipeColor::Red);
                    }
                }; break;
                case open_char_pipe_color: {
                    this->char_pipe->set_color(closed_char_pipe_color);
                    this->char_port->close();
                    this->char_fall->close();
                    this->char_filter->switch_to_costume("off");
                    this->char_cloud->show(true);
                    this->charin.close();
                };
                default: { /* ignore */ }
            }
        } else if (m == this->line_pipe) {
            switch (this->line_pipe->get_color()) {
                case closed_line_pipe_color: {
                    this->line_port->open();
                    this->line_fall->open();
                    this->line_cloud->show(false);

                    this->linein.open(this->stream_source);
                    this->stream_buffer.clear();

                    if (!this->linein.fail()) {
                        this->line_pipe->set_color(open_line_pipe_color);
                    } else {
                        this->line_pipe->set_color(MarioPipeColor::Red);
                    }
                }; break;
                case open_line_pipe_color: {
                    this->line_pipe->set_color(closed_line_pipe_color);
                    this->line_port->close();
                    this->line_fall->close();
                    this->line_filter->switch_to_costume("off");
                    this->line_cloud->show(true);
                    this->linein.close();
                };
                default: { /* ignore */ }
            }
        } else if (m == this->char_filter) {
            if (this->char_pipe->get_color() == open_char_pipe_color) {
                this->char_filter->switch_to_next_costume();

                if (strcmp(this->char_filter->current_costume_name(), "on") == 0) {
                    this->char_fall->flow();
                    this->char_port->flow();
                    this->agent->play_print();
                } else {
                    this->char_fall->pause();
                    this->char_port->pause();
                    this->agent_rest();
                }
            }
        } else if (m == this->line_filter) {
            if (this->line_pipe->get_color() == open_line_pipe_color) {
                this->line_filter->switch_to_next_costume();
            
                if (strcmp(this->line_filter->current_costume_name(), "on") == 0) {
                    this->line_fall->flow();
                    this->line_port->flow();
                    this->agent->play_print();
                } else {
                    this->line_fall->pause();
                    this->line_port->pause();
                    this->agent_rest();
                }
            }
        }

        this->no_selected();
    }
}

bool WarGrey::PLT::StreamPlane::update_tooltip(IMatter* m, float x, float y, float gx, float gy) {
    bool updated = false;

    if (m == this->char_pipe) {
        updated = this->update_pipe_status(this->charin, this->char_pipe, closed_char_pipe_color);
    } else if (m == this->line_pipe) {
        updated = this->update_pipe_status(this->linein, this->line_pipe, closed_line_pipe_color);
    } else if (m == this->char_filter) {
        if (this->char_pipe->get_color() != open_char_pipe_color) {
            this->tooltip->set_text(ORANGE, " %s ", file_closed_filter_tooltip);
            updated = true;
        } else {
            updated = this->update_progress(this->charin, "按字节读取，已完成");
        }
    } else if (m == this->line_filter) {
        if (this->line_pipe->get_color() != open_line_pipe_color) {
            this->tooltip->set_text(ORANGE, " %s ", file_closed_filter_tooltip);
            updated = true;
        } else {
            updated = this->update_progress(this->linein, "按行读取，已完成");
        }
    } else if ((m == this->char_port) || (m == this->char_fall)) {
        updated = this->update_progress(this->charin, "已读取");
    } else if ((m == this->line_port) || (m == this->line_fall)) {
        updated = this->update_progress(this->linein, "已读取");
    }

    return updated;
}

bool WarGrey::PLT::StreamPlane::update_pipe_status(std::ifstream& in, MarioVPipe* pipe, MarioPipeColor closed_color) {
    if (pipe->get_color() == closed_color) {
        this->tooltip->set_text(GREEN, " %s ", file_closed_pipe_tooltip);
    } else if (!in.fail() || in.eof()) {
        if (!this->update_progress(in, file_open_tooltip)) {
            this->tooltip->set_text(CRIMSON, " %s ", file_eof_tooltip);
        }
    } else {
        this->tooltip->set_text(FIREBRICK, " %s ", file_failure_tooltip);
    }

    return true;
}

bool WarGrey::PLT::StreamPlane::update_progress(std::ifstream& in, const char* message) {
    bool updated = false;

    if (in.is_open()) {
        auto pos = in.tellg();

        if (pos >= 0) {
            float percentage = 100.0F;

            if (this->stream_source_size > 0) {
                percentage = float(pos) / float(this->stream_source_size) * 100.0F;
            }

            this->tooltip->set_text(DODGERBLUE, " %s%.02f%% ", message, percentage);
            updated = true;
        }
    }

    return updated;
}

void WarGrey::PLT::StreamPlane::agent_rest() {
    if ((strcmp(this->char_filter->current_costume_name(), "off") == 0)
        && (strcmp(this->line_filter->current_costume_name(), "off") == 0)) {
        this->agent->stop();
    }
}

/*************************************************************************************************/
WarGrey::PLT::StreamSprite::StreamSprite(const char* action, float width, float ratio)
    : Sprite(WATERFALL_PATH), action(action), width(width), ratio(ratio) {}

void WarGrey::PLT::StreamSprite::construct(SDL_Renderer* renderer) {
    Sprite::construct(renderer);

    this->switch_to_costume(this->action);
    
    if ((this->width > 0.0F) && (this->ratio > 0.0F)) {
        this->resize(this->width, this->width * this->ratio);
    }
}

void WarGrey::PLT::StreamSprite::open() {
    this->show(true);
    this->switch_to_costume(this->action);
}

void WarGrey::PLT::StreamSprite::flow() {
    this->play(this->action);
}

void WarGrey::PLT::StreamSprite::pause() {
    this->stop();    
}

void WarGrey::PLT::StreamSprite::close() {
    this->stop();
    this->show(false);
}
