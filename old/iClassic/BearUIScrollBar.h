#pragma once
namespace BearUI
{
	namespace Classic
	{

		class BEARUI_API BearUIScrollBar :public BearUIItem
		{
			BEAR_CLASS_WITHOUT_COPY(BearUIScrollBar);

		public:
			BearUIScrollBar();
			~BearUIScrollBar();
			BearVector<BearString> Items;
			float ScrollZoneView;
			float ScrollPosition;
			float ScrollOne;
			BearColor ColorBackground;

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				CallBack =bear_create_class_function_ref(f);
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

			BearClassFunctionRef*CallBack;
			void*CallBack_Class;

			BearVector2<float> MousePosition;
			BearVector2<float> StartPosition;
		};
	}
}