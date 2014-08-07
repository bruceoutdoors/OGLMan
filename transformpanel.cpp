#include "oglman/mesh.h"
#include "transformpanel.h"
#include "panelwidget.h"

namespace sfg {

TransformPanel::Ptr TransformPanel::Create()
{
    Ptr ptr = std::make_shared<TransformPanel>();

    ptr->SetRowSpacings( 5.f );
    ptr->SetColumnSpacings( 5.f );

    ptr->attachLabel("Selected Mesh: ", 0, 0, 4, 1);
    ptr->attachLabel("Translate:", 0, 1, 1, 1, ALIGN_RIGHT);
    ptr->attachLabel("Rotation:",  0, 2, 1, 1, ALIGN_RIGHT);
    ptr->attachLabel("Scale:",     0, 3, 1, 1, ALIGN_RIGHT);

    // setup spin group
    ptr->spin_group.resize(6);
    for(int i = 0; i <= 2; i++) ptr->setupSpinButton(ptr->spin_group[i], -50, 50, 0.25f, 2);
    for(int i = 3; i <= 5; i++) ptr->setupSpinButton(ptr->spin_group[i], -360, 360, 5, 0);

    // add spin group to table:
    int k = 0;
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= 3; j++) {
            ptr->Attach(ptr->spin_group[k++], sf::Rect<sf::Uint32>(j, i, 1, 1),
                    sfg::Table::FILL, sfg::Table::FILL );
        }
    }

    ptr->scale_slider = sfg::Scale::Create(0, 1, 0.01f);
    ptr->scale_label = sfg::Label::Create("0.00");

    ptr->Attach(ptr->scale_slider, sf::Rect<sf::Uint32>(1, 3, 2, 1),
           sfg::Table::FILL, sfg::Table::FILL);
    ptr->Attach(ptr->scale_label, sf::Rect<sf::Uint32>(3, 3, 1, 1),
           sfg::Table::FILL, sfg::Table::FILL);

    ptr->reset_trans_button = sfg::Button::Create("Reset transformations");
    ptr->Attach(ptr->reset_trans_button,
                  sf::Rect<sf::Uint32>(1, 4, 3, 1),
                  sfg::Table::FILL, sfg::Table::FILL);

    ptr->spin_group[0]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onTranslateX, ptr));
    ptr->spin_group[1]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onTranslateY, ptr));
    ptr->spin_group[2]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onTranslateZ, ptr));
    ptr->spin_group[3]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onRotateX, ptr));
    ptr->spin_group[4]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onRotateY, ptr));
    ptr->spin_group[5]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&TransformPanel::onRotateZ, ptr));

    ptr->scale_slider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(
                std::bind(&TransformPanel::onScale, ptr));
    ptr->reset_trans_button->GetSignal(sfg::Button::OnLeftClick).Connect(
                std::bind(&TransformPanel::onResetTransformations, ptr));

    return ptr;
}
Mesh *TransformPanel::getActiveMesh() const
{
    return active_mesh;
}

void TransformPanel::setActiveMesh(Mesh *value)
{
    active_mesh = value;

    scale_slider->GetAdjustment()->SetValue(active_mesh->getScale());
    scale_label->SetText(floatToString(active_mesh->getScale()));

    spin_group[0]->SetValue(active_mesh->getTranslateX());
    spin_group[1]->SetValue(active_mesh->getTranslateY());
    spin_group[2]->SetValue(active_mesh->getTranslateZ());

    spin_group[3]->SetValue(active_mesh->getRotateX());
    spin_group[4]->SetValue(active_mesh->getRotateY());
    spin_group[5]->SetValue(active_mesh->getRotateZ());
}

void TransformPanel::onTranslateX()
{
    active_mesh->setTranslateX(spin_group[0]->GetValue());
}

void TransformPanel::onTranslateY()
{
    active_mesh->setTranslateY(spin_group[1]->GetValue());
}

void TransformPanel::onTranslateZ()
{
    active_mesh->setTranslateZ(spin_group[2]->GetValue());
}

void TransformPanel::onRotateX()
{
    active_mesh->setRotateX(spin_group[3]->GetValue());
}

void TransformPanel::onRotateY()
{
    active_mesh->setRotateY(spin_group[4]->GetValue());
}

void TransformPanel::onRotateZ()
{
    active_mesh->setRotateZ(spin_group[5]->GetValue());
}

void TransformPanel::onScale()
{
    active_mesh->setScale(scale_slider->GetAdjustment()->GetValue());
    scale_label->SetText(floatToString(active_mesh->getScale()));
}

void TransformPanel::onResetTransformations()
{
    for (auto &sb : spin_group) sb->GetAdjustment()->SetValue(0);
    scale_slider->SetValue(1);
}

} // end namespace sfg
