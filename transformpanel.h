#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H

#include "panelwidget.h"
class Mesh;

namespace sfg {

class TransformPanel : public PanelWidget
{
public:
    typedef std::shared_ptr<TransformPanel> Ptr;
    static Ptr Create();

    Mesh *getActiveMesh() const;
    void setActiveMesh(Mesh *value);

private:
    Mesh *active_mesh;
    std::vector<sfg::SpinButton::Ptr> spin_group;
    sfg::Label::Ptr mesh_name;
    sfg::Scale::Ptr scale_slider;
    sfg::Label::Ptr scale_label;
    sfg::Button::Ptr reset_trans_button;

    // slots:
    void onTranslateX();
    void onTranslateY();
    void onTranslateZ();
    void onRotateX();
    void onRotateY();
    void onRotateZ();
    void onScale();
    void onResetTransformations();
};

} // end namespace sfg

#endif // TRANSFORMPANEL_H
