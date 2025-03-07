#include "color_wheel.hpp"

using namespace Plteen;
using namespace Linguisteen;

/*************************************************************************************************/
static const size_t hue_count = 36U;
static const float hue_radius = 16.0F;
static const float wheel_radius = 360.0F;

static const float primary_radius = 100.0F;

/*************************************************************************************************/
void Linguisteen::ColorWheelWorld::load(float width, float height) {
    this->set_background(0x000000U);

    this->primaries.push_back(this->insert(new Ellipselet(primary_radius, 0xFF0000U)));
    this->primaries.push_back(this->insert(new Ellipselet(primary_radius, 0x00FF00U)));
    this->primaries.push_back(this->insert(new Ellipselet(primary_radius, 0x0000FFU)));

    for (auto com : this->primaries) {
        com->set_color_mixture(ColorMixture::Add);
    }

    this->load_hues();
    TheBigBang::load(width, height);
}

void Linguisteen::ColorWheelWorld::reflow(float width, float height) {
    float cx = width * 0.5F;
    float cy = height * 0.55F;
    float x, y;

    for (auto c : this->hues) {
        circle_point(wheel_radius, float(c->get_brush_color().hue()) - 90.0F, &x, &y, false);
        this->move_to(c, { cx + x, cy + y }, MatterPort::CC);
    }

    this->reflow_primaries(cx, cy);
    
    TheBigBang::reflow(width, height);
}

void Linguisteen::ColorWheelWorld::after_select(IMatter* m, bool yes) {
    if (yes) {
        auto com = dynamic_cast<Circlet*>(m);

        if (com != nullptr) {
            this->primaries[this->selection_seq]->set_brush_color(com->get_brush_color());
            this->selection_seq = (this->selection_seq + 1) % this->primaries.size();
        }
    }
}

bool Linguisteen::ColorWheelWorld::update_tooltip(IMatter* m, float x, float y, float gx, float gy) {
    bool updated = false;
    auto com = dynamic_cast<Circlet*>(m);
    auto cc = dynamic_cast<Ellipselet*>(m);

    if (com != nullptr) {
        RGBA brush = com->get_brush_color();

        this->tooltip->set_text(" #%06X [Hue: %.2f] ", brush.rgb(), brush.hue());
        this->no_selected();
        updated = true;
    } else if (cc != nullptr) {
        RGBA c = 0U;

        for (size_t idx = 0; idx < this->primaries.size(); idx ++) {
            Point<float> dot = this->get_matter_location(this->primaries[idx], MatterPort::CC);

            if (point_distance(gx, gy, dot.x, dot.y) <= primary_radius) {
                c = c + this->primaries[idx]->get_brush_color();
            }
        }

        this->tooltip->set_text(c.hexstring(false));
        updated = true;
    }

    return updated;
}

/*************************************************************************************************/
void Linguisteen::ColorWheelWorld::load_hues() {
    float delta_deg = 360.0F / float(hue_count);
    float deg = 0.0F;

    while (deg < 360.0F) {
        this->hues.push_back(this->insert(new Circlet(hue_radius, RGBA::HSV(deg))));
        deg += delta_deg;
    }
}

void Linguisteen::ColorWheelWorld::reflow_primaries(float x, float y) {
    float cc_off = primary_radius * 0.5F;
    
    this->move_to(this->primaries[0], { x, y }, MatterPort::CB, { 0.0F, cc_off });
    this->move_to(this->primaries[1], { this->primaries[0], MatterPort::CB }, MatterPort::RC, { cc_off, 0.0F });
    this->move_to(this->primaries[2], { this->primaries[1], MatterPort::CC }, MatterPort::LC);
}
