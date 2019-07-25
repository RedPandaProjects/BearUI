#include "BearUI.hpp"

BearUI::Classic::BearUIListBox::BearUIListBox(): SelectItem(-1), CallBack(0)
{
	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorPlane.Set(uint8(20), uint8(20), uint8(20));
	ColorSelectFocus = BearCore::BearColor(uint8(0), uint8(151), uint8(251));
	ColorSelect.Set(uint8(67), uint8(67), uint8(67));
	UIScrollBar.SetCallback(this,&BearUIListBox::CBScrollBar);
}

BearUI::Classic::BearUIListBox::~BearUIListBox()
{
	if (CallBack)CallBack->Destroy();
}


void BearUI::Classic::BearUIListBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_SelectedItem:
		if (CallBack)CallBack->Call<void>(CallBack_Class);
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIListBox::Reset()
{
	PopItems();


	bool view_all = Items.size()*BearUIListItem::GetHieght(Font) > Rect.y1;

	BearCore::BearVector2<float> size = Size;
	if (view_all)
	{
		size.x -=static_cast<float>( Font.GetHieght());
		UIScrollBar.Rect = Rect;
		UIScrollBar.Rect.x1 = static_cast<float>(Font.GetHieght());
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
		UIItems.resize(Items.size());
	}
	{
		
		auto b = UIItems.begin();
		auto e = UIItems.end();
		bsize ID = 0;
		while (b != e)
		{
			(*b)->ID = ID++;
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
		UIItems[i]->ColorSelect = ColorSelect;
		UIItems[i]->ColorSelectFocus = ColorSelectFocus;
		UIItems[i]->Parent = this;
	}
	PushItem(&UIScrollBar);

	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIPlane.Color = ColorPlane;
	PushItem(&UIPlane);
	UIPlaneBackground.Rect = Rect;
	UIPlaneBackground.Color = ColorPlaneBackground;
	PushItem(&UIPlaneBackground);



	BearUIItem::Reset();
	if (SelectItem<0&&bsize(SelectItem) >= Items.size())
		SelectItem = -1;
	else
		UIItems[SelectItem]->OnMessage(BearUIListItem::M_Click);
	BearUIItem::Reset();
}




void BearUI::Classic::BearUIListBox::CBScrollBar()
{
	float var1 = BearUIListItem::GetHieght(Font)*UIItems.size()- (Rect.y1-4);
	for (bsize i = 0; i < UIItems.size(); i++)
	{
		UIItems[i]->Position.set(Position.x + 2 , Position.y + 2 + BearUIListItem::GetHieght(Font)*i - var1 * UIScrollBar.ScrollPosition);
	}
}
