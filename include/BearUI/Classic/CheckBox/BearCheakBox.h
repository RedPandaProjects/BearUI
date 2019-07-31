#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearCheakBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearCheakBox);
		public:
			BearCheakBox();
			~BearCheakBox();
			BearCore::BearColor ColorOn;
			BearCore::BearColor ColorOnSelect;
			BearCore::BearColor ColorOff;
			BearCore::BearColor ColorOffSelect;
			BearCore::BearColor ColorPlaneBackground;
			BearFontRef Font;
			BearCore::BearString Text;
			inline const bool Switched()const {return UICheakBoxSwitch.Switch;}
			void Switch(bool Switch);
		protected:
			
			virtual void Reset();
		private:
			BearCheakBoxSwitch UICheakBoxSwitch;
			BearUIText           UIText;
		};
	}
}