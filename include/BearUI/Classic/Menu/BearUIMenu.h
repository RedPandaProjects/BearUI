#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenuBar;
		class BEARUI_API BearUIMenu :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIMenu);
		public:
			BearUIMenu();
			~BearUIMenu();
			BearCore::BearColor Color;
			BearFontRef Font;
			BearUIMenuItem&Add(const bchar*Text);
			void AddBorder();
			BearUIMenu&AddMenu(const bchar*Text);
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EMessage
			{
				M_ItemClick=0x100,
			};
			BearUIMenuBar*Parent;
			virtual void OnMessage(int32 message);
		protected:
	
			virtual bool OnMouse(float x, float y);
			virtual void Reset();
		private:
			BearUITexture UIPlane;
			BearUITexture UIBackgroundPlane;
			BearCore::BearVector<BearCore::BearMemoryRef<BearUIMenuItem>> UIItems;
			BearCore::BearVector<BearCore::BearMemoryRef<BearUIMenu>> UIMenus;
		};
	}
}