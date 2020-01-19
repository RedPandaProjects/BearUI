#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenuBar :public BearUIItem
		{
			friend class BearUIMenu;
			BEAR_CLASS_WITHOUT_COPY(BearUIMenuBar);
		public:
			BearUIMenuBar();
			~BearUIMenuBar();
			BearColor Color;
			BearColor ColorBackground;
			BearFontRef Font;
			BearUIMenu&Add(const bchar*Text);
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			enum EMessage
			{
				M_MenuItemClick=0x100,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void Update(BearTime time);
			virtual bool OnMouse(float x, float y);
			virtual void KillFocus();
			virtual void Reload();
		private:
			BearUITexture UIPlane;
			BearVector<BearRef< BearUIMenuBarItem>> UIMenuItems;
			BearVector<BearRef< BearUIMenu>> UIMenus;
		};
	}
}