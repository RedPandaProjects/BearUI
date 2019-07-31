#include "BearUI.hpp"

BearUI::Classic::BearUITextBox::BearUITextBox():Key_PressMouse(false), Key_PressShift(false), Key_PressCtrl(false)
{

	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorPlane.Set(uint8(20), uint8(20), uint8(20));
	ColorPlaneBackgroundFocused.Set(uint8(0), uint8(120), uint8(200));
	PushItem(&UICursor.UIPlane);
	PushItem(&UIText.UIText);
	PushItem(&UIScrollBarUD);
	PushItem(&UIScrollBarRL);
	PushItem(&UIPlane);
	PushItem(&UIPlaneBackground);
	UIScrollBarUD.SetCallback(this, &BearUITextBox::CBScrollBarUD);
	UIScrollBarRL.SetCallback(this, &BearUITextBox::CBScrollBarRL);	
	UIScrollBarRL.Style.set(true, UIScrollBarRL.S_LeftRight);
	UICursor.UIPlane.Flags.set(false, UIText.UIText.UI_NoClip);
	UIText.UIText.Flags.set(false, UIText.UIText.UI_NoClip);
}

BearUI::Classic::BearUITextBox::~BearUITextBox()
{
}

void BearUI::Classic::BearUITextBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
		if (!UIPlane.Rect.inZone(GetMouseLastPosition()))break;
		UICursor.Position = UICursor.GetPosition(UIText, UIPlane, GetMouseLastPosition());
		UICursor.Update(UIText,UIPlane);
		UIText.KillSelect();
		UIText.UIText.SelectStart = UICursor.Position;
		UIPlaneBackground.Color = ColorPlaneBackgroundFocused;
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
		 UIText.UIText.Flags.set(false,  UIText.UIText.F_IgnoreLine);
		 Rect.x1 -= static_cast<float>(Font.GetHieght());
		 Rect.y1 -= static_cast<float>(Font.GetHieght());
		 ////////////////////////////////////////////////////////////////////
		 UIScrollBarUD.Position = Position;
		 UIScrollBarUD.Position.x += Rect.x1 ;
		 UIScrollBarUD.Size.y = Size.y-1;
		 UIScrollBarUD.Size.x = static_cast<float>(Font.GetHieght());
		 UIScrollBarUD.Visible = false;
		 ////////////////////////////////////////////////////////////////////
		 UIScrollBarRL.Position = Position;
		 UIScrollBarRL.Position.y += Rect.y1 ;
		 UIScrollBarRL.Size.x = Size.x - 1;
		 UIScrollBarRL.Size.y = static_cast<float>(Font.GetHieght());
		 UIScrollBarRL.Visible = false;
		 ////////////////////////////////////////////////////////////////////
		 UIPlaneBackground.Color = ColorPlaneBackground;
		 UIPlaneBackground.Rect =Rect;
		 UIPlaneBackground.Rect += BearCore::BearVector4<float>(0, 0,  static_cast<float>(Font.GetHieght()),  static_cast<float>(Font.GetHieght()));
	}
	else
	{
		Rect.y1 = static_cast<float>(Font.GetMaxHieght()) + 2 + 4;
		UIText.UIText.Flags.set(true,  UIText.UIText.F_IgnoreLine);
		UIScrollBarUD.Visible = true;
		UIScrollBarRL.Visible = true;

		////////////////////////////////////////////////////////////////////
		UIPlaneBackground.Color = ColorPlaneBackground;
		UIPlaneBackground.Rect = Rect;

	}
	////////////////////////////////////////////////////////////////////
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIPlane.Color = ColorPlane;

	////////////////////////////////////////////////////////////////////
	UIText.UIText.Rect = Rect;
	UIText.UIText.Font = Font;
	UIText.UIText.Rect += BearCore::BearVector4<float>(2+1, 2+1, -4-2, -4-2);
	UIText.UIText.Clip = UIText.UIText.Rect;
	MouseZone = UIText.UIText.Rect;
	
	////////////////////////////////////////////////////////////////////
	UICursor.Reset(UIText);
	////////////////////////////////////////////////////////////////////
	UIText.UIText.ColorSelect = ColorPlaneBackgroundFocused;
	////////////////////////////////////////////////////////////////////
	ScrollBarUD_Update();
	ScrollBarRL_Update();
	BearUIItem::Reset();
}

