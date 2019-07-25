#include "BearUI.hpp"

BearUI::Classic::BearUITextBox::BearUITextBox()
{

	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorPlane.Set(uint8(20), uint8(20), uint8(20));
	ColorPlaneBackgroundFocused.Set(uint8(0), uint8(120), uint8(200));
	PushItem(&UICursor.UIPlane);
	PushItem(&UIText);
	PushItem(&UIPlane);
	PushItem(&UIPlaneBackground);
	UIText.Flags.set(false, UIText.UI_NoClip);

	
}

BearUI::Classic::BearUITextBox::~BearUITextBox()
{
}

void BearUI::Classic::BearUITextBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
		UICursor.Update(UIText,UIPlane);
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUITextBox::Reset()
{
	if (Style.test(S_richTextBox))
	{
		UIText.Flags.set(false, UIText.F_IgnoreLine);
	}
	else
	{
		Rect.y1 = static_cast<float>(Font.GetMaxHieght()) + 2 + 4;
		UIText.Flags.set(true, UIText.F_IgnoreLine);
	}
	////////////////////////////////////////////////////////////////////
	UIText.Rect = UIPlane.Rect;
	UIText.Font = Font;
	UIText.Rect += BearCore::BearVector4<float>(2, 2, -4, -4);
	UIText.Clip = UIText.Rect;
	////////////////////////////////////////////////////////////////////
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIPlane.Color = ColorPlane;
	////////////////////////////////////////////////////////////////////
	UIPlaneBackground.Color = ColorPlaneBackground;
	UIPlaneBackground.Rect = Rect;
	////////////////////////////////////////////////////////////////////
	UICursor.Reset(UIText);
	////////////////////////////////////////////////////////////////////
	BearUIItem::Reset();
}

bool BearUI::Classic::BearUITextBox::OnChar(bchar16 ch)
{
	if (ch == L'\b')
	{
		if(Text.size())
		Text.erase(Text.begin() + Text.size()-1);
	}
	else
	{
		if (ch == L'\r')ch =L'\n';
		if (ch == L'\n'&&Style.test(S_richTextBox))return true;
		Text.append(1, BearCore::BearEncoding::ToCurrent( ch));
		UIText.Text = Text;
		UIText.Reset();
	}
	return true;
}

bool BearUI::Classic::BearUITextBox::OnKeyDown(BearInput::Key key)
{
	switch (key)
	{
	
	case BearInput::KeyLeft:
		if (Focused())
		{
			UICursor.Position--;
			UICursor.Update(UIText, UIPlane);
		}
		break;
	case BearInput::KeyRight:
		if (Focused())
		{
			UICursor.Position++;
			UICursor.Update(UIText, UIPlane);
		}
		break;

	default:
		break;
	}
	return BearUIItem::OnKeyDown(key)||Focused();
}

bool BearUI::Classic::BearUITextBox::OnKeyUp(BearInput::Key key)
{
	
	return 	BearUIItem::OnKeyUp(key);;
}

void BearUI::Classic::BearUITextBox::KillFocus()
{

	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUITextBox::Update()
{
	
	BearUIItem::Update();
}

BearUI::Classic::BearUITextBox::SCursor::SCursor() :Position(0)
{
}

void BearUI::Classic::BearUITextBox::SCursor::Reset(BearUIText & UIText)
{
	Position = 0;
	UIPlane.Visible = true;
	UIPlane.Position = UIText.Position;
	UIPlane.Size.x = 1.f;
	UIPlane.Size.y =static_cast<float>( UIText.Font.GetMaxHieght());

}

void BearUI::Classic::BearUITextBox::SCursor::Update(BearUIText & UIText, BearUITexture&UIGlobalPlane)
{
	if (Position < 0)Position = 0;
	if (Position > UIText.Text.size())Position =static_cast<bint>( UIText.Text.size());
	UIPlane.Visible = false;
	UIPlane.Position = UIText.Position;
	UIPlane.Position.x += UIText.GetSizeLastLine(*UIText.Text,Position);
	UIPlane.Reset();
}
