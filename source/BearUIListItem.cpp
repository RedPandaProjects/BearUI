#include "BearUI.hpp"

BearUI::BearUIListItem::BearUIListItem():ID(0), CallBack(0)
{
	Color = BearCore::BearColor::Transparent;
	ColorSelected = BearCore::BearColor(uint8(0), uint8(151), uint8(251));
	Flags. and (~UIFlags::UI_NoClip);
	PushItem(&UIText);
	PushItem(&UITexture);
	UIText.Flags = UITexture.Flags = Flags;
}

BearUI::BearUIListItem::~BearUIListItem()
{
	if (CallBack)CallBack->Destroy();
}

float BearUI::BearUIListItem::GetHieght(const BearFontRef & font)
{
	return static_cast<float>(font.GetHieght()) + 2;
}

void BearUI::BearUIListItem::Draw(BearUI * ui, float time)
{
	return BearUIItem::Draw(ui, time);
}

void BearUI::BearUIListItem::Update()
{
	UIText.Rect = Rect;
	UIText.Rect.y += 1;
	UIText.Rect.y1 -= 2;
	UITexture.Rect = Rect;


	return BearUIItem::Update();
}

void BearUI::BearUIListItem::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
		if(CallBack)CallBack->Call<void>(CallBack_Class,this);
		UITexture.Color = ColorSelected;
		break;
	default:
		break;
	}
}

bool BearUI::BearUIListItem::OnMouse(float x, float y)
{
	return BearUIItem::OnMouse(x,y);
}

bool BearUI::BearUIListItem::OnKeyDown(BearInput::Key key)
{
	return BearUIItem::OnKeyDown(key);
}

bool BearUI::BearUIListItem::OnKeyUp(BearInput::Key key)
{
	return BearUIItem::OnKeyUp(key);
}

void BearUI::BearUIListItem::Reset()
{
	Rect.y1 = static_cast<float>(Font.GetHieght()) + 2;
	UIText.Text = Text;
	UIText.Font = Font;
	UIText.Rect = Rect;
	UIText.Rect.y  += 1;
	UIText.Rect.y1 -= 2;
	UIText.Clip = Clip;

	UITexture.Rect  = Rect;
	UITexture.Clip  = Clip;
	UITexture.Color = Color;

	BearUIItem::Reset();
}

void BearUI::BearUIListItem::KillFocus()
{
	BearUIItem::KillFocus();
//	UITexture.Color = Color;
}

void BearUI::BearUIListItem::KillSelect()
{	UITexture.Color = Color;
}

void BearUI::BearUIListItem::Unload()
{
	BearUIItem::Unload();
}

void BearUI::BearUIListItem::Reload()
{
	BearUIItem::Reload();
}
