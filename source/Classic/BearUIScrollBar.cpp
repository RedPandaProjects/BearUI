#include "BearUI.hpp"

BearUI::Classic::BearUIScrollBar::BearUIScrollBar() :ScrollZoneView(0.2f), ScrollOne(0.2f), ScrollPosition(0.f), CallBack(0)
{
	ColorBackground.Set(uint8(70), uint8(70), uint8(70), uint8(255));
	PushItem(&UIButton);
	PushItem(&UIButtonDown);
	PushItem(&UIButtonUp);
	PushItem(&UIBackground);
	UIButtonUp.SetCallback(this, &BearUIScrollBar::SubScrollOne);
	UIButtonDown.SetCallback(this, &BearUIScrollBar::AddScrollOne);
	UIButton.SetCallback(this, &BearUIScrollBar::UpdatePosition);
}

BearUI::Classic::BearUIScrollBar::~BearUIScrollBar()
{
	if (CallBack)CallBack->Destroy();
}

void BearUI::Classic::BearUIScrollBar::OnMessage(int32 message)
{
	switch (message)
	{
	case M_ScrollUpdatePosition:
		if(Style.test(S_LeftRight))
			UIButton.Position.x = floorf((ScrollPosition *(Rect.x1 - 32 - UIButton.Size.x)) + 16 + Rect.x);
		else
			UIButton.Position.y = floorf((ScrollPosition *(Rect.y1 - 32 - UIButton.Size.y)) + 16 + Rect.y);
		break;
	case M_ScrollChange:
		if(CallBack)CallBack->Call<void>(CallBack_Class);
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

bool BearUI::Classic::BearUIScrollBar::OnMouse(float x, float y)
{
	MousePosition.set(x, y);
	if (!UIButton.IsPress())
		StartPosition.set(x, y);
	return BearUIItem::OnMouse(x,y);;
}



void BearUI::Classic::BearUIScrollBar::Reset()
{
	UIBackground.Rect = Rect;
	UIButton.Rect = Rect;
	UIButtonDown.Rect = Rect;
	UIButtonUp.Rect = Rect;
	if (Style.test(S_LeftRight))
	{
		UIButton.Rect.y += 3;
		UIButton.Rect.y1 -= 6;
		UIButton.Rect.x1 -= 32;
		UIButton.Rect.x1 *= ScrollZoneView;
		UIButton.Rect.x += 16;
		if (ScrollZoneView >= 1.f)UIButton.Visible = true;
		else UIButton.Visible = false;
		UIButtonUp.Rect.x1 = 16;



		UIButtonDown.Rect.x = Rect.x + Rect.x1 - 16;
		UIButtonDown.Rect.x1 = 16;
	}
	else
	{
		UIButton.Rect.x += 3;
		UIButton.Rect.x1 -= 6;
		UIButton.Rect.y1 -= 32;
		UIButton.Rect.y1 *= ScrollZoneView;
		UIButton.Rect.y += 16;
		if (ScrollZoneView >= 1.f)UIButton.Visible = true;
		else UIButton.Visible = false;
		UIButtonUp.Rect.y1 = 16;



		UIButtonDown.Rect.y = Rect.y + Rect.y1 - 16;
		UIButtonDown.Rect.y1 = 16;
	}


	UIButton.Flags.OR( UIButton.F_CallBackPress);
	UIButton.StyleConfig = BearUIButton::StyleWithoutBackground();

	UIBackground.Color = ColorBackground;

	ScrollPosition = 0;
	BearUIItem::Reset();
}


void BearUI::Classic::BearUIScrollBar::UpdatePosition()
{
	if (!Style.test(S_LeftRight))
	{
		float change = MousePosition.y - StartPosition.y;
		UIButton.Position.y += change;
		StartPosition.y = MousePosition.y;
		if (UIButton.Position.y < Rect.y + 16)
			UIButton.Position.y = Rect.y + 16;
		else if (UIButton.Position.y > Rect.y + Rect.y1 - UIButtonDown.Rect.y1 - UIButton.Rect.y1)
			UIButton.Position.y = Rect.y + Rect.y1 - UIButtonDown.Rect.y1 - UIButton.Rect.y1;
		ScrollPosition = (UIButton.Position.y - Rect.y - 16) / (Rect.y1 - 32 - UIButton.Size.y);
		OnMessage(M_ScrollChange);
	}
	else
	{
		float change = MousePosition.x - StartPosition.x;
		UIButton.Position.x += change;
		StartPosition.x = MousePosition.x;
		if (UIButton.Position.x < Rect.x + 16)
			UIButton.Position.x = Rect.x + 16;
		else if (UIButton.Position.x > Rect.x + Rect.x1 - UIButtonDown.Rect.x1 - UIButton.Rect.x1)
			UIButton.Position.x = Rect.x + Rect.x1 - UIButtonDown.Rect.x1 - UIButton.Rect.x1;
		ScrollPosition = (UIButton.Position.x - Rect.x - 16) / (Rect.x1 - 32 - UIButton.Size.x);
		OnMessage(M_ScrollChange);
	}
}

void BearUI::Classic::BearUIScrollBar::AddScrollOne()
{
	ScrollPosition += ScrollOne;
	if (ScrollPosition > 1)ScrollPosition = 1;
	OnMessage(M_ScrollUpdatePosition);
	OnMessage(M_ScrollChange);
}

void BearUI::Classic::BearUIScrollBar::SubScrollOne()
{
	ScrollPosition -= ScrollOne;
	if (ScrollPosition < 0)ScrollPosition = 0;
	OnMessage(M_ScrollUpdatePosition);
	OnMessage(M_ScrollChange);
}
