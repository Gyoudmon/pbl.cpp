#pragma once

#include "../../big_bang/game.hpp"

namespace WarGrey::PLT {
    bool is_plt_plane_name(const char* name);

    class ThePLTPlane : public WarGrey::STEM::Plane {
        public:
            ThePLTPlane(const char* name);
            virtual ~ThePLTPlane() {}

        public:
            void load(float width, float height) override;

        protected:
            bool update_atlas_position_for_tooltip(WarGrey::STEM::IMatter* m, float x, float y);

        protected:
            WarGrey::STEM::Linkmon* agent;
            WarGrey::STEM::Labellet* title;
            WarGrey::STEM::Labellet* tooltip;
    };
}
