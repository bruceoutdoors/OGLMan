#include "oglman/camera.h"
#include "camerapanel.h"

namespace sfg {

CameraPanel::CameraPanel() :
    PanelWidget()
{
    camera_name = Label::Create("Active Camera: None Selected");
    attach(camera_name, 0, 0, 2, 1);
    attachLabel("Focal length:", 0, 1, 1, 1, ALIGN_RIGHT);
    attachLabel("Near plane:",   0, 2, 1, 1, ALIGN_RIGHT);
    attachLabel("Far plane:",    0, 3, 1, 1, ALIGN_RIGHT);

    setupSpinButton(focal_length, 0, 600, 0.1f, 1);
    setupSpinButton(near_plane,   0, 100, 0.5f, 1);
    setupSpinButton(far_plane,    0, 100, 0.5f, 1);

    attach(focal_length, 1, 1, 1, 1);
    attach(near_plane,   1, 2, 1, 1);
    attach(far_plane,    1, 3, 1, 1);

    focal_length->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onFocalLength, this));
    near_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onNearPlane, this));
    far_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&CameraPanel::onFarPlane, this));
}

CameraPanel::Ptr CameraPanel::Create()
{
    return std::make_shared<CameraPanel>();
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
