#pragma once
namespace BearUI
{
	class BEARUI_API BearUITriangle :public BearUIStaticItem
	{
		friend class BearUI;
		BEAR_CLASS_NO_COPY(BearUITriangle);
	public:
		BearUITriangle();
		~BearUITriangle();
	public:
		BearCore::BearColor Color;
		float Scale;
		enum EStyle
		{
			S_TriangleUp   =0,
			S_TriangleDown =1,
			S_TriangleLeft =3 ,
			S_TriangleRight=7,
		};
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
		BearGraphics::BearVertexDefault m_vertex[3];

	};
}