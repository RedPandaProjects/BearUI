#pragma once
namespace BearUI
{

	namespace Classic
	{
	
		class BEARUI_API BearUIMenuBarItem :public BearUIItem
		{
			friend class BearUIMenuBar;
			BEAR_CLASS_NO_COPY(BearUIMenuBarItem);
		public:
			BearUIMenuBarItem();
			~BearUIMenuBarItem();
			BearCore::BearColor Color;
			BearFontRef Font;
			BearCore::BearString Text;
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
	
			virtual void Update(BearCore::BearTime time);
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