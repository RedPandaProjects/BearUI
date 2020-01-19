#pragma once
namespace BearUI
{

	namespace Classic
	{
	
		class BEARUI_API BearUIMenuBarItem :public BearUIItem
		{
			friend class BearUIMenuBar;
			BEAR_CLASS_WITHOUT_COPY(BearUIMenuBarItem);
		public:
			BearUIMenuBarItem();
			~BearUIMenuBarItem();
			BearColor Color;
			BearFontRef Font;
			BearString Text;
			BearUIMenu*Menu;
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			enum EMesssage
			{
				M_Hide=0x100
			};
			enum EStyle
			{
				S_NotHide = 1,
			};
	
			virtual void Update(BearTime time);
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
			virtual void Reload();
		private:
			BearUIText UIText;
			BearUITexture UIPlane;
			BearUITexture UIPlaneBcackground;
		};
	}
}