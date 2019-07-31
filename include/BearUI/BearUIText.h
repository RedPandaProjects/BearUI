#pragma once
namespace BearUI
{
	class BEARUI_API BearUIText:public BearUIStaticItem
	{
		BEAR_CLASS_NO_COPY(BearUIText);
		friend class BearUI;
	public:
		BearUIText();
		~BearUIText();
		BearCore::BearString Text;
		BearCore::BearColor Color;

		bsize SelectStart;
		bsize SelectEnd;
		bool Select;
		BearCore::BearColor ColorSelect;

		BearFontRef Font;
		BearCore::BearVector2<float> ShiftPosition;
		enum StyleText
		{
			ST_None,
			ST_CenterOfWidth  =  1<<0,
			ST_CenterOfHeight = 1<<1,
			ST_MaxWidth       = 1 << 2,
			F_IgnoreLine    = 1<<3,
		};

		bsize GetCountLine(const bchar*text)const;
		float GetMaxSizeLine(const bchar*text)const;
		float GetMaxSizeLine(const bchar*text,bsize size)const;
		float GetSizeLastLine(const bchar*text)const;
		float GetSizeLastLine(const bchar*text, bsize size)const;
		virtual void Reset();
	public:
		float GetMaxHeightCharInLine(const bchar*text)const;
		virtual void Draw(BearUI * ui, BearCore::BearTime time);

		virtual void Unload();
		virtual void Reload();
	private:
		BearUITexture UISelectTexture;
	};
}