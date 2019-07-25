#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearCheakBoxSwitch :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearCheakBoxSwitch);
		public:
			BearCheakBoxSwitch();
			~BearCheakBoxSwitch();
			BearCore::BearColor ColorOn;
			BearCore::BearColor ColorOnSelect;
			BearCore::BearColor ColorOff;
			BearCore::BearColor ColorOffSelect;
			bool Switch;
			BearCore::BearColor ColorPlaneBackground;
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
		private:
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
		};
	}
}