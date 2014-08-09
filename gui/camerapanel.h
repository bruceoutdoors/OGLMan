#ifndef CAMERAPANEL_H
#define CAMERAPANEL_H

#include "panelwidget.h"
class Camera;

namespace sfg {

class CameraPanel : public PanelWidget
{
public:
    typedef std::shared_ptr<CameraPanel> Ptr;
    CameraPanel();
    static Ptr Create();

    Camera *getActiveCamera() const;
    void setActiveCamera(Camera *value);

private:
    SpinButton::Ptr focal_length;
    SpinButton::Ptr near_plane;
    SpinButton::Ptr far_plane;
    Label::Ptr camera_name;

    Camera *active_camera;

    // slots:
    void onFocalLength();
    void onNearPlane();
    void onFarPlane();
};

} // end namespace sfg

#endif // CAMERAPANEL_H
