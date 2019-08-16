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
			enum EStyle
			{
				S_LeftRight=1
			};
	
			inline void SetPosition(float position)
			{
				ScrollPosition = position;
				OnMessage(M_ScrollUpdatePosition);
			}
			inline void SetZoneView(float zoneView)
			{
				ScrollZoneView = zoneView;
				Reset();
			}	
		
		private:
				virtual float  CalcWidth() const;
				virtual float  CalcHeight() const;
		protected:
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