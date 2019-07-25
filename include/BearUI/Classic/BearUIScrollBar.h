#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIScrollBar :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIScrollBar);

		public:
			BearUIScrollBar();
			~BearUIScrollBar();
			BearCore::BearVector<BearCore::BearString> Items;
			float ScrollZoneView;
			float ScrollPosition;
			float ScrollOne;
			BearCore::BearColor ColorBackground;

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				CallBack = BearCore::bear_create_class_function_ref(f);
				CallBack_Class = reinterpret_cast<void*>(cl);
			}
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			enum EMessage
			{
				M_ScrollChange = 0x100,
				M_ScrollUpdatePosition,
			};
			virtual void OnMessage(int32 message);
			virtual bool OnMouse(float x, float y);
			virtual void Reset();
		private:
			void UpdatePosition();
			void AddScrollOne();
			void SubScrollOne();
			BearCore::BearVector<BearCore::BearMemoryRef<BearUIListItem>> UIItems;
			BearUITexture UIBackground;
			BearUIButton UIButton;
			BearUIButton UIButtonDown;
			BearUIButton UIButtonUp;

			BearCore::BearClassFunctionRef*CallBack;
			void*CallBack_Class;

			BearCore::BearVector2<float> MousePosition;
			BearCore::BearVector2<float> StartPosition;
		};
	}
}