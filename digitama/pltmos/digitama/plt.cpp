#include "plt.hpp"

#include "../../big_bang/bang.hpp"
#include "../../big_bang/datum/string.hpp"

using namespace WarGrey::STEM;
using namespace WarGrey::PLT;

/*************************************************************************************************/
static const char* title_fmt = "%s程序语言理论: %s";
static const char* plt_name_prefix = "[λ]";

/*************************************************************************************************/
bool WarGrey::PLT::is_plt_plane_name(const char* name) {
    return (name != nullptr) && string_prefix(name, plt_name_prefix);
}

WarGrey::PLT::ThePLTPlane::ThePLTPlane(const char* name)
    : WarGrey::STEM::Plane(std::string().append(plt_name_prefix).append(name)) {}
            
void WarGrey::PLT::ThePLTPlane::load(float width, float height) {
    this->title = this->insert(new Labellet(GameFont::Title(), BLACK, title_fmt, plt_name_prefix, this->name() + strlen(plt_name_prefix)));
    this->agent = this->insert(new Linkmon());
    this->tooltip = this->insert(make_label_for_tooltip(GameFont::Tooltip()));

    this->move_to(this->title, this->agent, MatterAnchor::RB, MatterAnchor::LB);

    this->agent->scale(-1.0F, 1.0F);
    this->set_sentry_sprite(this->agent);
    this->set_tooltip_matter(this->tooltip);
}

bool WarGrey::PLT::ThePLTPlane::update_atlas_position_for_tooltip(IMatter* m, float x, float y) {
    bool updated = false;
    GridAtlas* atlas = dynamic_cast<GridAtlas*>(m);

    if (atlas != nullptr) {
        int row, col;

        atlas->map_tile_index(x, y, &row, &col);
        this->tooltip->set_text(" (%d, %d) ", row, col);
        updated = true;
    }

    return updated;
}
