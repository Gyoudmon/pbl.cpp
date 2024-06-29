#include "color_mixture.hpp"

using namespace GYDM;
using namespace Linguisteen;

/*************************************************************************************************/
static const float radius = 100.0F;
static const float gliding_duration = 2.0F;

/*************************************************************************************************/
void Linguisteen::ColorMixtureWorld::load(float width, float height) {
    TheBigBang::load(width, height);

    /* 思考：为什么背景一定要是黑色的？ */
    this->set_background(0x000000U);

    this->half_white = this->insert(new Rectanglet(width * 0.5F, height, 0xFFFFFFU));
    this->half_white->camouflage(true);

    this->red = this->insert(new Circlet(radius, 0xFF0000U));   // 红色
    this->green = this->insert(new Circlet(radius, 0x00FF00U)); // 绿色
    this->blue = this->insert(new Circlet(radius, 0x0000FFU));  // 蓝色

    /* 设置混色模式，RGB 属加色模型 */
    this->red->set_color_mixture(ColorMixture::Add);
    this->green->set_color_mixture(ColorMixture::Add);
    this->blue->set_color_mixture(ColorMixture::Add);

    this->cyan = this->insert(new Circlet(radius, 0x00FFFFU));    // 青色
    this->magenta = this->insert(new Circlet(radius, 0xFF00FFU)); // 品红
    this->yellow = this->insert(new Circlet(radius, 0xFFFF00U));  // 黄色

    /* 设置混色模式，CYMK 属减色模型，但实际计算为乘法 */
    this->cyan->set_color_mixture(ColorMixture::Subtract);
    this->magenta->set_color_mixture(ColorMixture::Multiply);
    this->yellow->set_color_mixture(ColorMixture::Multiply);
}

void Linguisteen::ColorMixtureWorld::reflow(float width, float height) {
    TheBigBang::reflow(width, height);

    this->move_to(this->half_white, { width * 0.5F, 0.0F }, MatterPort::LT);

    this->move_to(this->green, { 0.0F, height * 0.5F }, MatterPort::LC);
    this->move_to(this->red, { this->green, MatterPort::CT }, MatterPort::CB);
    this->move_to(this->blue, { this->green, MatterPort::CB }, MatterPort::CT);

    this->move_to(this->magenta, { width, height * 0.5F }, MatterPort::RC);
    this->move_to(this->cyan, { this->magenta, MatterPort::CT }, MatterPort::CB);
    this->move_to(this->yellow, { this->magenta, MatterPort::CB }, MatterPort::CT);
}

void Linguisteen::ColorMixtureWorld::after_select(IMatter* m, bool yes) {
    if (!yes) {
        if (!this->is_colliding_with_mouse(m)) {
            auto rgb = dynamic_cast<Circlet*>(m);

            if (rgb != nullptr) {
                this->glide_to_mouse(gliding_duration, rgb, MatterPort::CC);
            }
        }
    }
}
