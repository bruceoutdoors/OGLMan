#ifndef OUTLINER_H
#define OUTLINER_H

#include <SFGUI/SFGUI.hpp>
#include <vector>

class BufferMan;
class Mesh;

namespace sfg {

class Outliner : public Widget
{
public:
    typedef std::shared_ptr<Outliner> Ptr;
    Outliner(BufferMan *man);
    static Ptr Create(BufferMan *man);
    Box::Ptr getBox() const;
    Mesh *getSelectedMesh();
    bool hasSelectedMesh() const;

    virtual const std::string &GetName() const override;

    // signals:
    static Signal::SignalID OnSelect;

protected:
    // dummy function to shut the compiler up
    virtual sf::Vector2f CalculateRequisition() override;

private:
    std::vector<RadioButton::Ptr> buttons;
    Box::Ptr box;

    BufferMan *bufferman;
    Mesh *selected_mesh;

    // slots:
    void onRadioSelect();
    void onSelectNone();

};

} // end namespace sfg

#endif // OUTLINER_H
