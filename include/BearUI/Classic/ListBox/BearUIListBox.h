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

			bint SelectItem;

			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlane;
			BearCore::BearColor ColorSelect;
			BearCore::BearColor ColorSelectFocus;

			BearFontRef Font;

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				m_call_back = BearCore::bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
			inline 	BearCore::BearVector<BearCore::BearString>&GetItems() { m_change = true; return m_items; }
			inline 	const BearCore::BearVector<BearCore::BearString>&GetItems()const { return m_items; }
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
			virtual void Update(BearCore::BearTime time);
			virtual void Reset();
			virtual void Reload();
		private:
			BearCore::BearVector<BearCore::BearString> m_items;
			bool m_change;
			BearCore::BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
			void CBScrollBar();
			BearCore::BearVector<BearCore::BearMemoryRef<BearUIListItem>> UIItems;
			BearUITexture UIPlaneBackground;
			BearUITexture UIPlane;
			BearUIScrollBar UIScrollBar;
		};
	}
}