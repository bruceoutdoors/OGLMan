#include "oglman/camera.h"
#include "camerapanel.h"

namespace sfg {

CameraPanel::Ptr CameraPanel::Create()
{
    Ptr ptr = std::make_shared<CameraPanel>();

    ptr->SetRowSpacings( 5.f );
    ptr->SetColumnSpacings( 5.f );

    ptr->camera_name = Label::Create("Active Camera: None Selected");
    ptr->Attach(ptr->camera_name, sf::Rect<sf::Uint32>(0, 0, 2, 1),
         sfg::Table::FILL, sfg::Table::FILL );
    ptr->attachLabel("Focal length:", 0, 1, 1, 1, ALIGN_RIGHT);
    ptr->attachLabel("Near plane:",   0, 2, 1, 1, ALIGN_RIGHT);
    ptr->attachLabel("Far plane:",    0, 3, 1, 1, ALIGN_RIGHT);

    ptr->setupSpinButton(ptr->focal_length, 0, 600, 0.1f, 1);
    ptr->setupSpinButton(ptr->near_plane,   0, 100, 0.5f, 1);
    ptr->setupSpinButton(ptr->far_plane,    0, 100, 0.5f, 1);

    ptr->Attach(ptr->focal_length, sf::Rect<sf::Uint32>(1, 1, 1, 1),
         sfg::Table::FILL, sfg::Table::FILL );
    ptr->Attach(ptr->near_plane, sf::Rect<sf::Uint32>(1, 2, 1, 1),
            sfg::Table::FILL, sfg::Table::FILL );
    ptr->Attach(ptr->far_plane, sf::Rect<sf::Uint32>(1, 3, 1, 1),
            sfg::Table::FILL, sfg::Table::FILL );

    ptr->focal_length->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onFocalLength, ptr));
    ptr->near_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onNearPlane, ptr));
    ptr->far_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onFarPlane, ptr));

    return ptr;
}
Camera *CameraPanel::getActiveCamera() const
{
    return active_camera;
}

void CameraPanel::setActiveCamera(Camera *value)
{
    active_camera = value;
    focal_length->SetValue(active_camera->getFocalLength());
    near_plane->SetValue(active_camera->getNearPlane());
    far_plane->SetValue(active_camera->getFarPlane());
    camera_name->SetText("Active Camera: " + active_camera->getName());
}

void CameraPanel::onFocalLength()
{
    active_camera->setFocalLength(focal_length->GetValue());
}

void CameraPanel::onNearPlane()
{
    active_camera->setNearPlane(near_plane->GetValue());
}

void CameraPanel::onFarPlane()
{
    active_camera->setFarPlane(far_plane->GetValue());
}

} // end namespace sfg
