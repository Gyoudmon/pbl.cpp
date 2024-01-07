#pragma once // 确保只被 include 一次

#include <gydm/bang.hpp>

namespace Linguisteen {
    class ColorMixtureWorld : public GYDM::TheBigBang {
    public:
        ColorMixtureWorld() : TheBigBang("混色模型", GHOSTWHITE) {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(GYDM::IMatter* m) override { return true; }

    protected: // 覆盖鼠标事件处理方法
        void after_select(GYDM::IMatter* m, bool yes) override;
        void on_tap_selected(GYDM::IMatter* m, float x, float y) override { this->no_selected(); }

    private:
        GYDM::Circlet* red;
        GYDM::Circlet* green;
        GYDM::Circlet* blue;

    private:
        GYDM::Rectanglet* half_white;
        GYDM::Circlet* cyan;
        GYDM::Circlet* yellow;
        GYDM::Circlet* magenta;
    };
}
