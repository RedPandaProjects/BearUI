#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenuBar :public BearUIItem
		{
			friend class BearUIMenu;
			BEAR_CLASS_NO_COPY(BearUIMenuBar);
		public:
			BearUIMenuBar();
			~BearUIMenuBar();
			BearCore::BearColor Color;
			BearCore::BearColor ColorBackground;
			BearFontRef Font;
			BearUIMenu&Add(const bchar*Text);
			float GetHeight();
		protected:
			enum EMessage
			{
				M_MenuItemClick=0x100,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void Update(BearCore::BearTime time);
			virtual bool OnMouse(float x, float y);
			virtual void KillFocus();
		private:
			BearUITexture UIPlane;
			BearCore::BearVector< BearCore::BearMemoryRef< BearUIMenuBarItem>> UIMenuItems;
			BearCore::BearVector<BearCore::BearMemoryRef< BearUIMenu>> UIMenus;
		};
	}
}