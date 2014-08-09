#include "panelwidget.h"

namespace sfg {

void PanelWidget::attachLabel(sf::String text, sf::Uint32 r, sf::Uint32 c,
                                 sf::Uint32 rs, sf::Uint32 cs, sf::Vector2f align)
{
    auto alignment = Alignment::Create();
    alignment->SetAlignment(align);
    alignment->SetScale(sf::Vector2f( 0.f, .01f ));
    alignment->Add(Label::Create(text));

    Attach(alignment, sf::Rect<sf::Uint32>(r, c, rs, cs),
                   Table::FILL, Table::FILL );
}

void PanelWidget::setupSpinButton(SpinButton::Ptr &b, float min,
                                     float max, float step, unsigned int precision)
{
    b = SpinButton::Create(min, max, step);
    b->SetRequisition(sf::Vector2f(70.f, 0.f));
    b->SetDigits(precision);
}

std::string PanelWidget::floatToString(float fl, unsigned int precision)
{
    std::stringstream sstr;
    sstr << fl;

    std::string result = sstr.str();
    std::size_t found = result.find(".");
    result = result.substr(0, found + precision + 1);

    return result;
}

} // end namespace sfg
