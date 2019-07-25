#pragma once
namespace BearUI
{
	class BEARUI_API BearUI;
	class BEARUI_API BearUIStaticItem
	{
		BEAR_CLASS_NO_COPY(BearUIStaticItem);
	protected:
		BearUIStaticItem();
		~BearUIStaticItem();
	public:
		union
		{
			BearCore::BearVector4<float> Rect;
			struct
			{
				BearCore::BearVector2<float> Position;
				BearCore::BearVector2<float> Size;
			};
		};
		BearCore::BearVector4<float> Clip;
		enum EFlags
		{
			UI_NoClip = 1 << 31,
			UI_NoMouseEnter=1<<30,
		};
		BearCore::BearFlags<int64> Flags;
		BearCore::BearFlags<int64> Style;
		bool Visible;
	public:
		virtual void Draw(BearUI * ui ,float time);
		virtual void Reset();
		virtual void Unload() ;
		virtual void Reload() ;
	};
}