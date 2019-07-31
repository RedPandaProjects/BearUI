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
				S_richTextBox = 1
			};
		protected:
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual bool OnChar(bchar16 ch);
			virtual bool OnKeyDown(BearInput::Key key);
			virtual bool OnKeyUp(BearInput::Key key);
			virtual void KillFocus();
			virtual void Update(BearCore::BearTime time);
			virtual int32 GetCursor(float x,float y);
		private:
			bool Key_PressShift;
			bool Key_PressMouse;
			bool Key_PressCtrl;
			BearCore::BearVector4<float> MouseZone;
			////////////////////////////////////////////////////////////////////
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
			////////////////////////////////////////////////////////////////////
			struct SText
			{
				SText()  :UIText_Shift(0) , UIText_ShiftY(0){}
				BearUIText UIText;
				float UIText_Shift;
				float UIText_ShiftY;
				void UpdatePosition(BearUITexture&UIGlobalPlane);
				bsize GetCountLine(bsize pos);
				bsize GetCountLine(bsize pos1,bsize pos2);
				void Up(bint&position);
				void Down(bint&position);
				void Up(bsize&position);
				void Down(bsize&position);
				bsize GetPositionLine(bsize line);
				bsize GetSizeLine(bsize line);
				////////////////////////////////////////////////////////////////////
				void KillSelect();
				void ShowSelect();
				void Copy();
				void Cut(bint&position);
				void Paste(bint&position);
				void Delete(bint&position);
				inline bool Selected() const { return UIText.Select; }
			private:
	

			} UIText;
			
			////////////////////////////////////////////////////////////////////
			struct SCursor
			{
				SCursor();
				void Reset(SText&UIText);
				void Update(SText&UIText,BearUITexture&UIGlobalPlane);
				void UpdatePosition(SText&UIText, BearUITexture&UIGlobalPlane);
				bint GetPosition(SText&UIText, BearUITexture&UIGlobalPlane, BearCore::BearVector2<float> mouse_position);
				void UpdateShiftRight(SText&UIText, BearUITexture&UIGlobalPlane);
				void UpdateShiftLeft(SText&UIText, BearUITexture&UIGlobalPlane);
				void UpdateShiftUp(SText&UIText, BearUITexture&UIGlobalPlane);
				void UpdateShiftDown(SText&UIText, BearUITexture&UIGlobalPlane);
				void Kill();
				BearUITexture UIPlane;
				bint Position;
			}
			UICursor;
			////////////////////////////////////////////////////////////////////
			BearUIScrollBar UIScrollBarUD;
			void CBScrollBarUD();
			void ScrollBarUD_Update();
			BearUIScrollBar UIScrollBarRL;
			void CBScrollBarRL();
			void ScrollBarRL_Update();
		};
	}
}