#include <gydm_stem/bang.hpp>

/*************************************************************************************************/
namespace WarGrey::STEM {
    class Gallery : public WarGrey::STEM::TheBigBang {
        public:
            Gallery() : TheBigBang("精灵和图元陈列馆") {}

        public:
            void load(float width, float height) override;
            void reflow(float width, float height) override;

        public:
            bool can_select(WarGrey::STEM::IMatter* m) override {
                return true;
            }

        private: // 本游戏世界中的有以下物体
            WarGrey::STEM::Labellet* caption;
            WarGrey::STEM::IShapelet* raft;
            WarGrey::STEM::IShapelet* bow;
            WarGrey::STEM::IShapelet* stern;
            WarGrey::STEM::IShapelet* flag;
            WarGrey::STEM::IShapelet* mast;
            WarGrey::STEM::IShapelet* post;
            WarGrey::STEM::IShapelet* paddle;
            WarGrey::STEM::IShapelet* sea;
    };
}
