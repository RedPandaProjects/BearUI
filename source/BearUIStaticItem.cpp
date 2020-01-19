#include "BearUI.hpp"

BearUIStaticItem::BearUIStaticItem():Rect(0,0,0,0), Visible(false), Clip(0,0,0,0),Style(0),Flags(UI_NoClip)
{
}

BearUIStaticItem::~BearUIStaticItem()
{
} 


float BearUIStaticItem::CalcWidth() const
{
	return 0.0f;
}

float BearUIStaticItem::CalcHeight() const
{
	return 0.0f;
}

void BearUIStaticItem::Draw(BearUI * ui,BearTime time)
{
}

void BearUIStaticItem::Reset()
{
}

void BearUIStaticItem::Unload()
{
}

void BearUIStaticItem::Reload(BearUIResourcesManager* Manager)
{
	Reset();
}
