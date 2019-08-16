#pragma once
namespace BearUI
{
	class BEARUI_API BearUITexture :public BearUIStaticItem
	{
		friend class BearUI;
		BEAR_CLASS_NO_COPY(BearUITexture);
	public:
		BearUITexture();
		~BearUITexture();
	private:
		virtual float  CalcWidth() const;
		virtual float  CalcHeight() const;
	public:
		BearCore::BearVector4<float> TextureUV;
		BearGraphics::BearTexture2DRef Texture;
		BearCore::BearColor Color;
		float Rotation;

		virtual void Draw(BearUI * ui, BearCore::BearTime time);
		virtual void Reset();
		virtual void Unload();
		virtual void Reload();
	private:
		BearGraphics::BearVertexDefault m_vertex[4];

	};
}