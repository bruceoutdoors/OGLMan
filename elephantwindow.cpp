#include "elephantwindow.h"

const float LIGHT_MOVE = 0.1f;
const float ZOOM_SPEED = 1.0f;
const float PAN_SPEED  = 0.05f;
const float INIT_SCALE = 0.25f;

const sf::Vector2f ALIGN_LEFT   = sf::Vector2f(0.0f, 0.5f);
const sf::Vector2f ALIGN_RIGHT  = sf::Vector2f(1.0f, 0.5f);
const sf::Vector2f ALIGN_CENTER = sf::Vector2f(0.5f, 0.5f);

ElephantWindow::ElephantWindow(sf::VideoMode mode, const sf::String &title)
    : OpenGLWindow(mode, title)
{
    isWindowSelect = false;
    clock = new sf::Clock();

    arcball = new Arcball();
    setActiveCamera(arcball);
}

ElephantWindow::~ElephantWindow()
{
    delete elephant;
    delete plane;
    delete clock;
}

void ElephantWindow::draw()
{
    elephant->draw();
    plane->draw();
}

void ElephantWindow::init()
{
    std::string resource_dir = "./resource/";
    elephant = new Mesh(resource_dir + "elephant-triangulated.obj");
    elephant->setTexture(resource_dir + "elephant-texture-1024.jpg");
    elephant->setScale(INIT_SCALE);

    plane = new Plane(10);

    offLights();
    guiSetup();
}

bool ElephantWindow::handleEvents()
{
    sf::Event e;
    while (this->pollEvent(e)) {
        desktop.HandleEvent(e);
        switch (e.type) {
        case sf::Event::Closed:
            this->close();
            return true;
            break;

        // Resize event : adjust viewport
        case sf::Event::Resized:
            resizeGL(e.size.width, e.size.height);
            break;

        // Handle keyboard events
        case sf::Event::KeyPressed:
            if (keyboardEventHandler(e.key.code)) return true;
            break;

        case sf::Event::MouseMoved:
            if (isWindowSelect) break;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                getActiveCamera()->mouseDrag(vec2(e.mouseMove.x, e.mouseMove.y));
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                getActiveCamera()->pan(vec2(e.mouseMove.x, e.mouseMove.y), PAN_SPEED);
            }
            break;

        case sf::Event::MouseWheelMoved:
            if (isWindowSelect) break;
            if (e.mouseWheel.delta > 0) {
                getActiveCamera()->moveForward(ZOOM_SPEED);
            } else {
                getActiveCamera()->moveForward(-ZOOM_SPEED);
            }
            break;


        default:
            break; // suppress enum not handled warnings
        }
    }
    return false;
}

void ElephantWindow::guiDraw()
{
    // Update the GUI every 1ms
    if( clock->getElapsedTime().asMicroseconds() >= 1000 ) {
        auto delta = static_cast<float>( clock->getElapsedTime().asMicroseconds() ) / 1000000.f;
        // Update() takes the elapsed time in seconds.
        desktop.Update(delta);
        clock->restart();
    }
    sfgui.Display(*this);
}

void ElephantWindow::guiSetup()
{
    setActive();

    table = sfg::Table::Create();
    table->SetRowSpacings( 5.f );
    table->SetColumnSpacings( 5.f );

    attachLabel("Tranformations", 0, 0, 4, 1);
    attachLabel("Translate:", 0, 1, 1, 1, ALIGN_RIGHT);
    attachLabel("Rotation:",  0, 2, 1, 1, ALIGN_RIGHT);
    attachLabel("Scale:",     0, 3, 1, 1, ALIGN_RIGHT);

    // setup spin group
    spin_group.resize(6);
    for(int i = 0; i <= 2; i++) setupSpinButton(spin_group[i], -50, 50, 0.25f, 2);
    for(int i = 3; i <= 5; i++) setupSpinButton(spin_group[i], -360, 360, 5, 0);

    // add spin group to table:
    int k = 0;
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= 3; j++) {
            table->Attach(spin_group[k++], sf::Rect<sf::Uint32>(j, i, 1, 1),
                 sfg::Table::FILL, sfg::Table::FILL );
        }
    }

    scale_slider = sfg::Scale::Create(0, 1, 0.01f);
    scale_slider->GetAdjustment()->SetValue(elephant->getScale());
    scale_label = sfg::Label::Create(floatToString(INIT_SCALE));

    table->Attach(scale_slider, sf::Rect<sf::Uint32>(1, 3, 2, 1),
                  sfg::Table::FILL, sfg::Table::FILL);
    table->Attach(scale_label, sf::Rect<sf::Uint32>(3, 3, 1, 1),
                  sfg::Table::FILL, sfg::Table::FILL);

    reset_trans_button = sfg::Button::Create("Reset transformations");
    table->Attach(reset_trans_button,
                  sf::Rect<sf::Uint32>(1, 4, 3, 1),
                  sfg::Table::FILL, sfg::Table::FILL);

    // separator:
    table->Attach(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL),
                  sf::Rect<sf::Uint32>(0, 5, 4, 1),
                  sfg::Table::FILL, sfg::Table::FILL);

    attachLabel("Camera Controls", 0, 6, 4, 1);
    attachLabel("Focal length:", 0, 7, 1, 1, ALIGN_RIGHT);
    attachLabel("Near plane:",   0, 8, 1, 1, ALIGN_RIGHT);
    attachLabel("Far plane:",    0, 9, 1, 1, ALIGN_RIGHT);

    setupSpinButton(focal_length, 0, 600, 0.1f, 1);
    setupSpinButton(near_plane,   0, 100, 0.5f, 1);
    setupSpinButton(far_plane,    0, 100, 0.5f, 1);

    focal_length->SetValue(arcball->getFocalLength());
    near_plane->SetValue(arcball->getNearPlane());
    far_plane->SetValue(arcball->getFarPlane());

    table->Attach(focal_length, sf::Rect<sf::Uint32>(1, 7, 2, 1),
         sfg::Table::FILL, sfg::Table::FILL );
    table->Attach(near_plane, sf::Rect<sf::Uint32>(1, 8, 2, 1),
            sfg::Table::FILL, sfg::Table::FILL );
    table->Attach(far_plane, sf::Rect<sf::Uint32>(1, 9, 2, 1),
            sfg::Table::FILL, sfg::Table::FILL );

    auto window = sfg::Window::Create();
    window->SetStyle(window->GetStyle() ^ sfg::Window::RESIZE);
    window->SetTitle("Toolbox");
    window->Add(table);
    desktop.Add(window);

    spin_group[0]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onTranslateX, this));
    spin_group[1]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onTranslateY, this));
    spin_group[2]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onTranslateZ, this));
    spin_group[3]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onRotateX, this));
    spin_group[4]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onRotateY, this));
    spin_group[5]->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onRotateZ, this));

    scale_slider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(
                std::bind(&ElephantWindow::onScale, this));
    reset_trans_button->GetSignal(sfg::Button::OnLeftClick).Connect(
                std::bind(&ElephantWindow::onResetTransformations, this));

    focal_length->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onFocalLength, this));
    near_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onNearPlane, this));
    far_plane->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&ElephantWindow::onFarPlane, this));

    window->GetSignal(sfg::Widget::OnMouseEnter).Connect(
                std::bind(&ElephantWindow::onWindowMove, this));
    window->GetSignal(sfg::Widget::OnMouseLeave).Connect(
                std::bind(&ElephantWindow::onWindowMoveRelease, this));
}

