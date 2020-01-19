#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenuBar;
		class BEARUI_API BearUIMenu :public BearUIItem
		{
			friend BearUIMenuBar;
			friend BearUIMenuItem;
			BEAR_CLASS_WITHOUT_COPY(BearUIMenu);
		public:
			BearUIMenu();
			~BearUIMenu();
			BearColor Color;
			BearFontRef Font;
			BearUIMenuItem&Add(const bchar*Text);
			void AddBorder();
			BearUIMenu&AddMenu(const bchar*Text);
			virtual float  CalcWidth() const;
		private:
			virtual float  CalcHeight() const;
		protected:
			enum EMessage
			{
				M_ItemClick=0x100,
			};
			BearUIMenuBar*Parent;
			virtual void OnMessage(int32 message);
		protected:
	
			virtual bool OnMouse(float x, float y);
			virtual void Reset();
			virtual void Reload();
		private:
			BearUITexture UIPlane;
			BearUITexture UIBackgroundPlane;
			BearVector<BearMemoryRef<BearUIMenuItem>> UIItems;
			BearVector<BearMemoryRef<BearUIMenu>> UIMenus;
		};
	}
}