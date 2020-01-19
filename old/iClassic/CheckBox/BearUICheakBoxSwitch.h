#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUICheakBoxSwitch :public BearUIItem
		{
			friend class BearUICheakBox;
			BEAR_CLASS_WITHOUT_COPY(BearUICheakBoxSwitch);
		public:
			BearUICheakBoxSwitch();
			~BearUICheakBoxSwitch();
			BearColor ColorOn;
			BearColor ColorOnSelect;
			BearColor ColorOff;
			BearColor ColorOffSelect;
			bool Switch;
			BearColor ColorPlaneBackground;
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
		private:
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
		};
	}
}