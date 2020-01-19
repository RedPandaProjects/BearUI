#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUICheakBox :public BearUIItem
		{
			BEAR_CLASS_WITHOUT_COPY(BearUICheakBox);
		public:
			BearUICheakBox();
			~BearUICheakBox();
			BearColor ColorOn;
			BearColor ColorOnSelect;
			BearColor ColorOff;
			BearColor ColorOffSelect;
			BearColor ColorPlaneBackground;
			BearFontRef Font;
			BearString Text;
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