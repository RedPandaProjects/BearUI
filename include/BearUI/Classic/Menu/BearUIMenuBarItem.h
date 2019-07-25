#pragma once
namespace BearUI
{

	namespace Classic
	{
	
		class BEARUI_API BearUIMenuBarItem :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIMenuBarItem);
		public:
			BearUIMenuBarItem();
			~BearUIMenuBarItem();
			BearCore::BearColor Color;
			BearFontRef Font;
			BearCore::BearString Text;
			BearUIMenu*Menu;
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EMesssage
			{
				M_Hide=0x100
			};
			enum EStyle
			{
				S_NotHide = 1,
			};
	
			virtual void Update();
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
		private:
			BearUIText UIText;
			BearUITexture UIPlane;
			BearUITexture UIPlaneBcackground;
		};
	}
}