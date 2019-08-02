#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUIPGroupBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIPGroupBox);
		public:
			BearUIPGroupBox();
			~BearUIPGroupBox();
			BearFontRef Font;
			BearCore::BearString Text;
			BearCore::BearColor Color;
			BearCore::BearColor ColorBackground;
			BearCore::BearColor ColorBackgroundFocused;
		protected:
			virtual void OnMessage(int32 message);
			virtual void KillFocus();
			virtual void Reset();
		private:
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackgound;
			BearUIText UIText;
		};
	}
}