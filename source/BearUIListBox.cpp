#include "BearUI.hpp"

BearUI::BearUIListBox::BearUIListBox(): SelectItem(-1), CallBack(0)
{
	ColorBackground.Set(uint8(100), uint8(100), uint8(100));
	UIScrollBar.SetCallback(this,&BearUIListBox::CBScrollBar);
}

BearUI::BearUIListBox::~BearUIListBox()
{
	if (CallBack)CallBack->Destroy();
}

void BearUI::BearUIListBox::Draw(BearUI * ui, float time)
{
	return BearUIItem::Draw(ui,time);
}

void BearUI::BearUIListBox::Update()
{
	return BearUIItem::Update();
}

void BearUI::BearUIListBox::OnMessage(int32 message)
{
	switch (message)
	{
	case LB_SelectedItem:
		if (CallBack)CallBack->Call<void>(CallBack_Class);
		break;
	}
}

bool BearUI::BearUIListBox::OnMouse(float x, float y)
{
	return BearUIItem::OnMouse(x,y);
}

bool BearUI::BearUIListBox::OnKeyDown(BearInput::Key key)
{
	return BearUIItem::OnKeyDown(key);
}

bool BearUI::BearUIListBox::OnKeyUp(BearInput::Key key)
{
	return BearUIItem::OnKeyUp(key);
}

void BearUI::BearUIListBox::Reset()
{

	UIBackground.Color = ColorBackground;

	bool view_all = Items.size()*BearUIListItem::GetHieght(Font) > Rect.y1;

	BearCore::BearVector2<float> size = Size;
	if (view_all)
	{
		size.x -= 16;
		UIScrollBar.Rect = Rect;
		UIScrollBar.Rect.x1 = 16;
		UIScrollBar.Rect.x +=size.x;
		UIScrollBar.Visible = false;
		UIScrollBar.ScrollZoneView = Rect.y1/(Items.size()*BearUIListItem::GetHieght(Font)) ;
	}
	else
	{
		UIScrollBar.Visible = true;
	}

	if (Items.size() > UIItems.size())
	{
		for (bsize i = UIItems.size(); i < Items.size(); i++)
		{
			UIItems.push_back(BearCore::bear_new<BearUIListItem>());
			
		}
	}
	else if (Items.size() < UIItems.size())
	{
		auto b = UIItems.begin()+ Items.size();
		auto e = UIItems.end();
		while (b != e)
		{
			PopItem(**b);
			b++;
		}
		UIItems.resize(Items.size());
	}
	{
		
		auto b = UIItems.begin();
		auto e = UIItems.end();
		bsize ID = 0;
		while (b != e)
		{
			(*b)->ID = ID++;
			(*b)->SetCallback(this, &BearUIListBox::CBSelectedItem);
			PushItem(**b);
			b++;
		}
	}



	for (bsize i = 0; i < Items.size(); i++)
	{
		UIItems[i]->Size.set(size.x - 4, size.y - 4);
		UIItems[i]->Position.set(Position.x+2, Position.y+2 + BearUIListItem::GetHieght(Font)*i);
		UIItems[i]->Clip.set(Rect.x+2, Rect.y+2, size.x - 4, size.y - 4);
		UIItems[i]->Font = Font;
		UIItems[i]->Text = Items[i];
	}
	PushItem(&UIScrollBar);
	PushItem(&UIBackground);

	UIBackground.Rect = Rect;
	UIBackground.Color = ColorBackground;

	BearUIItem::Reset();
	if (SelectItem >= Items.size())
		SelectItem = -1;
	else
		UIItems[SelectItem]->OnMessage(BearUIListItem::LI_Click);
}

void BearUI::BearUIListBox::KillFocus()
{
	BearUIItem::KillFocus();
}

void BearUI::BearUIListBox::Unload()
{
	BearUIItem::Unload();
}

void BearUI::BearUIListBox::Reload()
{
	BearUIItem::Reload();
}

void BearUI::BearUIListBox::CBSelectedItem(BearUIListItem * item)
{
	auto b = UIItems.begin();
	auto e = UIItems.end();
	while (b != e)
	{
		if(**b!=item)
		(*b)->KillSelect();
		b++;
	}
	SelectItem = item->ID;
	OnMessage(LB_SelectedItem);
}

void BearUI::BearUIListBox::CBScrollBar()
{
	float var1 = BearUIListItem::GetHieght(Font)*UIItems.size()- (Rect.y1-4);
	for (bsize i = 0; i < UIItems.size(); i++)
	{
		UIItems[i]->Position.set(Position.x + 2 , Position.y + 2 + BearUIListItem::GetHieght(Font)*i - var1 * UIScrollBar.ScrollPosition);
	}
}
