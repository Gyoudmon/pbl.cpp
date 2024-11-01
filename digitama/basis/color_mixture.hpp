#pragma once // 确保只被 include 一次

#include <plteen/bang.hpp>

namespace Linguisteen {
    class ColorMixtureWorld : public Plteen::TheBigBang {
    public:
        ColorMixtureWorld() : TheBigBang("混色模型", GHOSTWHITE) {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(Plteen::IMatter* m) override { return true; }

    protected: // 覆盖鼠标事件处理方法
        void after_select(Plteen::IMatter* m, bool yes) override;
        void on_tap_selected(Plteen::IMatter* m, float x, float y) override { this->no_selected(); }

    private:
        Plteen::Circlet* red;
        Plteen::Circlet* green;
        Plteen::Circlet* blue;

    private:
        Plteen::Rectanglet* half_white;
        Plteen::Circlet* cyan;
        Plteen::Circlet* yellow;
        Plteen::Circlet* magenta;
    };
}
