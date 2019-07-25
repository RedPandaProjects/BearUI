#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenuBar :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIMenuBar);
		public:
			BearUIMenuBar();
			~BearUIMenuBar();
			BearCore::BearColor Color;
			BearCore::BearColor ColorBackground;
			BearFontRef Font;
			BearUIMenu&Add(const bchar*Text);
			float GetHeight();
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EMessage
			{
				M_MenuItemClick=0x100,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void Update();
			virtual bool OnMouse(float x, float y);
			virtual void KillFocus();
		private:
			BearUITexture UIPlane;
			BearCore::BearVector< BearCore::BearMemoryRef< BearUIMenuBarItem>> UIMenuItems;
			BearCore::BearVector<BearCore::BearMemoryRef< BearUIMenu>> UIMenus;
		};
	}
}