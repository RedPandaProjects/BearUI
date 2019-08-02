#include "BearUI.hpp"

BearUI::Classic::BearUICheakBox::BearUICheakBox()
{
	PushItem(&UICheakBoxSwitch);
	PushItem(&UIText);
	//UIText.Style.set(true, UIText.ST_CenterOfHeight);

	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorOff.Set(uint8(45), uint8(45), uint8(45));
	ColorOffSelect.Set(uint8(55), uint8(55), uint8(55));
	ColorOn.Set(uint8(0), uint8(60), uint8(200));
	ColorOnSelect.Set(uint8(0), uint8(70), uint8(200));
}

BearUI::Classic::BearUICheakBox::~BearUICheakBox()
{
}

void BearUI::Classic::BearUICheakBox::Switch(bool Switch)
{
	if (UICheakBoxSwitch.Switch != Switch) { UICheakBoxSwitch.Switch = Switch; UICheakBoxSwitch.Reset(); }
}

void BearUI::Classic::BearUICheakBox::Reset()
{
	float hw= static_cast<float>(Font.GetHieght());
	Size.y = hw;
	UICheakBoxSwitch.ColorOff = ColorOff;
	UICheakBoxSwitch.ColorOffSelect = ColorOffSelect;
	UICheakBoxSwitch.ColorOn = ColorOn;
	UICheakBoxSwitch.ColorOnSelect = ColorOnSelect;
	UICheakBoxSwitch.ColorPlaneBackground = ColorPlaneBackground;
	UICheakBoxSwitch.Position = Position;
	UICheakBoxSwitch.Size.set(hw, hw);
	UIText.Position.set(Position.x + hw + 4, Position.y);
	UIText.Font = Font;
	Size.x =4+hw +UIText.GetMaxSizeLine(*Text);
	UIText.Size.y = hw;
	UIText.Size.x = UIText.GetMaxSizeLine(*Text);;
	UIText.Text = Text;
	BearUIItem::Reset();
}

