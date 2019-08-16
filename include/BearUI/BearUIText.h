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
		enum EStyleText
		{
			ST_None,
			ST_CenterOfWidth  =  1<<0,
			ST_CenterOfHeight = 1<<1,
			ST_MaxWidth       = 1 << 2,
			ST_OneLine    = 1<<3,
		};
		enum EWigth
		{
			W_Max,
			W_LastLine,
		};

	public:
		virtual void Reset();
		virtual float  CalcWidth() const;
		virtual float  CalcHeight() const;
		virtual void Draw(BearUI * ui, BearCore::BearTime time);
		virtual void Unload();
		virtual void Reload();
	public:
		static bsize GetCountLine(const BearFontRef &font, const bchar*text, float max_wigth = 0, EStyleText eStyleText = ST_None);
		static float GetWidth(const BearFontRef &font, const bchar*text, float max_wigth = 0, EStyleText eStyleText = ST_None, EWigth eSizeLine = W_Max);
		static float GetWidthWithSizeLimit(const BearFontRef &font, const bchar*text, bsize size,  float max_wigth=0, EStyleText eStyleText = ST_None, EWigth eSizeLine = W_Max);
		static BearCore::BearVector2<float> GetMaxHeightCharInLine(const BearFontRef &font, const bchar*text, EStyleText eStyleText = ST_None);
	private:

		BearUITexture UISelectTexture;
	};
}