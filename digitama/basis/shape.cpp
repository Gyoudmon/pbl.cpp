#include "shape.hpp"           // 导入本模块自己的头文件

using namespace GYDM;        // 声明本模块的类和函数默认以 GYDM 的名义使用，或者
using namespace Linguisteen; //                     以 Linguisteen 的名义使用

/*************************************************************************************************/
// 实现 ShapeWorld::load 方法，在舞台上加入基础几何图形的实例，注意添加顺序
void Linguisteen::ShapeWorld::load(float width, float height) {
    // 调用父类的同名方法加载标题和小猫助手
    TheBigBang::load(width, height);

    // 苍绿色院子
    this->garden = this->insert(new Ellipselet(200, 80, PALEGREEN, KHAKI));
    
    // 房屋部件
    this->roof = this->insert(new RegularPolygonlet(3, 140.0F, -90.0F, DEEPSKYBLUE, ROYALBLUE)); // 深空蓝屋顶
    this->wall = this->insert(new Rectanglet(200, 180, WHITESMOKE, SNOW));                       // 白色墙壁
    this->door = this->insert(new Rectanglet(42, 84, KHAKI, DARKKHAKI));                         // 卡其色门
    this->lock = this->insert(new Circlet(4, CHOCOLATE));                                        // 巧克力色门锁
    this->window = this->insert(new RoundedSquarelet(64, -0.15F, LIGHTSKYBLUE, SKYBLUE));        // 天蓝色窗户
}

// 实现 ShapeWorld::reflow 方法，重新排列几何图形在舞台上的位置
void Linguisteen::ShapeWorld::reflow(float width, float height) {
    // 调用父类的同名方法排列标题和小猫助手
    TheBigBang::reflow(width, height);

    // 排列基本图形以组装房屋
    this->move_to(this->roof, Position(width * 0.50F, height * 0.50F), MatterAnchor::CB);
    this->move_to(this->wall, Position(this->roof, MatterAnchor::CB), MatterAnchor::CT);
    this->move_to(this->door, Position(this->wall, MatterAnchor::RB), MatterAnchor::RB, Vector(-24.0F, 0.0F));
    this->move_to(this->lock, Position(this->door, MatterAnchor::RC), MatterAnchor::RC, Vector(-4.0F, 0.0F));
    this->move_to(this->window, Position(this->wall, MatterAnchor::CC), MatterAnchor::RC);

    // 排列院子
    this->move_to(this->garden, Position(this->wall, MatterAnchor::CC), MatterAnchor::CT);
}
