#pragma once // 确保只被 include 一次

// 导入宇宙大爆炸模块，内含 TheBigBang 类和常用函数
#include <plteen/bang.hpp>

// 以 Linguisteen 的名义提供
namespace Linguisteen {
    // 创建自定义数据类型，并命名为 ShapeWorld, 继承自 TheBigBang
    class ShapeWorld : public Plteen::TheBigBang {
    public:
        // 构造函数，默认什么都不做，除了通过父类构造函数设置窗口标题和帧频
        ShapeWorld() : TheBigBang("图形宇宙(对象版)") {}

        // 析构函数，默认什么都不做
        virtual ~ShapeWorld() {}
        
    public:
        // 加载游戏中的物体(包括前景、背景、建筑、游戏角色等等)
        void load(float width, float height) override;

        // 布局游戏对象，让它们待在正确的位置上
        void reflow(float width, float height) override;

    public: // 为演示该设计思路的优点，运行游戏里的物体可以被选中
        bool can_select(Plteen::IMatter* m) override { return true; }

    private: // 本游戏世界有以下物体
        Plteen::IShapelet* roof;
        Plteen::IShapelet* wall;
        Plteen::IShapelet* door;
        Plteen::IShapelet* lock;
        Plteen::IShapelet* window;
        Plteen::IShapelet* garden;
    };
}
