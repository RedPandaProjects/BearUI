#include "BearUI.hpp"

BearUI::Classic::BearUIPlane::BearUIPlane():Color(uint8(45), uint8(45), uint8(45))
{
	PushItem(&UIPlane);
}

BearUI::Classic::BearUIPlane::~BearUIPlane()
{
}

float BearUI::Classic::BearUIPlane::CalcWidth() const
{
	return 0.0f;
}

float BearUI::Classic::BearUIPlane::CalcHeight() const
{
	return 0.0f;
}

void BearUI::Classic::BearUIPlane::Reset()
{
	UIPlane.Rect = Rect;
	UIPlane.Color = Color;
	BearUIItem::Reset();
}
