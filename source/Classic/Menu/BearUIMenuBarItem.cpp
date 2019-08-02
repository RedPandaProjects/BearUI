#include "BearUI.hpp"

BearUI::Classic::BearUIMenuBarItem::BearUIMenuBarItem():Menu(0)
{
	Color.Set(uint8(27), uint8(27), uint8(27));
}

BearUI::Classic::BearUIMenuBarItem::~BearUIMenuBarItem()
{
}

void BearUI::Classic::BearUIMenuBarItem::Update(BearCore::BearTime time)
{
	BearUIItem::Update(time);
	if (Flags.is(S_NotHide) && MouseEntered())
	{
		UIPlane.Visible = false;
		if(Menu)
			Menu->Visible = false;

	}
}

void BearUI::Classic::BearUIMenuBarItem::OnMessage(int32 message)
{
	BearUIItem::OnMessage(message);
	switch (message)
	{
	case M_MouseEnter:
		UIPlaneBcackground.Visible = false;
		break;
	case M_MouseLevae:
		if (Flags.is(S_NotHide))
			break;
		UIPlaneBcackground.Visible = true;
	
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIMenuBarItem::Reset()
{
	PopItems();
	UIText.Text = Text;
	UIText.Font = Font;
	UIText.Position = Position+BearCore::BearVector2<float>(static_cast<float>(Font.GetHieght())/2.f,2);
	UIText.Size.x = UIText.GetMaxSizeLine(*Text);
	UIText.Size.y = static_cast<float>(Font.GetHieght());
	Size.x = UIText.GetMaxSizeLine(*Text)+ static_cast<float>(Font.GetHieght());
	Size.y =static_cast<float>( Font.GetHieght())+4;
	
	UIPlane.Color = Color;
	UIPlaneBcackground.Color.Set(uint8(Color.GetUint8().x + 54), uint8(Color.GetUint8().y + 54), uint8(Color.GetUint8().x1 + 54));
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1,1,-2,0);
	UIPlaneBcackground.Rect = Rect;
	PushItem(&UIText);
	PushItem(&UIPlane);
	PushItem(&UIPlaneBcackground);
	
	if (Menu)
	{
		Menu->Position = Position;
		Menu->Position.y += Size.y;
		Menu->Visible=true;
		Menu->Font = Font;
		PushItem(Menu);
	}
	BearUIItem::Reset();
}

void BearUI::Classic::BearUIMenuBarItem::KillFocus()
{

	if (Menu)
	{
		Menu->Visible = true;
	}
	//Flags.set(false, MBI_BarFocus);
	UIPlane.Visible = true;
	UIPlaneBcackground.Visible = true;
	BearUIItem::KillFocus();
}


