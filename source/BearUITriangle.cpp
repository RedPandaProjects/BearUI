#include "BearUI.hpp"

BearUI::BearUITriangle::BearUITriangle():Scale(1),Color(BearCore::BearColor::White)
{
}

BearUI::BearUITriangle::~BearUITriangle()
{
}

float BearUI::BearUITriangle::CalcWidth() const
{
	return 0.0f;
}

float BearUI::BearUITriangle::CalcHeight() const
{
	return 0.0f;
}

void BearUI::BearUITriangle::Draw(BearUI * ui, BearCore::BearTime time)
{
	if (Visible)return;
	ui->Render(this);
}

void BearUI::BearUITriangle::Reset()
{
}

void BearUI::BearUITriangle::Unload()
{
}

void BearUI::BearUITriangle::Reload()
{
}
