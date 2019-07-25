#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITextBox :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUITextBox);
		public:
			BearUITextBox();
			~BearUITextBox();
			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlaneBackgroundFocused;
			BearCore::BearColor ColorPlane;
			BearFontRef Font;
			BearCore::BearString Text;
			enum EStyle
			{
				S_richTextBox=1
			};
		protected:
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual bool OnChar(bchar16 ch);
			virtual bool OnKeyDown(BearInput::Key key);
			virtual bool OnKeyUp(BearInput::Key key);
			virtual void KillFocus();
			virtual void Update();
		private:
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
			////////////////////////////////////////////////////////////////////
			BearUIText UIText;
			bsize UIText_ShiftOfChar;
			float UIText_Shift;
			////////////////////////////////////////////////////////////////////
			struct SCursor
			{
				SCursor();
				void Reset(BearUIText&UIText);
				void Update(BearUIText&UIText,BearUITexture&UIGlobalPlane);
				void Kill();
				BearUITexture UIPlane;
				bint Position;
			}
			UICursor;
			
		};
	}
}