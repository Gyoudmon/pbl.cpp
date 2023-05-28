#pragma once // 确保只被 include 一次

#include "../big_bang/bang.hpp"
#include "../big_bang/matter/graphlet/chromalet.hpp"

#include <vector>

namespace WarGrey::STEM {
    class ChromaticityDiagramWorld : public WarGrey::STEM::TheBigBang {
    public:
        ChromaticityDiagramWorld() : TheBigBang("色度图", 0xFFFFFFU) {}
        virtual ~ChromaticityDiagramWorld() {}
        
    public:
        void load(float width, float height) override;
        void update(uint64_t interval, uint32_t count, uint64_t uptime) override;
        void reflow(float width, float height) override;

    public:
        bool can_select(IMatter* m) override;
        void after_select(IMatter* m, bool yes) override;
        bool update_tooltip(IMatter* m, float lx, float ly, float gx, float gy) override;

    private:
        void reflow_primaries(float x, float y);

    private:
        std::vector<WarGrey::STEM::Circlet*> hues;
        std::vector<WarGrey::STEM::Ellipselet*> primaries;
        WarGrey::STEM::Chromalet* chroma_dia;

    private:
        size_t selection_seq = 0; 
    };
}
