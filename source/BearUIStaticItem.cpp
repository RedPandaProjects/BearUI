#include "BearUI.hpp"

BearUI::BearUIStaticItem::BearUIStaticItem():Rect(0,0,0,0), Visible(false), Clip(0,0,0,0),Style(0),Flags(UI_NoClip)
{
}

BearUI::BearUIStaticItem::~BearUIStaticItem()
{
} 


float BearUI::BearUIStaticItem::CalcWidth() const
{
	return 0.0f;
}

float BearUI::BearUIStaticItem::CalcHeight() const
{
	return 0.0f;
}

void BearUI::BearUIStaticItem::Draw(BearUI * ui, BearCore::BearTime time)
{
}

void BearUI::BearUIStaticItem::Reset()
{
}

void BearUI::BearUIStaticItem::Unload()
{
}

void BearUI::BearUIStaticItem::Reload()
{
	Reset();
}
