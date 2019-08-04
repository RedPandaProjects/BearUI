#pragma once
namespace BearUI
{
	class BEARUI_API BearUIRenderTarget :public BearUIStaticItem
	{
		friend class BearUI;
		BEAR_CLASS_NO_COPY(BearUIRenderTarget);
	public:
		BearUIRenderTarget();
		~BearUIRenderTarget();
	public:
		BearCore::BearVector4<float> TextureUV;
		BearGraphics::BearRenderTargetViewRef RenderTarget;
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