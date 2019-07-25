#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIComboBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIComboBox);

		public:
			BearUIComboBox();
			~BearUIComboBox();
			BearCore::BearVector<BearCore::BearString> Items;
			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlane;
			bint SelectItem;
			BearFontRef Font;
			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				CallBack = BearCore::bear_create_class_function_ref(f);
				CallBack_Class = reinterpret_cast<void*>(cl);
			}
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EMessage
			{
				M_SelectItem,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
		private:
			void CBButton();
			void CBListBox();
			BearUIListBox UIListBox;
			BearUIButton UIButton;
			BearUITexture UITexture;
			BearUITexture UITextureBackground;
			BearUIText UIText;
			BearCore::BearClassFunctionRef*CallBack;
			void*CallBack_Class;
		};
	}
}