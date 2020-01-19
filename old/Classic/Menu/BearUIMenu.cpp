#include "BearUI.hpp"

BearUI::Classic::BearUIMenu::BearUIMenu()
{
	Color.Set(uint8(27), uint8(27), uint8(27));
	Parent = 0;
}

BearUI::Classic::BearUIMenu::~BearUIMenu()
{
}

BearUI::Classic::BearUIMenuItem & BearUI::Classic::BearUIMenu::Add(const bchar * Text)
{
	BearUIMenuItem*Item =bear_new< BearUIMenuItem>();
	UIItems.push_back(Item);
	Item->Text = Text;
	Item->Parent = this;
	Reset();
	return *Item;
}

void BearUI::Classic::BearUIMenu::AddBorder()
{
	BearUIMenuItem*Item =bear_new< BearUIMenuItem>();
	UIItems.push_back(Item);
	Item->Style.set(true, BearUIMenuItem::S_Border);
	Reset();
}

BearUI::Classic::BearUIMenu & BearUI::Classic::BearUIMenu::AddMenu(const bchar * Text)
{
	BearUIMenuItem*Item =bear_new< BearUIMenuItem>();
	UIItems.push_back(Item);
	Item->Text = Text;

	BearUIMenu*Menu =bear_new< BearUIMenu>();
	UIMenus.push_back(Menu);
	Item->Menu = Menu;
	Item->Parent = this;
	Reset();
	return *Menu;
}

float BearUI::Classic::BearUIMenu::CalcWidth() const
{
	float  width = static_cast<float>(Font.GetHieght()) * 5;;
	for (auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		width =BearMath::max((*b)->UIText.CalcWidth(), width);

	}
	return width+6;
}

float BearUI::Classic::BearUIMenu::CalcHeight() const
{
	return 0.0f;
}

void BearUI::Classic::BearUIMenu::OnMessage(int32 message)
{
	switch (message)
	{
	case M_ItemClick:
		if (Parent)Parent->OnMessage(BearUIMenuBar::M_MenuItemClick);
		break;
	}
	BearUIItem::OnMessage(message);
}

bool BearUI::Classic::BearUIMenu::OnMouse(float x, float y)
{
	if (Visible)return false;
	for (auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		if ((*b)->OnMouse(x, y))
		{
			for (auto b1 = UIItems.begin(), e1 = UIItems.end(); b1 != e1; b1++)
			{
				if(b1!=b)
				(*b1)->KillFocus();
			}
			return true;
		}
	
	}
	return BearUIItem::OnMouse(x,y);
}

void BearUI::Classic::BearUIMenu::Reset()
{
	PopItems();
	float height = static_cast<float>(Font.GetHieght()) + 4;
	float width = static_cast<float>(Font.GetHieght())*5;
	auto color = Color;
	color.Set(uint8(color.GetUint8().x + 27), uint8(color.GetUint8().y + 27), uint8(color.GetUint8().x1 + 27));
	UIBackgroundPlane.Color.Set(uint8(color.GetUint8().x + 27), uint8(color.GetUint8().y + 27), uint8(color.GetUint8().x1 + 27));
	/*bsize max_size_text = 0;
	for(auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		if ((*b)->Menu)
		{
			max_size_text =BearMath::max((*b)->Text.size()+5, max_size_text);
		}
		else
		{
			max_size_text =BearMath::max((*b)->Text.size(), max_size_text);
		}
		
	}
	*/
	for (auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		(*b)->Font = Font;
		(*b)->Color = color;
		(*b)->UIText.Reset();

	}	
	height += 2;
	Size.x = CalcWidth();
	Size.y = 4;
	auto position = Position;
	position.x += 3;
	position.y += 2;
	for (auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		PushItem(*(*b));
		(*b)->Position = position;
		(*b)->Size.x = width;
		if ((*b)->Style.is(BearUIMenuItem::S_Border))
		{
			(*b)->Position.y += 1;
			position.y += 3;
			(*b)->Size.y = 1;
			Size.y += 3;
		}
		else
		{
			
			(*b)->Size.x = width;
			(*b)->Size.y = height;
			position.y += height;
			if ((*b)->Menu)
			{
				(*b)->Flags.set(true, BearUIMenuItem::F_NotHide);
				(*b)->Style.set(true, BearUIMenuItem::S_Submenu);
				(*b)->Menu->Font = Font;
				(*b)->Menu->Parent = Parent;
				(*b)->Menu->Position.y = (*b)->Position.y;
				(*b)->Menu->Position.x = Size.x + Position.x-2;
				(*b)->PushItem((*b)->Menu);
			}
			Size.y += height;
		}
	}
	UIPlane.Rect = Rect;
	UIPlane.Rect +=BearVector4<float>(1, 1, -2, -2);

	UIPlane.Color = Color;
	
	PushItem(&UIPlane);
	UIBackgroundPlane.Rect = Rect;
	PushItem(&UIBackgroundPlane);
	BearUIItem::Reset();
}

void BearUI::Classic::BearUIMenu::Reload()
{
	for (auto b = UIItems.begin(), e = UIItems.end(); b != e; b++)
	{
		(*b)->Font = Font;

	}
	BearUIItem::Reload();
}
