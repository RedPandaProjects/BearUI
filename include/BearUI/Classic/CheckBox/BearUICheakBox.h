#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUICheakBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUICheakBox);
		public:
			BearUICheakBox();
			~BearUICheakBox();
			BearCore::BearColor ColorOn;
			BearCore::BearColor ColorOnSelect;
			BearCore::BearColor ColorOff;
			BearCore::BearColor ColorOffSelect;
			BearCore::BearColor ColorPlaneBackground;
			BearFontRef Font;
			BearCore::BearString Text;
			inline const bool Switched()const {return UICheakBoxSwitch.Switch;}
			void Switch(bool Switch);
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			virtual void Reload();
			virtual void Reset();
		private:
			BearUICheakBoxSwitch UICheakBoxSwitch;
			BearUIText           UIText;
		};
	}
}