#include "BearUI.hpp"

BearUITriangle::BearUITriangle():Scale(1),Color(BearColor::White)
{
}

BearUITriangle::~BearUITriangle()
{
}

float BearUITriangle::CalcWidth() const
{
	return 0.0f;
}

float BearUITriangle::CalcHeight() const
{
	return 0.0f;
}

void BearUITriangle::Draw(BearUI * ui,BearTime time)
{
	if (Visible)return;
	ui->Render(this);
}

void BearUITriangle::Reset()
{
}

void BearUITriangle::Unload()
{
}

void BearUITriangle::Reload(BearUIResourcesManager* Manager)
{
}
