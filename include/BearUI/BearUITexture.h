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
	public:
		BearCore::BearVector4<float> TextureUV;
		BearGraphics::BearTexture2DRef Texture;
		BearCore::BearColor Color;
		float Rotation;
#ifdef BEAR_UI_EXPORTS
	public:
#else
	protected:
#endif
		virtual void Draw(BearUI * ui, float time);
		virtual void Reset();
		virtual void Unload();
		virtual void Reload();
	private:
		BearGraphics::BearVertexDefault m_vertex[4];

	};
}