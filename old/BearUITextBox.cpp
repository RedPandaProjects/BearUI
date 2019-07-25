#include "BearUI.hpp"

BearUI::Classic::BearUITextBox::BearUITextBox(): UICursorPosition(0), UITextShift(0), UICursorShift(0), ShiftPress(false), SelectStart(-1), CtrlPress(false)
{
	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorPlane.Set(uint8(20), uint8(20), uint8(20));
	ColorPlaneBackgroundFocused.Set(uint8(0), uint8(120), uint8(200));
	PushItem(&UIText);
	PushItem(&UIPlaneSelect);
	UIPlaneSelect.Color = ColorPlaneBackgroundFocused;
	UIPlaneSelect.Visible = true;

	UICursor.Color = BearCore::BearColor::White;
	PushItem(&UICursor);
//	UIText.Style.set(true, UIText.ST_CenterOfHeight);
	PushItem(&UIPlane);

	PushItem(&UIPlaneBackground);
	UIText.Flags.set(false, UIText.UI_NoClip);
	UIPlaneSelect.Flags.set(false, UIText.UI_NoClip);

	
}

BearUI::Classic::BearUITextBox::~BearUITextBox()
{
}

void BearUI::Classic::BearUITextBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
	{
		SelectKill(false);
		auto posstion = GetMouseLastPosition();
		if (UICursorZone.inZone(posstion))
		{
			
			bint CursorPosition =	GetCursorPosition(posstion);
			if (CursorPosition < 0)break;
			bint old_UICursorPosition = UICursorPosition;
			UICursorPosition = CursorPosition;
		
			UpdateCursorPosition();
			if (ShiftPress)
			{
				SelectStart = old_UICursorPosition+UITextShift;
				SelectEnd= UICursorPosition + UITextShift;
				SelectShow();
			}
	
			printf("UICursorPosition:%lld\r\n", UICursorPosition);
		}
		MousePress = true;
	}
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUITextBox::Reset()
{
	if (Style.test(S_richTextBox))
	{
		UIText.Flags.set(false, UIText.F_IgnoreLine);
	//	UIText.Flags.set(false, UIText.ST_MaxWidth);
	}
	else
	{
		Rect.y1 = static_cast<float>(Font.GetMaxHieght()) + 2 + 4;
		UIText.Flags.set(true, UIText.F_IgnoreLine);
	}
	
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIPlane.Color = ColorPlane;
	UIText.Rect = UIPlane.Rect;
	UIText.Font = Font;
	UIText.Rect += BearCore::BearVector4<float>(2, 2, -4, -4);
	UIText.Clip = UIText.Rect;
	UIPlaneBackground.Color = ColorPlaneBackground;
	UIPlaneBackground.Rect = Rect;


	UICursor.Position = UIText.Position;
	UICursor.Size.y = static_cast<float>(Font.GetMaxHieght());
	UICursor.Size.x = 1;
	UIPlaneSelect.Clip = UIText.Rect;
	SelectKill();
	BearUIItem::Reset();
}

bool BearUI::Classic::BearUITextBox::OnChar(bchar16 ch)
{
	SelectKill();
	if (ch == L'\b')
	{
		if (UICursorPosition||UITextShift)
			if (static_cast<bint>(Text.size()) > UICursorPosition + UITextShift - 1)
				Text.erase(UICursorPosition + UITextShift - 1,1);
		UIText.Text = Text;
		UIText.Reset();
		UICursorPosition--;
		UpdateCursorPosition();
	}

	else
	{
		if (ch == L'\r')ch = '\n';
		if (ch == L'\n'&&!Style.test(S_richTextBox))return true;
	
		bchar text[] = { BearCore::BearEncoding::ToCurrent(ch) ,0 };
		Text.insert(UICursorPosition + UITextShift, text);
		UIText.Text = Text;
		UIText.Reset();
		UICursorPosition++;
		UpdateCursorPosition();
	}
	return true;
}

