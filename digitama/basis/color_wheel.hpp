#pragma once // 确保只被 include 一次

#include <gydm/bang.hpp>

#include <vector>

namespace Linguisteen {
    class ColorWheelWorld : public GYDM::TheBigBang {
    public:
        ColorWheelWorld() : TheBigBang("色相环", 0xFFFFFFU) {}
        virtual ~ColorWheelWorld() {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(GYDM::IMatter* m) override { return (dynamic_cast<GYDM::Circlet*>(m) != nullptr) || (m == this->agent); }
        void after_select(GYDM::IMatter* m, bool yes) override;
        bool update_tooltip(GYDM::IMatter* m, float x, float y, float gx, float gy) override;

    private:
        void load_hues();
        void reflow_primaries(float x, float y);

    private:
        std::vector<GYDM::Circlet*> hues;
        std::vector<GYDM::Ellipselet*> primaries;

    private:
        size_t selection_seq = 0; 
    };
}
