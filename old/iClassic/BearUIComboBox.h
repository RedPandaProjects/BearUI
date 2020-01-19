#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIComboBox :public BearUIItem
		{
			BEAR_CLASS_WITHOUT_COPY(BearUIComboBox);

		public:
			BearUIComboBox();
			~BearUIComboBox();
		
			BearColor ColorPlaneBackground;
			BearColor ColorPlane;
			bint SelectItem;
			BearFontRef Font;
			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				m_call_back =bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
			inline 	BearVector<BearString>&GetItems() { m_change = true; return m_items; }
			inline 	constBearVector<BearString>&GetItems()const { return m_items; }
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
			virtual void Update(BearTime time);
		private:
			BearVector<BearString> m_items;
			bool m_change;
			void CBButton();
			void CBListBox();
			BearUIListBox UIListBox;
			BearUIButton UIButton;
			BearUITexture UITexture;
			BearUITexture UITextureBackground;
			BearUIText UIText;
			BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
		};
	}
}