#include "BearUI.hpp"

BearUI::Classic::BearUIGroupBox::BearUIGroupBox()
{
	UIText.Flags.set(false, UIText.UI_NoClip);
	ColorBackground.Set(uint8(100), uint8(100), uint8(100));
	Color.Set(uint8(20), uint8(20), uint8(20));
	ColorBackgroundFocused.Set(uint8(0), uint8(120), uint8(200));
}

BearUI::Classic::BearUIGroupBox::~BearUIGroupBox()
{
}

float BearUI::Classic::BearUIGroupBox::CalcHeight() const
{
	return 0.0f;
}

float BearUI::Classic::BearUIGroupBox::CalcWidth() const
{
	return 0.0f;
}

void BearUI::Classic::BearUIGroupBox::OnMessage(int32 message)
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

void BearUI::Classic::BearUIGroupBox::KillFocus()
{
	UIPlaneBackgound.Color = ColorBackground;
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUIGroupBox::Reset()
{
	PopItem(&UIPlane);
	PopItem(&UIPlaneBackgound);
	PopItem(&UIText);
	UIPlaneBackgound.Rect = Rect;
	UIPlane.Rect = Rect;
	UIPlane.Rect +=BearVector4<float>(1, 1, -2, -2);
	UIText.Position = Position;
	UIText.Position +=BearVector2<float>(roundf(static_cast<float>(Font.GetHieght())*0.333f), 1);
	UIText.Clip = UIPlane.Rect;
	
	UIPlaneBackgound.Color = ColorBackground;
	UIPlane.Color = Color;
	PushItem(&UIText);
	PushItem(&UIPlane);
	PushItem(&UIPlaneBackgound);
	BearUIItem::Reset();
}

bool BearUI::Classic::BearUIGroupBox::OnKeyDown(BearInput::Key key)
{
	if (BearUIItem::OnKeyDown(key))
	{
		UIPlaneBackgound.Color = ColorBackgroundFocused;
		return true;
	}
	return false;
}

void BearUI::Classic::BearUIGroupBox::Reload()
{
	UIText.Text = Text;
	UIText.Font = Font;
	BearUIItem::Reload();
}
