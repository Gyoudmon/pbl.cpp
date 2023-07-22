#pragma once // 确保只被 include 一次

#include <gydm_stem/bang.hpp>

namespace WarGrey::STEM {
    class ColorMixtureWorld : public WarGrey::STEM::TheBigBang {
    public:
        ColorMixtureWorld() : TheBigBang("混色模型", GHOSTWHITE) {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(WarGrey::STEM::IMatter* m) override { return true; }

    protected: // 覆盖鼠标事件处理方法
        void after_select(WarGrey::STEM::IMatter* m, bool yes) override;
        void on_tap_selected(WarGrey::STEM::IMatter* m, float x, float y) override { this->no_selected(); }

    private:
        WarGrey::STEM::Circlet* red;
        WarGrey::STEM::Circlet* green;
        WarGrey::STEM::Circlet* blue;

    private:
        WarGrey::STEM::Rectanglet* half_bg;
        WarGrey::STEM::Circlet* cyan;
        WarGrey::STEM::Circlet* yellow;
        WarGrey::STEM::Circlet* magenta;
    };
}
