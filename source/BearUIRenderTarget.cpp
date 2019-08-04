#include "BearUI.hpp"

BearUI::BearUIRenderTarget::BearUIRenderTarget():Color(BearCore::BearColor::White), TextureUV(0,0,1,1)
{
//	Texture = BearGraphics::BearDefaultManager::GetTexture2D();
}

BearUI::BearUIRenderTarget::~BearUIRenderTarget()
{
}

void BearUI::BearUIRenderTarget::Draw(BearUI * ui, BearCore::BearTime time)
{
	if (Visible)return;
	m_vertex[0].Position.set(Position.x, Position.y + Size.y);
	m_vertex[1].Position.set(Position.x + Size.x, Position.y);
	m_vertex[2].Position.set(Position.x, Position.y);
	m_vertex[3].Position.set(Position.x + Size.x, Position.y + Size.y);
	m_vertex[0].TextureUV.set(TextureUV.x, TextureUV.y1);
	m_vertex[1].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y + TextureUV.y);
	m_vertex[2].TextureUV.set(TextureUV.x, TextureUV.y);
	m_vertex[3].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y1 + TextureUV.y);
	ui->Render(this);
}

void BearUI::BearUIRenderTarget::Reset()
{
}

void BearUI::BearUIRenderTarget::Unload()
{
//	Texture.Clear();
	RenderTarget.Clear();
}

void BearUI::BearUIRenderTarget::Reload()
{
//	Texture= BearGraphics::BearDefaultManager::GetTexture2D();
}

