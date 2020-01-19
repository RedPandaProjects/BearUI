#include "BearUI.hpp"

BearUI::Classic::BearUICheakBoxSwitch::BearUICheakBoxSwitch():Switch(false)
{
	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorOff.Set(uint8(45), uint8(45), uint8(45));
	ColorOffSelect.Set(uint8(55), uint8(55), uint8(55));
	ColorOn.Set(uint8(0), uint8(60), uint8(200));
	ColorOnSelect.Set(uint8(0), uint8(70), uint8(200));
	PushItem(&UIPlane);
	PushItem(&UIPlaneBackground);
	UIPlaneBackground.Flags.set(false, UIPlaneBackground.UI_NoMouseEnter);
}

BearUI::Classic::BearUICheakBoxSwitch::~BearUICheakBoxSwitch()
{
}

float BearUI::Classic::BearUICheakBoxSwitch::CalcWidth() const
{
	return 0.0f;
}

float BearUI::Classic::BearUICheakBoxSwitch::CalcHeight() const
{
	return 0.0f;
}

void BearUI::Classic::BearUICheakBoxSwitch::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLevae:
		if (!Switch)
			UIPlane.Color = ColorOff;
		else
			UIPlane.Color = ColorOn;
		break;
	case M_MouseLClick:
		Switch = !Switch;
	case M_MouseEnter:
		if (!Switch)
			UIPlane.Color = ColorOffSelect;
		else
			UIPlane.Color = ColorOnSelect;
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUICheakBoxSwitch::Reset()
{


	UIPlane.Rect = Rect;
	UIPlane.Rect +=BearVector4<float>(Rect.x1*0.1f, Rect.y1*0.1f, Rect.x1*-0.2f, Rect.y1*-0.2f);
	UIPlane.Color = ColorOff;


	UIPlaneBackground.Rect = Rect;
	UIPlaneBackground.Color = ColorPlaneBackground;
	BearUIItem::Reset();
}

void BearUI::Classic::BearUICheakBoxSwitch::KillFocus()
{
	if (!Switch)
		UIPlane.Color = ColorOff;
	else
		UIPlane.Color = ColorOn;
	BearUIItem::KillFocus();
}