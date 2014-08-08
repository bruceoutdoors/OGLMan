#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <SFGUI/SFGUI.hpp>
#include <sstream>

namespace sfg {

const sf::Vector2f ALIGN_LEFT   = sf::Vector2f(0.0f, 0.5f);
const sf::Vector2f ALIGN_RIGHT  = sf::Vector2f(1.0f, 0.5f);
const sf::Vector2f ALIGN_CENTER = sf::Vector2f(0.5f, 0.5f);

class PanelWidget : public Table
{
public:
    void attachLabel(sf::String text, sf::Uint32 r, sf::Uint32 c,
                     sf::Uint32 rs, sf::Uint32 cs,
                     sf::Vector2f align = ALIGN_CENTER);
    void setupSpinButton(sfg::SpinButton::Ptr &b, float min,
                                         float max, float step, unsigned int precision);
protected:
    std::string floatToString(float fl, unsigned int precision = 2);
};

} // end namespace sfg

#endif // TRANSFORMWIDGET_H
