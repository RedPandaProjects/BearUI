#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIListBox :public BearUIItem
		{
			friend BearUIListItem;
			BEAR_CLASS_NO_COPY(BearUIListBox);

		public:
			BearUIListBox();
			~BearUIListBox();
			BearCore::BearVector<BearCore::BearString> Items;
			bint SelectItem;

			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlane;
			BearCore::BearColor ColorSelect;
			BearCore::BearColor ColorSelectFocus;

			BearFontRef Font;


			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				CallBack = BearCore::bear_create_class_function_ref(f);
				CallBack_Class = reinterpret_cast<void*>(cl);
			}
			virtual void Reset();
		protected:
			enum EMessage
			{
				M_SelectedItem = 0x100,
			};
			virtual void OnMessage(int32 message);
	
		private:

			BearCore::BearClassFunctionRef*CallBack;
			void*CallBack_Class;
			void CBScrollBar();
			BearCore::BearVector<BearCore::BearMemoryRef<BearUIListItem>> UIItems;
			BearUITexture UIPlaneBackground;
			BearUITexture UIPlane;
			BearUIScrollBar UIScrollBar;
		};
	}
}