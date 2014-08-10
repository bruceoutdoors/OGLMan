#include "oglman/mesh.h"
#include "transformpanel.h"
#include "panelwidget.h"

namespace sfg {

const sf::String DEFAULT_MSG = "Selected Mesh: None";

TransformPanel::TransformPanel() :
    PanelWidget(),
    active_mesh(nullptr)
{
    mesh_name = Label::Create(DEFAULT_MSG);
    attach(mesh_name, 0, 0, 4, 1);
    attachLabel("Translate:", 0, 1, 1, 1, ALIGN_RIGHT);
    attachLabel("Rotation:",  0, 2, 1, 1, ALIGN_RIGHT);
    attachLabel("Scale:",     0, 3, 1, 1, ALIGN_RIGHT);

    // setup spin group
    spin_group.resize(6);
    for (int i = 0; i <= 2; i++) setupSpinButton(spin_group[i], -10000, 10000, 0.25f, 2);
    for (int i = 3; i <= 5; i++) setupSpinButton(spin_group[i], -36000, 36000, 5, 0);

    // add spin group to table:
    int k = 0;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 3; j++) {
            attach(spin_group[k++], j, i, 1, 1);
        }
    }

    scale_slider = Scale::Create(0, 5, 0.01f);
    scale_label = Label::Create("0.00");

    attach(scale_slider, 1, 3, 2, 1);
    attach(scale_label, 3, 3, 1, 1);

    reset_trans_button = Button::Create("Reset transformations");
    attach(reset_trans_button, 1, 4, 3, 1);

    spin_group[0]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onTranslateX, this));
    spin_group[1]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onTranslateY, this));
    spin_group[2]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onTranslateZ, this));
    spin_group[3]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onRotateX, this));
    spin_group[4]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onRotateY, this));
    spin_group[5]->GetSignal(SpinButton::OnValueChanged).Connect(
        std::bind(&TransformPanel::onRotateZ, this));

    scale_slider->GetAdjustment()->GetSignal(Adjustment::OnChange).Connect(
        std::bind(&TransformPanel::onScale, this));
    reset_trans_button->GetSignal(Button::OnLeftClick).Connect(
        std::bind(&TransformPanel::onResetTransformations, this));
}

TransformPanel::Ptr TransformPanel::Create()
{
    return std::make_shared<TransformPanel>();
}

Mesh *TransformPanel::getActiveMesh() const
{
    return active_mesh;
}

void TransformPanel::setActiveMesh(Mesh *value)
{
    active_mesh = value;

    if (!hasActiveMesh()) {
        mesh_name->SetText(DEFAULT_MSG);
        onResetTransformations();
        return;
    }

    scale_slider->GetAdjustment()->SetValue(active_mesh->getScale());
    scale_label->SetText(floatToString(active_mesh->getScale()));

    spin_group[0]->SetValue(active_mesh->getTranslateX());
    spin_group[1]->SetValue(active_mesh->getTranslateY());
    spin_group[2]->SetValue(active_mesh->getTranslateZ());

    spin_group[3]->SetValue(active_mesh->getRotateX());
    spin_group[4]->SetValue(active_mesh->getRotateY());
    spin_group[5]->SetValue(active_mesh->getRotateZ());

    mesh_name->SetText("Selected Mesh: " + active_mesh->getName());
}

bool TransformPanel::hasActiveMesh() const
{
    return active_mesh != nullptr;
}

void TransformPanel::onTranslateX()
{
    if (!hasActiveMesh()) return;
    active_mesh->setTranslateX(spin_group[0]->GetValue());
}

void TransformPanel::onTranslateY()
{
    if (!hasActiveMesh()) return;
    active_mesh->setTranslateY(spin_group[1]->GetValue());
}

void TransformPanel::onTranslateZ()
{
    if (!hasActiveMesh()) return;
    active_mesh->setTranslateZ(spin_group[2]->GetValue());
}

void TransformPanel::onRotateX()
{
    if (!hasActiveMesh()) return;
    active_mesh->setRotateX(spin_group[3]->GetValue());
}

void TransformPanel::onRotateY()
{
    if (!hasActiveMesh()) return;
    active_mesh->setRotateY(spin_group[4]->GetValue());
}

void TransformPanel::onRotateZ()
{
    if (!hasActiveMesh()) return;
    active_mesh->setRotateZ(spin_group[5]->GetValue());
}

void TransformPanel::onScale()
{
    scale_label->SetText(floatToString(scale_slider->GetAdjustment()->GetValue()));
    if (!hasActiveMesh()) return;
    active_mesh->setScale(scale_slider->GetAdjustment()->GetValue());
}

void TransformPanel::onResetTransformations()
{
    for (auto &sb : spin_group) sb->GetAdjustment()->SetValue(0);
    scale_slider->SetValue(1);
}

} // end namespace sfg
