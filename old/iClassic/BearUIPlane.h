#pragma once
namespace BearUI
{

	namespace Classic
	{


		class BEARUI_API BearUIPlane :public BearUIItem
		{
			BEAR_CLASS_WITHOUT_COPY(BearUIPlane);
		public:
			BearUIPlane();
			~BearUIPlane();
			BearColor Color;
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:

			virtual void Reset();
		private:
			BearUITexture UIPlane;
		};
	}
}