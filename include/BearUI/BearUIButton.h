#pragma once
namespace BearUI
{
	


	class BEARUI_API BearUIButton :public BearUIItem
	{
		BEAR_CLASS_NO_COPY(BearUIButton);
	public:
		struct StyleDefault
		{
			StyleDefault() :ShowBackground(true)
			{
				Colors[A_Default][CT_Plane].Set(uint8(63), uint8(63), uint8(70));
				Colors[A_Default][CT_Background].Set(uint8(90), uint8(90), uint8(90));

				Colors[A_MouseEnter][CT_Plane].Set(uint8(63), uint8(63), uint8(70));
				Colors[A_MouseEnter][CT_Background].Set(uint8(0), uint8(100), uint8(150));

				Colors[A_MouseClick][CT_Plane].Set(uint8(0), uint8(100), uint8(150));
				Colors[A_MouseClick][CT_Background].Set(uint8(0), uint8(100), uint8(150));

				Colors[A_Disable][CT_Plane].Set(uint8(200), uint8(200), uint8(200));
				Colors[A_Disable][CT_Background].Set(uint8(200), uint8(200), uint8(200));
			}
			enum Action
			{
				A_Default = 0,
				A_MouseEnter,
				A_MouseClick,
				A_Disable,
				A_Count,
			};
			enum ColorType
			{
				CT_Plane,
				CT_Background,
				CT_Count,
			};
			bool ShowBackground;
			BearCore::BearColor Colors[A_Count][CT_Count];
		};

		struct StyleWithoutBackground:public StyleDefault
		{
			StyleWithoutBackground()
			{
				ShowBackground = false;
				Colors[A_Default][CT_Plane].Set(uint8(100), uint8(100), uint8(100));
				Colors[A_MouseEnter][CT_Plane].Set(uint8(150), uint8(150), uint8(150));
				Colors[A_MouseClick][CT_Plane].Set(uint8(230), uint8(230), uint8(230));
				Colors[A_Disable][CT_Plane].Set(uint8(200), uint8(200), uint8(200));
			}
		};
	public:
		BearUIButton();
		~BearUIButton();
		BearFontRef Font;
		BearCore::BearString Text;
		StyleDefault StyleConfig;
	
		template<class CL,typename F>
		inline void SetCallback(CL*cl, F f)
		{
			CallBack = BearCore::bear_create_class_function_ref(f);
			CallBack_Class = reinterpret_cast<void*>(cl);
		}
		enum ButtonFlags
		{
			B_CallBackPress=1,
		};
		enum ButtonStyle
		{
			B_WithoutBackground=1,
		};
		inline bool IsPress()const
		{
			return bPress;
		}
	public:
		virtual void Update();
		virtual void Draw(BearUI * ui, float time);
		virtual void OnMessage(int32 message) ;
		virtual bool OnMouse(float x, float y);
		virtual bool OnKeyDown(BearInput::Key key);
		virtual bool OnKeyUp(BearInput::Key key) ;
		virtual void Reset();
		virtual void Unload();
		virtual void Reload();
		virtual void KillFocus();
	
	private:
		BearUITexture UITexture;
		BearUITexture UITextureBack;
		BearUIText UIText;
		BearCore::BearClassFunctionRef*CallBack;
		void*CallBack_Class;
		bool bPress;
	};
}