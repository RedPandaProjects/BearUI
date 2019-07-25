#pragma once
namespace BearUI
{

	namespace Classic
	{
		class BEARUI_API BearUIMenu;
		class BEARUI_API BearUIMenuItem :public BearUIItem
		{
			friend class BearUIMenu;
			BEAR_CLASS_NO_COPY(BearUIMenuItem);
		public:
		
			
			BearUIMenuItem();
			~BearUIMenuItem();
			BearCore::BearColor Color;
			BearCore::BearString Text;
			BearFontRef Font;
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EFlags
			{
				F_NotHide = 1,
			};
			enum EStyle
			{
				S_Submenu = 1,
				S_Border = 2,
		};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				if (CallBack)CallBack->Destroy();
				CallBack = BearCore::bear_create_class_function_ref(f);
				CallBack_Class = reinterpret_cast<void*>(cl);
			}
			virtual bool OnMouse(float x, float y);
		private:
			BearCore::BearClassFunctionRef*CallBack;
			void*CallBack_Class;
			BearUIMenu*Menu;
			BearUIMenu*Parent;
			BearUIText    UIText;
			BearUITriangle    UITriangleSubMenu;
			BearUITexture UITextureBackground;
		};
	}
}