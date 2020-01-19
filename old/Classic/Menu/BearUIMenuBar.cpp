#include "BearUI.hpp"

BearUI::Classic::BearUIMenuBar::BearUIMenuBar()
{
	Visible = false;
	Color.Set(uint8(27), uint8(27), uint8(27));
	ColorBackground.Set(uint8(45), uint8(45), uint8(45));
}

BearUI::Classic::BearUIMenuBar::~BearUIMenuBar()
{

}

BearUI::Classic::BearUIMenu & BearUI::Classic::BearUIMenuBar::Add(const bchar * Text)
{
	BearUIMenuBarItem*Item =bear_new< BearUIMenuBarItem>();
	UIMenuItems.push_back(Item);
	Item->Text = Text;
	Item->Color = Color;
	BearUIMenu*Menu =bear_new< BearUIMenu>();
	UIMenus.push_back(Menu);
	Item->Menu = Menu;
	Menu->Color = Color;
	Reset();
	return *Menu;
}

float BearUI::Classic::BearUIMenuBar::CalcWidth() const
{
	float result = 0;
	for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
	{
	
		result += (*b)->CalcWidth();
	}
	return result;
}

float BearUI::Classic::BearUIMenuBar::CalcHeight() const
{
	return static_cast<float>(Font.GetHieght()) + 8;
}



void BearUI::Classic::BearUIMenuBar::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MenuItemClick:
		KillFocus();
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIMenuBar::Reset()
{
	PopItems();
	auto position = Position;
	position.y += 2;
	for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
	{
		(*b)->Font = Font;
		(*b)->Color = Color;
		(*b)->Menu->Color = Color;;
		(*b)->Menu->Parent = this;
		(*b)->Position = position;
		position.x += (*b)->CalcHeight();
		PushItem(**b);
	}
	Rect.y1 = CalcHeight();
	UIPlane.Rect = Rect;
	UIPlane.Color = ColorBackground;
	PushItem(&UIPlane);
	BearUIItem::Reset();
}

void BearUI::Classic::BearUIMenuBar::Update(BearTime time)
{
	if (Focused())
	{
		for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
		{
			(*b)->Flags.set(true, BearUIMenuBarItem::S_NotHide);
		}
	}
	else
	{
		for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
		{
			(*b)->Flags.set(false, BearUIMenuBarItem::S_NotHide);
		}
	}
	BearUIItem::Update(time);
}

bool BearUI::Classic::BearUIMenuBar::OnMouse(float x, float y)
{
	if (Visible)return false;
	for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
	{
		if ((*b)->OnMouse(x, y))
		{
			for (auto b1 = UIMenuItems.begin(), e1 = UIMenuItems.end(); b1 != e1; b1++)
			{
				if (b1 != b)
					(*b1)->KillFocus();
			}
			return true;
		}

	}
	return BearUIItem::OnMouse(x,y);
}

void BearUI::Classic::BearUIMenuBar::KillFocus()
{
	//printf("kill focus \r\n");
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUIMenuBar::Reload()
{
	for (auto b = UIMenuItems.begin(), e = UIMenuItems.end(); b != e; b++)
	{
		(*b)->Font = Font;
	}
	BearUIItem::Reload();
}
