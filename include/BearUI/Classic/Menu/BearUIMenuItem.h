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
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
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
				if (m_call_back)m_call_back->Destroy();
				m_call_back = BearCore::bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
			virtual bool OnMouse(float x, float y);
			virtual void Reload();
		private:
			BearCore::BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
			BearUIMenu*Menu;
			BearUIMenu*Parent;
			BearUIText    UIText;
			BearUITriangle    UITriangleSubMenu;
			BearUITexture UITextureBackground;
		};
	}
}