bool BearUI::Classic::BearUITextBox::OnChar(bchar16 ch)
{
	if (ch == L'\b')
	{
		if (UIText.Selected())
		{
			UIText.Delete(UICursor.Position);
			UICursor.Update(UIText, UIPlane);
			Text = UIText.UIText.Text;
		}
		else
		{
			if (UICursor.Position > 0 && Text.size() > static_cast<bsize>(UICursor.Position - 1))
				Text.erase(static_cast<bsize>(UICursor.Position - 1), 1);
			UICursor.Position--;
			UIText.UIText.Text = Text;
			UIText.UIText.Reset();
			UICursor.Update(UIText, UIPlane);
		}
	}
	else
	{
		if (UIText.Selected())
		{
			UIText.Delete(UICursor.Position);
			UICursor.Update(UIText, UIPlane);
			Text = UIText.UIText.Text;
		}
		if (ch == L'\r')ch =L'\n';
		if (ch == L'\n'&&!Style.test(S_richTextBox))return true;
		Text.insert(UICursor.Position,1, BearCore::BearEncoding::ToCurrent( ch));
		 UIText.UIText.Text = Text;
		 UIText.UIText.Reset();
		 UIText.KillSelect();
		UICursor.Position++;
		UICursor.Update(UIText,UIPlane);
	}
	ScrollBarUD_Update();
	ScrollBarRL_Update();
	return true;
}

bool BearUI::Classic::BearUITextBox::OnKeyDown(BearInput::Key key)
{
	if (Focused())
	{
		switch (key)
		{
		case  BearInput::KeyC:
			UIText.Copy();
			break;
		case  BearInput::KeyV:
			UIText.Paste(UICursor.Position);
			UICursor.Update(UIText, UIPlane);
			Text = UIText.UIText.Text;
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;
		case  BearInput::KeyX:
			UIText.Cut(UICursor.Position);
			UICursor.Update(UIText, UIPlane);
			Text = UIText.UIText.Text;
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;
		case  BearInput::KeyDelete:
			if (UIText.Selected())
			{
				UIText.Delete(UICursor.Position);
				UICursor.Update(UIText, UIPlane);
				Text = UIText.UIText.Text;
				ScrollBarUD_Update();
				ScrollBarRL_Update();
			}
			else
			{
				if (UICursor.Position > 0 && Text.size() > static_cast<bsize>(UICursor.Position))
					Text.erase(static_cast<bsize>(UICursor.Position ), 1);
				UIText.UIText.Text = Text;
				UIText.UIText.Reset();
				UICursor.Update(UIText, UIPlane);
				ScrollBarUD_Update();
				ScrollBarRL_Update();
			}
			break;
		case BearInput::KeyLControl:
			Key_PressCtrl = true;
			break;
		case BearInput::KeyMouseLeft:
			if (!MouseZone.inZone(GetMouseLastPosition()))break;
			Key_PressMouse = true;
			break;
		case BearInput::KeyLShift:
		case BearInput::KeyRShift:

			if (Key_PressShift == false)
			{
				UIText.UIText.SelectStart= UICursor.Position;
				UIText.UIText.SelectEnd = UICursor.Position;
			
			}
			Key_PressShift = true;
			break;
		case BearInput::KeyUp:
			if (Key_PressShift)
			{
				UIText.Up(UICursor.Position);
				UICursor.Update(UIText, UIPlane);
				UICursor.Kill();
				UIText.Up(UIText.UIText.SelectEnd);
				UIText.ShowSelect();
			}
			else if (UIText.Selected())
			{
				Key_PressMouse = false;
				UIText.KillSelect();
				UICursor.Position = UIText.UIText.SelectStart;
				UICursor.Update(UIText, UIPlane);
			}
			else if (Style.test(S_richTextBox))
			{
				
				UIText.Up(UICursor.Position);
				UICursor.Update(UIText, UIPlane);
			}
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;
		case BearInput::KeyDown:
			if (Key_PressShift)
			{
				UIText.Down(UICursor.Position);
				UICursor.Update(UIText, UIPlane);
				UICursor.Kill();
				UIText.Down(UIText.UIText.SelectEnd);
				UIText.ShowSelect();
			}
			else if (UIText.Selected())
			{
				Key_PressMouse = false;
				UIText.KillSelect();
				UICursor.Position = UIText.UIText.SelectEnd;
				UICursor.Update(UIText, UIPlane);
			}
			else if (Style.test(S_richTextBox))
			{
				UIText.Down(UICursor.Position);
				UICursor.Update(UIText, UIPlane);
			}
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;
		case BearInput::KeyLeft:
			if (Key_PressShift)
			{
	
				if (UIText.UIText.SelectEnd )				UIText.UIText.SelectEnd--;
				UICursor.Position = UIText.UIText.SelectEnd;
				UICursor.Update(UIText, UIPlane);
				UICursor.Kill();
				UIText.ShowSelect();
			}
			else if (UIText.Selected())
			{
				Key_PressMouse = false;
				UIText.KillSelect();
				UICursor.Position =BearCore::bear_min( UIText.UIText.SelectStart, UIText.UIText.SelectEnd);
				UICursor.Update(UIText, UIPlane);
			}
			else 
			{
				UICursor.Position--;
				UICursor.Update(UIText, UIPlane);
			}
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;
		case BearInput::KeyRight:
			if (Key_PressShift)
			{
				UICursor.Kill();

				UIText.UIText.SelectEnd++;
				if (UIText.UIText.SelectEnd > Text.size())UIText.UIText.SelectEnd = Text.size();
				UICursor.Position = UIText.UIText.SelectEnd;
				UICursor.Update(UIText, UIPlane);
				UICursor.Kill();
				UIText.ShowSelect();
			}
			else if (UIText.Selected())
			{
				Key_PressMouse = false;
				UIText.KillSelect();
				UICursor.Position = BearCore::bear_max(UIText.UIText.SelectStart, UIText.UIText.SelectEnd);
				UICursor.Update(UIText, UIPlane);
			}
			else
			{
				UICursor.Position++;
				UICursor.Update(UIText, UIPlane);
			}
			ScrollBarUD_Update();
			ScrollBarRL_Update();
			break;

		default:
			break;
		}
}
	return BearUIItem::OnKeyDown(key)||Focused();
}

