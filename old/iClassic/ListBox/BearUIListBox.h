#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIListBox :public BearUIItem
		{
			friend BearUIListItem;
			BEAR_CLASS_WITHOUT_COPY(BearUIListBox);

		public:
			BearUIListBox();
			~BearUIListBox();

			bint SelectItem;

			BearColor ColorPlaneBackground;
			BearColor ColorPlane;
			BearColor ColorSelect;
			BearColor ColorSelectFocus;

			BearFontRef Font;

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				m_call_back =bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
			inline 	BearVector<BearString>&GetItems() { m_change = true; return m_items; }
			inline 	constBearVector<BearString>&GetItems()const { return m_items; }
		protected:
			enum EMessage
			{
				M_SelectedItem = 0x100,
			};
			virtual void OnMessage(int32 message);
		private:
			virtual float  CalcHeight() const;
			virtual float  CalcWidth() const;
		protected:
			virtual void Update(BearTime time);
			virtual void Reset();
			virtual void Reload();
		private:
			BearVector<BearString> m_items;
			bool m_change;
			BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
			void CBScrollBar();
			BearVector<BearMemoryRef<BearUIListItem>> UIItems;
			BearUITexture UIPlaneBackground;
			BearUITexture UIPlane;
			BearUIScrollBar UIScrollBar;
		};
	}
}