bool BearUI::Classic::BearUITextBox::OnKeyDown(BearInput::Key key)
{
	switch (key)
	{
	case BearInput::Key::KeyLControl:
		if (Focused())
		{
			CtrlPress = true;
		}
		break;
	case BearInput::Key::KeyV:
		if (Focused())
		{
			Paste();
		}
		break;
	case BearInput::Key::KeyX:
		if (Focused())
		{
			SelectCut();
		}
		break;
	case BearInput::Key::KeyC:
		if (Focused())
		{
			SelectCopy();
		}
		break;
	case BearInput::Key::KeyDelete:
		if (Focused())
		{
			if (Selected())
			{
				SelectDel();
			}
			else
			{
				if (UICursorPosition || UITextShift)
					if (static_cast<bint>(Text.size()) > UICursorPosition + UITextShift )
						Text.erase(UICursorPosition + UITextShift , 1);
				UIText.Text = Text;
				UIText.Reset();
			}
			
		}
		break;
	case BearInput::Key::KeyLShift:
	case BearInput::Key::KeyRShift:
		if (Focused())
		{
			if (ShiftPress == false)
			{
				SelectKill();
			}
			ShiftPress = true;
		}
		break;
	case BearInput::Key::KeyLeft:
		if (Focused())
		{
			UICursorPosition--;
			UpdateCursorPosition();
			if (ShiftPress)
			{
				if (SelectStart == -1)
				{
					SelectStart = UICursorPosition + UITextShift+1;
					SelectEnd = UICursorPosition + UITextShift+1;
				
				}
				
				SelectEnd--;
				if (SelectEnd < 0)SelectEnd = 0;
				SelectShow();
			}
			else
			{
				SelectKill();
			}
			
		}
		break;
	case BearInput::Key::KeyRight:
		if (Focused())
		{
			UICursorPosition++;
			UpdateCursorPosition();
			if (ShiftPress)
			{
				if (SelectStart == -1)
				{
					SelectStart = UICursorPosition + UITextShift-1;
					SelectEnd = UICursorPosition + UITextShift-1;

				}
				SelectEnd++;
				if (SelectEnd > static_cast<bint>(Text.size()))SelectEnd = static_cast<bint>(Text.size());
				SelectShow();
			}
			else
			{
				SelectKill();
			}
			

		}
		break;
	default:
		BearUIItem::OnKeyDown(key);
	
		break;
	}
	return Focused();
}

bool BearUI::Classic::BearUITextBox::OnKeyUp(BearInput::Key key)
{
	switch (key)
	{
	case BearInput::Key::KeyMouseLeft:
		MousePress = false;
		break;
	case BearInput::Key::KeyLShift:
	case BearInput::Key::KeyRShift:
		ShiftPress = false;
		break;
	case BearInput::Key::KeyLControl:
		CtrlPress = false;
		break;
	default:
		break;
	}
	return 	BearUIItem::OnKeyUp(key);;
}

