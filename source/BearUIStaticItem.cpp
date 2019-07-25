#include "BearUI.hpp"

BearUI::BearUIStaticItem::BearUIStaticItem():Rect(0,0,0,0), Visible(false), Clip(0,0,0,0),Style(0),Flags(UI_NoClip)
{
}

BearUI::BearUIStaticItem::~BearUIStaticItem()
{
} 

void BearUI::BearUIStaticItem::Draw(BearUI * ui, float time)
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
