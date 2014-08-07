#ifndef CAMERAPANEL_H
#define CAMERAPANEL_H

#include "panelwidget.h"
class Camera;

namespace sfg {

class CameraPanel : public PanelWidget
{
public:
    typedef std::shared_ptr<CameraPanel> Ptr;
    static Ptr Create();

    Camera *getActiveCamera() const;
    void setActiveCamera(Camera *value);

private:
    sfg::SpinButton::Ptr focal_length;
    sfg::SpinButton::Ptr near_plane;
    sfg::SpinButton::Ptr far_plane;

    Camera *active_camera;

    // slots:
    void onFocalLength();
    void onNearPlane();
    void onFarPlane();
};

} // end namespace sfg

#endif // CAMERAPANEL_H
