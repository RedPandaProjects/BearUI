#pragma once
namespace BearUI
{
	class BEARUI_API BearUIText:public BearUIStaticItem
	{
		BEAR_CLASS_NO_COPY(BearUIText);

	public:
		BearUIText();
		~BearUIText();
		BearCore::BearString Text;
		BearCore::BearColor Color;
		BearFontRef Font;
		BearCore::BearVector2<float> ShiftPosition;
		enum StyleText
		{
			ST_None,
			ST_CenterOfWidth  =  1<<0,
			ST_CenterOfHeight = 1<<1,
			ST_MaxWidth       = 1 << 2,
		};

		bsize GetCountLine(const bchar*text)const;
		float GetMaxSizeLine(const bchar*text)const;
	public:
		virtual void Draw(BearUI * ui, float time);
		virtual void Reset();
		virtual void Unload();
		virtual void Reload();
	private:
		
	};
}