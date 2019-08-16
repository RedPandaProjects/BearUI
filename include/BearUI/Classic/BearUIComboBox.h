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
		
			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlane;
			bint SelectItem;
			BearFontRef Font;
			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				m_call_back = BearCore::bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
			inline 	BearCore::BearVector<BearCore::BearString>&GetItems() { m_change = true; return m_items; }
			inline 	const BearCore::BearVector<BearCore::BearString>&GetItems()const { return m_items; }
			virtual float  CalcHeight() const;
		private:
			virtual float  CalcWidth() const;
		protected:
			virtual void Reload();
			enum EMessage
			{
				M_SelectItem,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
			virtual void Update(BearCore::BearTime time);
		private:
			BearCore::BearVector<BearCore::BearString> m_items;
			bool m_change;
			void CBButton();
			void CBListBox();
			BearUIListBox UIListBox;
			BearUIButton UIButton;
			BearUITexture UITexture;
			BearUITexture UITextureBackground;
			BearUIText UIText;
			BearCore::BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
		};
	}
}