bool BearUI::Classic::BearUITextBox::OnKeyUp(BearInput::Key key)
{
	switch (key)
	{
	case BearInput::KeyLControl:
		Key_PressCtrl = false;
		break;
	case BearInput::KeyMouseLeft:
		Key_PressMouse = false;
		break;
	case BearInput::KeyLShift:
	case BearInput::KeyRShift:
		Key_PressShift = false;
		break;
	}
	return 	BearUIItem::OnKeyUp(key);;
}

void BearUI::Classic::BearUITextBox::KillFocus()
{
	UIPlaneBackground.Color = ColorPlaneBackground;
	Key_PressMouse = false;
	Key_PressShift = false;
	Key_PressCtrl = false;
	UIText.KillSelect();
	UICursor.Kill();
	
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUITextBox::Update(BearCore::BearTime time)
{

	if (Focused()&&Key_PressMouse)
	{
		bint position = UICursor.GetPosition(UIText, UIPlane, GetMouseLastPosition());
		UIText.UIText.SelectEnd = static_cast<bsize>(position);
		if (UIText.UIText.SelectEnd != UIText.UIText.SelectStart)
		{
			UICursor.Position = UIText.UIText.SelectEnd;
			UICursor.Update(UIText, UIPlane);
			UICursor.Kill();
			UIText.ShowSelect();
			ScrollBarUD_Update();
			ScrollBarRL_Update();
		}
	}
	else
	{
		if (Focused()&& !UIText.Selected())	UICursor.UIPlane.Visible = fmodf(time.asseconds(), 1.2f) > 0.6f ? false : true;
	}
	BearUIItem::Update(time);
}

int32 BearUI::Classic::BearUITextBox::GetCursor(float x, float y)
{
	if (UIPlane.Rect.inZone(BearCore::BearVector2<float>(x,y)))
	{
		if(!Key_PressMouse)
			return BearUICursorText::Type;
	}
	return 0;
}

void BearUI::Classic::BearUITextBox::CBScrollBarUD()
{
	UIText.UIText_ShiftY = (static_cast<float>((Text.count_element(TEXT("\n"))+1)*Font.GetHieght()) - (UIText.UIText.Size.y))*UIScrollBarUD.ScrollPosition;
	UIText.UpdatePosition(UIPlane);
	UICursor.UpdatePosition(UIText, UIPlane);
}

void BearUI::Classic::BearUITextBox::ScrollBarUD_Update()
{
	UIScrollBarUD.SetZoneView ( UIText.UIText.Size.y / static_cast<float>((Text.count_element(TEXT("\n")) + 1 )*Font.GetHieght()));
	if (UIText.UIText_ShiftY)
		UIScrollBarUD.SetPosition(UIText.UIText_ShiftY / (static_cast<float>((Text.count_element(TEXT("\n")) + 1) *Font.GetHieght()) - (UIText.UIText.Size.y)));
	else
		UIScrollBarUD.SetPosition(0);

}

void BearUI::Classic::BearUITextBox::CBScrollBarRL()
{
	UIText.UIText_Shift = ((UIText.UIText.GetMaxSizeLine(*UIText.UIText.Text)) - (UIText.UIText.Size.x))*UIScrollBarRL.ScrollPosition;
	UIText.UpdatePosition(UIPlane);
	UICursor.UpdatePosition(UIText, UIPlane);
}

void BearUI::Classic::BearUITextBox::ScrollBarRL_Update()
{
	UIScrollBarRL.SetZoneView(UIText.UIText.Size.x / UIText.UIText.GetMaxSizeLine(*UIText.UIText.Text));
	
	if (UIText.UIText_Shift)
		UIScrollBarRL.SetPosition(UIText.UIText_Shift / (UIText.UIText.GetMaxSizeLine(*UIText.UIText.Text) - (UIText.UIText.Size.x)));
	else
		UIScrollBarRL.SetPosition(0);

}

BearUI::Classic::BearUITextBox::SCursor::SCursor() :Position(0)
{
}

void BearUI::Classic::BearUITextBox::SCursor::Reset(SText & UIText)
{
	Position = 0;
	UIPlane.Visible = true;
	UIPlane.Position =  UIText.UIText.Position;
	UIPlane.Size.x = 1.f;
	UIPlane.Size.y =static_cast<float>(  UIText.UIText.Font.GetMaxHieght());
	UIPlane.Clip = UIText.UIText.Clip;
	UIPlane.Clip += BearCore::BearVector4<float>(-1, -1, 2, 2);

}

void BearUI::Classic::BearUITextBox::SCursor::Update(SText & UIText, BearUITexture&UIGlobalPlane)
{
	if (Position < 0)Position = 0;
	if (static_cast<bsize>(Position) >  UIText.UIText.Text.size())Position =static_cast<bint>(  UIText.UIText.Text.size());
	UIPlane.Visible = false;
	UIPlane.Position.x = 0;
	UIPlane.Position.y = 0;

	UIPlane.Position.x +=  UIText.UIText.GetSizeLastLine(* UIText.UIText.Text,Position);
	UIPlane.Position.y += static_cast<float>(UIText.GetCountLine(Position))*UIText.UIText.Font.GetHieght();
	if (UIPlane.Position.x+ UIText.UIText.Position.x > UIGlobalPlane.Position.x +2+ UIText.UIText.Size.x-4)
	{
		UpdateShiftRight(UIText, UIGlobalPlane);
	}
	if (UIPlane.Position.x + UIText.UIText.Position.x < UIGlobalPlane.Position.x+2 )
	{
		UpdateShiftLeft(UIText, UIGlobalPlane);
	}
	if (UIPlane.Position.y+ UIText.UIText.Position.y+ UIPlane.Size.y > UIGlobalPlane.Position.y + 2 + UIGlobalPlane.Size.y - 4)
	{
		UpdateShiftDown(UIText, UIGlobalPlane);
	}
	if (UIPlane.Position.y + UIText.UIText.Position.y < UIGlobalPlane.Position.y + 2)
	{
		UpdateShiftUp(UIText, UIGlobalPlane);
	}
	UIPlane.Position += UIText.UIText.Position;
	
}

void BearUI::Classic::BearUITextBox::SCursor::UpdatePosition(SText & UIText, BearUITexture & UIGlobalPlane)
{
	if (Position < 0)Position = 0;
	if (static_cast<bsize>(Position) > UIText.UIText.Text.size())Position = static_cast<bint>(UIText.UIText.Text.size());
	UIPlane.Visible = false;
	UIPlane.Position.x = 0;
	UIPlane.Position.y = 0;

	UIPlane.Position.x += UIText.UIText.GetSizeLastLine(*UIText.UIText.Text, Position);
	UIPlane.Position.y += static_cast<float>(UIText.GetCountLine(Position))*UIText.UIText.Font.GetHieght();

	UIPlane.Position += UIText.UIText.Position;

}

bint BearUI::Classic::BearUITextBox::SCursor::GetPosition(SText & UIText, BearUITexture & UIGlobalPlane, BearCore::BearVector2<float> mouse_position)
{
	auto lposition = mouse_position - UIText.UIText.Position ;
	if (lposition.y < 0)
		lposition.y = 0;
	bsize line = static_cast<bsize>(lposition.y / static_cast<float>(UIText.UIText.Font.GetHieght()));

	if (UIText.UIText.Text.count_element(TEXT("\n")) < line)
		line = UIText.UIText.Text.count_element(TEXT("\n"));
	bsize size_line = UIText.GetSizeLine(line);
	bsize position_line = UIText.GetPositionLine(line);
	if (lposition.x < 0)
		return position_line;
	float size_old = 0;
	for (bsize i = 0; i < size_line ; i++)
	{
		float size = UIText.UIText.GetSizeLastLine(&UIText.UIText.Text[position_line], i + 1);
		if (size > lposition.x)
		{
			if (size - lposition.x  >= lposition.x- size_old)
			{
				return  position_line + i;
			}
			else
			{
				return  position_line + i+1;
			}
		
		}
		size_old = size;
	}
	return position_line + size_line;
}

void BearUI::Classic::BearUITextBox::SCursor::UpdateShiftRight(SText & UIText, BearUITexture & UIGlobalPlane)
{
	float SizeLine = UIText.UIText.GetSizeLastLine(*UIText.UIText.Text, static_cast<bsize>(Position));
	UIText.UIText_Shift = SizeLine - UIText.UIText.Size.x;
	UIText.UpdatePosition(UIGlobalPlane);
}

void BearUI::Classic::BearUITextBox::SCursor::UpdateShiftLeft(SText & UIText, BearUITexture & UIGlobalPlane)
{
	float SizeLine = UIText.UIText.GetSizeLastLine(*UIText.UIText.Text, static_cast<bsize>(Position));
	UIText.UIText_Shift = SizeLine;
	UIText.UpdatePosition(UIGlobalPlane);
}

void BearUI::Classic::BearUITextBox::SCursor::UpdateShiftUp(SText & UIText, BearUITexture & UIGlobalPlane)
{
	float SizeLines = static_cast<float>(UIText.GetCountLine(static_cast<bsize>(Position) + 1)* UIText.UIText.Font.GetHieght());
	UIText.UIText_ShiftY = SizeLines;
	UIText.UpdatePosition(UIGlobalPlane);
}

void BearUI::Classic::BearUITextBox::SCursor::UpdateShiftDown(SText & UIText, BearUITexture & UIGlobalPlane)
{
	float SizeLines =static_cast<float>( UIText.GetCountLine(static_cast<bsize>(Position)+1)* UIText.UIText.Font.GetHieght());
	UIText.UIText_ShiftY = SizeLines - UIText.UIText.Size.y + UIPlane.Size.y;;
	UIText.UpdatePosition(UIGlobalPlane);
}

void BearUI::Classic::BearUITextBox::SCursor::Kill()
{
	UIPlane.Visible = true;
}

void BearUI::Classic::BearUITextBox::SText::UpdatePosition(BearUITexture & UIGlobalPlane)
{
	UIText.Position.x = 2 + UIGlobalPlane.Position.x - UIText_Shift;
	UIText.Position.y = 2 + UIGlobalPlane.Position.y - UIText_ShiftY;
}

bsize BearUI::Classic::BearUITextBox::SText::GetCountLine(bsize pos)
{
	pos = BearCore::bear_min(pos, UIText.Text.size());
	bsize result = 0;
	for (bsize i = 0; i < pos; i++)
	{
		if (UIText.Text[i] == TEXT('\n'))result++;
	}
	return result;
}

bsize BearUI::Classic::BearUITextBox::SText::GetCountLine(bsize pos1, bsize pos2)
{
	pos1 = BearCore::bear_min(pos1, UIText.Text.size());
	pos2 = BearCore::bear_min(pos2, UIText.Text.size());
	bsize result = 0;
	for (bsize i = pos1; i < pos2; i++)
	{
		if (UIText.Text[i] == TEXT('\n'))result++;
	}
	return result;
}

void BearUI::Classic::BearUITextBox::SText::Up(bint & position)
{
	if (position < 0)return;
	bsize lines = GetCountLine(static_cast<bsize>(position));
	if (!lines)return;
	bsize old_position = GetPositionLine(lines);
	bsize new_position = GetPositionLine(lines - 1);
	//bsize size_line_old = GetSizeLine(lines );
	bsize size_line_new= GetSizeLine(lines - 1);

	bsize local_position = static_cast<bsize>(position) - old_position;
	if (local_position > size_line_new)local_position = size_line_new;

	new_position += local_position;
	position = static_cast<bint>(new_position);

}

void BearUI::Classic::BearUITextBox::SText::Down(bint & position)
{
	if (position < 0)return;
	bsize global_lines = GetCountLine(UIText.Text.size());
	bsize lposition = GetCountLine(position);
	if (lposition>= global_lines)return;
	bsize old_position = GetPositionLine(lposition);
	bsize new_position = GetPositionLine(lposition+1);
	bsize size_line_new = GetSizeLine(lposition+1);

	bsize local_position = static_cast<bsize>(position) - old_position;
	
	if (local_position > size_line_new)local_position = size_line_new ;

	new_position += local_position;
	position = static_cast<bint>(new_position);
}

void BearUI::Classic::BearUITextBox::SText::Up(bsize & position)
{
	bint&result = *reinterpret_cast<bint*>(&position);
	Up(result);
}

void BearUI::Classic::BearUITextBox::SText::Down(bsize & position)
{
	bint&result = *reinterpret_cast<bint*>(&position);
	Down(result);
}

bsize BearUI::Classic::BearUITextBox::SText::GetPositionLine(bsize line)
{
	if (line == 0)return 0;
	bsize result = 0;
	bsize size = UIText.Text.size();
	for (bsize i = 0; i < size; i++)
	{
		if (UIText.Text[i] == TEXT('\n'))result++;
		if (result == line)return i+1;
	}
	return UIText.Text.size();
}

bsize BearUI::Classic::BearUITextBox::SText::GetSizeLine(bsize line)
{
	bsize position1 = GetPositionLine(line);
	bsize position2 = GetPositionLine(line+1);
	if (position2 != UIText.Text.size())
	{
		return position2 - position1 - 1;
	}
	return position2 - position1;
}

void BearUI::Classic::BearUITextBox::SText::KillSelect()
{
	UIText.Select = false;
}

void BearUI::Classic::BearUITextBox::SText::ShowSelect()
{
	UIText.Select = true;
}

void BearUI::Classic::BearUITextBox::SText::Copy()
{
	if (!Selected())return;
	if (UIText.SelectStart == UIText.SelectEnd) { return; }
	if (static_cast<bsize>(UIText.SelectStart) > UIText.Text.size()) { return; }
	bint selectStart = UIText.SelectStart, selectEnd = UIText.SelectEnd;
	if (selectStart > selectEnd)BearCore::bear_swap(selectStart, selectEnd);
	if (static_cast<bsize>(selectEnd) > UIText.Text.size())selectEnd = static_cast<bint>(UIText.Text.size());
	BEAR_ASSERT(selectStart < selectEnd);
	BearCore::BearString::ToClipboard(&UIText.Text[selectStart], selectEnd - selectStart);
	
}

void BearUI::Classic::BearUITextBox::SText::Cut(bint & position)
{
	Copy();
	Delete(position);
}

void BearUI::Classic::BearUITextBox::SText::Paste(bint & position)
{
	if (Selected())
	{
		Delete(position);
	}
	auto str = BearCore::BearString::GetClipboard();
	UIText.Text.insert(position , *str);
	position += str.size();
}

void BearUI::Classic::BearUITextBox::SText::Delete(bint & position)
{
	if (!Selected())return;
	if (UIText.SelectStart == UIText.SelectEnd) { return; }
	if (static_cast<bsize>(UIText.SelectStart) > UIText.Text.size()) { return; }
	bint selectStart = UIText.SelectStart, selectEnd = UIText.SelectEnd;
	if (selectStart > selectEnd)BearCore::bear_swap(selectStart, selectEnd);
	if (static_cast<bsize>(selectEnd) > UIText.Text.size())selectEnd = static_cast<bint>(UIText.Text.size());
	BEAR_ASSERT(selectStart < selectEnd);
	UIText.Text.erase(selectStart, selectEnd - selectStart);
	position = selectStart;
	KillSelect();
}
