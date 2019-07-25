#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUIListBox;
		class BEARUI_API BearUIListItem :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUIListItem);

		public:
			BearUIListItem();
			~BearUIListItem();
			bsize ID;
			BearCore::BearString Text;

			BearCore::BearColor ColorSelect;
			BearCore::BearColor ColorSelectFocus;

			BearFontRef Font;
			static float GetHieght(const BearFontRef&font);


#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			BearUIListBox*Parent;
			virtual void Update();
			enum EMessage
			{
				M_Click = 0x100,
			};
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void KillFocus();
		private:
			BearUIText UIText;
			BearUITexture UIPlane;
		};
	};
}