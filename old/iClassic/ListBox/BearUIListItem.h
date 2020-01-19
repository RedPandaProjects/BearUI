#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUIListBox;
		class BEARUI_API BearUIListItem :public BearUIItem
		{
			BEAR_CLASS_WITHOUT_COPY(BearUIListItem);
			friend BearUIListBox;

		public:
			BearUIListItem();
			~BearUIListItem();
			bsize ID;
			BearString Text;

			BearColor ColorSelect;
			BearColor ColorSelectFocus;

			BearFontRef Font;
			static float GetHieght(const BearFontRef&font);
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			BearUIListBox*Parent;
			virtual void Update(BearTime time);
			enum EMessage
			{
				M_Click = 0x100,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
			virtual void Reload();
		private:
			BearUIText UIText;
			BearUITexture UIPlane;
		};
	};
}