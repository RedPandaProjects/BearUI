#include "BearUI.hpp"

BearUI::Classic::BearUIMenuItem::BearUIMenuItem():Menu(0), CallBack(0)
{
	PushItem(&UIText);
	UITriangleSubMenu.Visible = true;
	PushItem(&UITriangleSubMenu);
	PushItem(&UITextureBackground);
	Parent = 0;
}

BearUI::Classic::BearUIMenuItem::~BearUIMenuItem()
{
	if (CallBack)CallBack->Destroy();
}

void BearUI::Classic::BearUIMenuItem::OnMessage(int32 message)
{
	BearUIItem::OnMessage(message);
	switch (message)
	{
	case M_MouseEnter:

		if (Style.is(S_Border))break;;
		UITextureBackground.Visible = false;
		if(Menu)
		Menu->Visible = false;
		break;
	case M_MouseLevae:
		if (Style.is(S_Border))break;;
		if (Flags.is(F_NotHide))break;;
		UITextureBackground.Visible = true;
		if (Menu)
		Menu->Visible = true;
		break;
	case M_MouseLClick:
		if (Menu)break;
		if(Parent)	Parent->OnMessage(BearUIMenu::M_ItemClick);
		if(CallBack)
		CallBack->Call<void>(CallBack_Class);
		break;
	};
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIMenuItem::Reset()
{
	
	if (Style.is(S_Border))
	{

		UIText.Visible = true;
		UITriangleSubMenu.Visible = true;
		UITextureBackground.Color = Color;
		UITextureBackground.Rect= Rect;
		return;
	}
	else
	{
		UIText.Visible = false;
	}
	if (Size.x == 0 || Size.y == 0)
	{
		float width = UIText.GetMaxSizeLine(*Text);
		float  height = static_cast<float>(Font.GetHieght());
		Rect.x1 = width + 8;
		Rect.y1 = height + 2;
	}
	UIText.Text = Text;
	UIText.Font = Font;
	UIText.Rect = Rect;
	
	UIText.Style.set(true, UIText.ST_CenterOfHeight);
	UITextureBackground.Rect = Rect;
	UITextureBackground.Color = Color;
	UITextureBackground.Visible = true;

	if (Style.is(S_Submenu))
	{
		UITriangleSubMenu.Visible = false;
		UITriangleSubMenu.Position=Position;
		UITriangleSubMenu.Position.x += Size.x - Size.y;
		UITriangleSubMenu.Size.x = Size.y;
		UITriangleSubMenu.Size.y = Size.y;
		UITriangleSubMenu.Style.set(true, BearUITriangle::S_TriangleRight);
		UITriangleSubMenu.Scale = 0.4f;
	}
	else
	{
		UITriangleSubMenu.Visible = true;
	}
	BearUIItem::Reset();
}

void BearUI::Classic::BearUIMenuItem::KillFocus()
{
	BearUIItem::KillFocus();
	if (Style.is(S_Border))
	{
		return;
	}
	UITextureBackground.Visible = true;
	if (Menu)
		Menu->Visible = true;
}

bool BearUI::Classic::BearUIMenuItem::OnMouse(float x, float y)
{
	return BearUIItem::OnMouse(x,y);;
}
