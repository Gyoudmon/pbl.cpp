#include "gallery.hpp"

using namespace WarGrey::STEM;

/*************************************************************************************************/
static inline void feed_raft_size(IMatter* m, float* raft_width, float* raft_height) {
    m->feed_extent(0.0F, 0.0F, raft_width, raft_height);

    (*raft_width)  *= 0.42F;
    (*raft_height) *= 0.80F;
}

/*************************************************************************************************/
void WarGrey::STEM::Gallery::load(float width, float height) {
    float raft_width, raft_height;

    TheBigBang::load(width, height);
    feed_raft_size(this->title, &raft_width, &raft_height);

    this->sea = this->insert(new Ellipselet(raft_width * 1.618F, raft_height, DEEPSKYBLUE));
                
    this->mast = this->insert(new Rectanglet(4.0F, raft_width, BURLYWOOD, SADDLEBROWN));
    this->flag = this->insert(new Trianglet(-raft_height, raft_height * 0.618F, -raft_height, -raft_height * 0.618F, ROYALBLUE, DODGERBLUE));

    this->post = this->insert(new RoundedRectanglet(raft_height * 0.618F, raft_height * 2.0F, -0.45F, BURLYWOOD, BURLYWOOD));
    this->paddle = this->insert(new Linelet(raft_width * 0.618F, raft_height * 2.0F, BROWN));
    this->raft = this->insert(new RoundedRectanglet(raft_width, raft_height, -0.1F, BURLYWOOD, BURLYWOOD));
    this->bow = this->insert(new RegularPolygonlet(3, raft_height * 0.5F, 180.0F, KHAKI, BURLYWOOD));
    this->stern = this->insert(new RegularPolygonlet(3, raft_height * 0.5F, 0.0F, KHAKI, BURLYWOOD));
                
    /* load renderer's name as the caption */ {
        IScreen* screen = this->master();

        if (screen != nullptr) {
            IUniverse* master = dynamic_cast<IUniverse*>(screen->display());

            if (master != nullptr) {
                this->caption = this->insert(new Labellet(GameFont::Default(), BLACK, master->get_renderer_name()));
            } else {
                this->caption = this->insert(new Labellet(GameFont::Default(), BLACK, "[Unknown]"));
            }
        }
    }
}

void WarGrey::STEM::Gallery::reflow(float width, float height) {
    float raft_width, raft_height;

    feed_raft_size(this->title, &raft_width, &raft_height);

    this->move_to(this->sea, width * 0.5F, height * 0.618F, MatterAnchor::CT);
                
    this->move_to(this->raft, this->sea, MatterAnchor::CT, MatterAnchor::CC);
    this->move_to(this->caption, this->raft, MatterAnchor::CC, MatterAnchor::CC);
    this->move_to(this->bow, this->raft, MatterAnchor::LC, MatterAnchor::RC);
    this->move_to(this->stern, this->raft, MatterAnchor::RC, MatterAnchor::LC);
    this->move_to(this->post, this->raft, MatterAnchor::RB, MatterAnchor::RB, -raft_height);
    this->move_to(this->paddle, this->post, MatterAnchor::CC, MatterAnchor::CC, raft_height * 1.2F);

    this->move_to(this->mast, this->raft, MatterAnchor::LB, MatterAnchor::LB, raft_height);
    this->move_to(this->flag, this->mast, MatterAnchor::RT, MatterAnchor::LT, 0.0F, raft_height * 0.25F);
}
