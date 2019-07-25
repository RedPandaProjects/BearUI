#include "BearUI.hpp"

BearUI::Classic::BearUIPlane::BearUIPlane():Color(uint8(45), uint8(45), uint8(45))
{
	PushItem(&UIPlane);
}

BearUI::Classic::BearUIPlane::~BearUIPlane()
{
}

void BearUI::Classic::BearUIPlane::Reset()
{
	UIPlane.Rect = Rect;
	UIPlane.Color = Color;
	BearUIItem::Reset();
}