void ElephantWindow::setupSpinButton(sfg::SpinButton::Ptr &b, float min,
                                     float max, float step, unsigned int precision)
{
    b = sfg::SpinButton::Create(min, max, step);
    b->SetRequisition(sf::Vector2f(70.f, 0.f));
    b->SetDigits(precision);
}

void ElephantWindow::attachLabel(sf::String text, sf::Uint32 r, sf::Uint32 c,
                                 sf::Uint32 rs, sf::Uint32 cs, sf::Vector2f align)
{
    auto alignment = sfg::Alignment::Create();
    alignment->SetAlignment(align);
    alignment->SetScale(sf::Vector2f( 0.f, .01f ));
    alignment->Add(sfg::Label::Create(text));

    table->Attach(alignment, sf::Rect<sf::Uint32>(r, c, rs, cs),
                   sfg::Table::FILL, sfg::Table::FILL );
}

bool ElephantWindow::keyboardEventHandler(int key)
{
    switch (key) {
    case sf::Keyboard::Escape:
        this->close();
        return true;

    case sf::Keyboard::F11:
        toggleFullscreen();
        break;

    case sf::Keyboard::Num7:
        hasLights() ? offLights() : onLights();
        break;

    case sf::Keyboard::Num4:
        wireframeToggle();
        break;

    }

    return false;
}

void ElephantWindow::onWindowMove()
{
    isWindowSelect = true;
}

void ElephantWindow::onWindowMoveRelease()
{
    isWindowSelect = false;
}

std::string ElephantWindow::floatToString(float fl, unsigned int precision)
{
    std::stringstream sstr;
    sstr << fl;

    std::string result = sstr.str();
    std::size_t found = result.find(".");
    result = result.substr(0, found + precision + 1);

    return result;
}

void ElephantWindow::onTranslateX()
{
    elephant->setTranslateX(spin_group[0]->GetValue());
}

void ElephantWindow::onTranslateY()
{
    elephant->setTranslateY(spin_group[1]->GetValue());
}

void ElephantWindow::onTranslateZ()
{
    elephant->setTranslateZ(spin_group[2]->GetValue());
}

void ElephantWindow::onRotateX()
{
    elephant->setRotateX(spin_group[3]->GetValue());
}

void ElephantWindow::onRotateY()
{
    elephant->setRotateY(spin_group[4]->GetValue());
}

void ElephantWindow::onRotateZ()
{
    elephant->setRotateZ(spin_group[5]->GetValue());
}

void ElephantWindow::onScale()
{
    elephant->setScale(scale_slider->GetAdjustment()->GetValue());
    scale_label->SetText(floatToString(elephant->getScale()));
}

void ElephantWindow::onFocalLength()
{
    arcball->setFocalLength(focal_length->GetValue());
}

void ElephantWindow::onNearPlane()
{
    arcball->setNearPlane(near_plane->GetValue());
}

void ElephantWindow::onFarPlane()
{
    arcball->setFarPlane(far_plane->GetValue());
}

void ElephantWindow::onResetTransformations()
{
    for (auto &sb : spin_group) sb->GetAdjustment()->SetValue(0);
    scale_slider->SetValue(INIT_SCALE);
}
