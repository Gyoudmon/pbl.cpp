#pragma once // 确保只被 include 一次

#include <plteen/bang.hpp>

#include <vector>

namespace Linguisteen {
    class ColorWheelWorld : public Plteen::TheBigBang {
    public:
        ColorWheelWorld() : TheBigBang("色相环", 0xFFFFFFU) {}
        virtual ~ColorWheelWorld() {}
        
    public:
        void load(float width, float height) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(Plteen::IMatter* m) override { return (dynamic_cast<Plteen::Circlet*>(m) != nullptr) || (m == this->agent); }
        void after_select(Plteen::IMatter* m, bool yes) override;
        bool update_tooltip(Plteen::IMatter* m, float x, float y, float gx, float gy) override;

    private:
        void load_hues();
        void reflow_primaries(float x, float y);

    private:
        std::vector<Plteen::Circlet*> hues;
        std::vector<Plteen::Ellipselet*> primaries;

    private:
        size_t selection_seq = 0; 
    };
}
