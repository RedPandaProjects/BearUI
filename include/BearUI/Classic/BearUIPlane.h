#pragma once
namespace BearUI
{

	namespace Classic
	{


		class BEARUI_API BearUIPlane :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIPlane);
		public:
			BearUIPlane();
			~BearUIPlane();
			BearCore::BearColor Color;
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