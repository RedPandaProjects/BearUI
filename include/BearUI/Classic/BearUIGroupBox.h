#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUIGroupBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIGroupBox);
		public:
			BearUIGroupBox();
			~BearUIGroupBox();
			BearFontRef Font;
			BearCore::BearString Text;
			BearCore::BearColor Color;
			BearCore::BearColor ColorBackground;
			BearCore::BearColor ColorBackgroundFocused;
		private:
			virtual float  CalcHeight() const;
			virtual float  CalcWidth() const;
		protected:
			virtual void OnMessage(int32 message);
			virtual void KillFocus();
			virtual void Reset();
			virtual bool OnKeyDown(BearInput::Key key);
			virtual void Reload();
		private:
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackgound;
			BearUIText UIText;
		};
	}
}