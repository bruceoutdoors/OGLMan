#include "oglman/bufferman.h"
#include "oglman/mesh.h"
#include "outliner.h"

#include <SFGUI/RadioButton.hpp>

namespace sfg {

Signal::SignalID Outliner::OnSelect = 0;

Outliner::Outliner(BufferMan *man) :
    bufferman(man), selected_mesh(nullptr)
{
    box = Box::Create(Box::Orientation::VERTICAL, 5.f);

    auto button_group = RadioButton::RadioButtonGroup::Create();

    for (BufferMan::It i = man->getMeshesBegin();
            i < man->getMeshesEnd(); ++i) {
        auto b = RadioButton::Create((*i)->getName(), button_group);
        b->GetSignal(ToggleButton::OnToggle).Connect(
            std::bind(&Outliner::onRadioSelect, this));
        buttons.push_back(b);
        box->Pack(b);
    }

    // add empty select:
    auto b = RadioButton::Create("*Select nothing*", button_group);
    b->SetActive(true);
    b->GetSignal(ToggleButton::OnToggle).Connect(
        std::bind(&Outliner::onSelectNone, this));
    buttons.push_back(b);
    box->Pack(b);
}

Outliner::Ptr Outliner::Create(BufferMan *man)
{
    return std::make_shared<Outliner>(man);
}

Box::Ptr Outliner::get() const
{
    return box;
}

Mesh *Outliner::getSelectedMesh()
{
    return selected_mesh;
}

bool Outliner::hasSelectedMesh() const
{
    selected_mesh != nullptr;
}

const std::string &Outliner::GetName() const
{
    static const std::string name("Outliner");
    return name;
}

sf::Vector2f Outliner::CalculateRequisition()
{
    return sf::Vector2f();
}

void Outliner::onRadioSelect()
{
    bufferman->deselectAll();
    BufferMan::It i = bufferman->getMeshesBegin();

    for (RadioButton::Ptr &b : buttons) {
        if (b->IsActive()) {
            selected_mesh = *i;
            selected_mesh->select();
            GetSignals().Emit(OnSelect);
            break;
        }

        if (i < bufferman->getMeshesEnd()) ++i;
    }
}

void Outliner::onSelectNone()
{
    bufferman->deselectAll();
    selected_mesh = nullptr;
    GetSignals().Emit(OnSelect);
}

} // end namespace sfg