void BearUI::Classic::BearUITextBox::KillFocus()
{
	CtrlPress = false;
	ShiftPress = false;
	MousePress = false;
	SelectKill();
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUITextBox::Update()
{
	if (Focused() && MousePress)
	{
		UICursorPosition = GetCursorPosition(GetMouseLastPosition());
		

		UpdateCursorPosition();
		if (SelectStart == -1)
		{
			SelectStart = UICursorPosition + UITextShift;
		}
		else
		{
			SelectEnd = UICursorPosition + UITextShift;
			SelectShow();
		}
	

	}
	BearUIItem::Update();
}



void BearUI::Classic::BearUITextBox::UpdateCursorPosition()
{


	if (UICursorPosition < 0)
	{

		UITextShift += UICursorPosition;
		if (UITextShift < 0)UITextShift = 0;
		UICursorPosition = 0;
		float shift = UIText.GetSizeLastLine(*Text, UITextShift);
		
		UIText.Position.x = UIPlane.Position.x + 2 - shift;
		UICursor.Position.x = UIPlane.Position.x + 2;
		UICursor.Position.y = (BearCore::BearString::CountElement(*Text, TEXT('\n'))- BearCore::BearString::CountElement(&Text[UITextShift+ UICursorPosition], TEXT('\n')))*Font.GetHieght()+ UIPlane.Position.y + 2;
		UICursorShift = 0;

	}
	else
	{
		if (UICursorPosition + UITextShift > static_cast<bint>(Text.size()))UICursorPosition = Text.size() - UITextShift;
		float delta = UIText.GetSizeLastLine(&Text[UITextShift], UICursorPosition);

		if (delta + UICursorShift > UIPlane.Size.x - 4)
		{
			UICursorShift = 0;
			while (delta + UICursorShift > UIPlane.Size.x - 4)
			{
				UITextShift++;
				UICursorPosition--;
				//if (UICursorPosition + UITextShift > static_cast<bint>(Text.size()))UICursorPosition = Text.size() - UITextShift;
				delta = UIText.GetSizeLastLine(&Text[UITextShift], UICursorPosition);
			}
			float shift = UIText.GetSizeLastLine(*Text, UITextShift);
			UICursorShift = (UIPlane.Size.x - 4 - delta);
			UIText.Position.x = UIPlane.Position.x + 2 - shift + UICursorShift;
			UICursor.Position.x = UIPlane.Position.x + 2 + delta + UICursorShift;
			UICursor.Position.y = (BearCore::BearString::CountElement(*Text, TEXT('\n')) - BearCore::BearString::CountElement(&Text[UITextShift+ UICursorPosition], TEXT('\n')))*Font.GetHieght() + UIPlane.Position.y + 2;

		}
		else
		{

			UICursor.Position.x = UIPlane.Position.x + 2 + delta + UICursorShift;
			UICursor.Position.y = (BearCore::BearString::CountElement(*Text, TEXT('\n')) - BearCore::BearString::CountElement(&Text[UITextShift+ UICursorPosition], TEXT('\n')))*Font.GetHieght() + UIPlane.Position.y + 2;

		}
	}
	UpdateCursorZone();
}

void BearUI::Classic::BearUITextBox::UpdateCursorZone()
{
	float delta = 0, old_delta = 0;
	for (bsize i = 0; i < Text.size() - UITextShift; i++)
	{
		old_delta = delta;
		delta = UIText.GetMaxSizeLine(&Text[UITextShift], i + 1);
		if (delta  > UIPlane.Size.x)
		{
			UICursorZone.set(UIPlane.Position.x + 2 + UICursorShift, UIText.Position.y, old_delta , UIText.Size.y);
			return;
		}
	}
	UICursorZone.set(UIPlane.Position.x + 2 + UICursorShift, UIText.Position.y, delta , UIText.Size.y);
}

bint BearUI::Classic::BearUITextBox::GetCursorPosition(const BearCore::BearVector2<float> mp)
{
	auto pos = mp - UIText.Position ;
	
	auto pos2 = mp - UIPlane.Position;
	if (pos2.x < 0)return -1;

	bsize shift_line = 0,line=0,line_size=0;
	if (Style.test(S_richTextBox))
	{
		line = static_cast<bsize>(floorf(pos.y / Font.GetHieght()));
		const bchar*dst = *Text;
		for (bsize i = 0; i < line&&dst; i++)
		{
			dst = BearCore::BearString::ToChar(dst, TEXT('\n'));
			if (dst)
			{
				dst++;
			}
		}
		if (dst)
		{
			shift_line = dst - (*Text);
			{
				const bchar* dst2 = BearCore::BearString::ToChar(dst, TEXT('\n'));
				if (dst2)
				{
					line_size = dst2 - (*Text);
				}
				else
				{
					line_size = Text.size();
				}
			}
		}
		else
		{
			line_size = Text.size();
		}
	}

	float delta = 0, old_delta = 0;
	float shift = UIText.GetSizeLastLine(&Text[shift_line], UITextShift);
	for (bsize i = 0; i < Text.size()- UITextShift- shift_line; i++)
	{
		old_delta = delta;
		delta = UIText.GetSizeLastLine(&Text[UITextShift+ shift_line],i+1);
		if (delta + shift  > pos.x)
		{
			float ch = delta - old_delta;
			float ch1 = delta + shift -pos.x;
			if (floorf(ch / ch1) > 1.1f)
			{
				return i+1+ shift_line+ UITextShift;
			}
			else
			{
				return i+ shift_line+ UITextShift;
			}

		}
	}
	
	return line_size-UITextShift;
}

void BearUI::Classic::BearUITextBox::Paste()
{
	if (Selected())
	{
		SelectDel();
	}
	auto str = BearCore::BearString::GetClipboard();
	Text.insert(UICursorPosition+UITextShift,*str);
	UICursorPosition += str.size();
	UpdateCursorPosition();
	UIText.Text = Text;
	UIText.Reset();
}

void BearUI::Classic::BearUITextBox::SelectShow()
{
	if (SelectStart <0&& SelectEnd<0) { UIPlaneSelect.Visible = true; return; }
	if (SelectStart == SelectEnd) { UIPlaneSelect.Visible = true; return; }
	if (static_cast<bsize>(SelectStart) > Text.size()) { UIPlaneSelect.Visible = true; return; }
	
	bint selectStart = SelectStart, selectEnd = SelectEnd;
	if (selectStart > selectEnd)BearCore::bear_swap(selectStart, selectEnd);


	if (static_cast<bsize>(selectEnd) > Text.size())selectEnd = static_cast<bint>(Text.size());
	BEAR_ASSERT(selectStart < selectEnd);
	float delta1 = UIText.GetMaxSizeLine(*Text, static_cast<bsize>(selectStart));
	float delta2 = UIText.GetMaxSizeLine(*Text, static_cast<bsize>(selectEnd));
	UIPlaneSelect.Position.x = UIText.Position.x + delta1 ;
	UIPlaneSelect.Size.x =  delta2 - delta1;
	UIPlaneSelect.Position.y = UIText.Position.y;
	UIPlaneSelect.Size.y = UIText.Size.y;
	UIPlaneSelect.Visible = false;
	UICursor.Visible = true;

}

void BearUI::Classic::BearUITextBox::SelectKill(bool shift_reset)
{
	//printf("SelectKill\r\n");
	SelectStart = -1;
	UIPlaneSelect.Visible = true;
	MousePress = false;
	if(shift_reset)ShiftPress = false;
	UICursor.Visible = false;
}

void BearUI::Classic::BearUITextBox::SelectCopy()
{
	if (SelectStart < 0 && SelectEnd < 0) { return; }
	if (SelectStart == SelectEnd) {  return; }
	if (static_cast<bsize>(SelectStart) > Text.size()) {  return; }
	bint selectStart = SelectStart, selectEnd = SelectEnd;
	if (selectStart > selectEnd)BearCore::bear_swap(selectStart, selectEnd);
	if (static_cast<bsize>(selectEnd) > Text.size())selectEnd = static_cast<bint>(Text.size());
	BEAR_ASSERT(selectStart < selectEnd);
	BearCore::BearString::ToClipboard(&Text[selectStart], selectEnd - selectStart); 

}

void BearUI::Classic::BearUITextBox::SelectDel()
{
	if (SelectStart < 0 && SelectEnd < 0) { return; }
	if (SelectStart == SelectEnd) { return; }
	if (static_cast<bsize>(SelectStart) > Text.size()) { return; }
	bint selectStart = SelectStart, selectEnd = SelectEnd;
	if (selectStart > selectEnd)BearCore::bear_swap(selectStart, selectEnd);
	if (static_cast<bsize>(selectEnd) > Text.size())selectEnd = static_cast<bint>(Text.size());
	BEAR_ASSERT(selectStart < selectEnd);
	Text.erase(selectStart, selectEnd - selectStart);
	UICursorPosition = selectStart-UITextShift;
	UIText.Text = Text;
	UIText.Reset();
	UpdateCursorPosition();
	SelectKill();
}

void BearUI::Classic::BearUITextBox::SelectCut()
{
	SelectCopy();
	SelectDel();

}


