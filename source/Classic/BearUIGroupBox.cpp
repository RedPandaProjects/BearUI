#include "BearUI.hpp"

BearUI::Classic::BearUIPGroupBox::BearUIPGroupBox()
{
	UIText.Flags.set(false, UIText.UI_NoClip);
	ColorBackground.Set(uint8(100), uint8(100), uint8(100));
	Color.Set(uint8(20), uint8(20), uint8(20));
	ColorBackgroundFocused.Set(uint8(0), uint8(120), uint8(200));
}

BearUI::Classic::BearUIPGroupBox::~BearUIPGroupBox()
{
}

void BearUI::Classic::BearUIPGroupBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
		UIPlaneBackgound.Color = ColorBackgroundFocused;
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIPGroupBox::KillFocus()
{
	UIPlaneBackgound.Color = ColorBackground;
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUIPGroupBox::Reset()
{
	PopItem(&UIPlane);
	PopItem(&UIPlaneBackgound);
	PopItem(&UIText);
	UIPlaneBackgound.Rect = Rect;
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIText.Position = Position;
	UIText.Position += BearCore::BearVector2<float>(1, 1);
	UIText.Clip = UIPlane.Rect;
	UIText.Text = Text;
	UIText.Font = Font;
	UIPlaneBackgound.Color = ColorBackground;
	UIPlane.Color = Color;
	PushItem(&UIText);
	PushItem(&UIPlane);
	PushItem(&UIPlaneBackgound);
	BearUIItem::Reset();
}
