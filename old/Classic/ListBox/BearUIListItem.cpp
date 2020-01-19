#include "BearUI.hpp"

BearUI::Classic::BearUIListItem::BearUIListItem():ID(0), Parent(0)
{
	
	ColorSelectFocus =BearColor(uint8(0), uint8(151), uint8(251));
	ColorSelect.Set(uint8(67), uint8(67), uint8(67));
	Flags. AND (~UI_NoClip);
	PushItem(&UIText);
	UIPlane.Visible = true;
	PushItem(&UIPlane);
	UIText.Flags = UIPlane.Flags = Flags;
}

BearUI::Classic::BearUIListItem::~BearUIListItem()
{
}

float BearUI::Classic::BearUIListItem::GetHieght(const BearFontRef & font)
{
	return static_cast<float>(font.GetHieght()) + 2;
}

float BearUI::Classic::BearUIListItem::CalcWidth() const
{
	return 0.0f;
}

float BearUI::Classic::BearUIListItem::CalcHeight() const
{
	return 0.0f;
}


void BearUI::Classic::BearUIListItem::Update(BearTime time)
{
	UIText.Rect = Rect;
	UIText.Rect.y += 1;
	UIText.Rect.y1 -= 2;
	UIPlane.Rect = Rect;


	return BearUIItem::Update(time);
}

void BearUI::Classic::BearUIListItem::OnMessage(int32 message)
{
	switch (message)
	{
	case M_Click:

		if (Parent)
		{
			Parent->SelectItem = ID;
			Parent->OnMessage(BearUIListBox::M_SelectedItem);
		}
		UIPlane.Color = ColorSelectFocus;
		UIPlane.Visible = false;
		break;
	case M_MouseLClick:
		OnMessage(M_Click);
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}



void BearUI::Classic::BearUIListItem::Reset()
{
	Rect.y1 = static_cast<float>(Font.GetHieght()) + 2;
	UIText.Text = Text;
	UIText.Font = Font;
	UIText.Rect = Rect;
	UIText.Rect.y  += 1;
	UIText.Rect.y1 -= 2;
	UIText.Clip = Clip;

	UIPlane.Rect  = Rect;
	UIPlane.Clip  = Clip;

	BearUIItem::Reset();
}

void BearUI::Classic::BearUIListItem::KillFocus()
{
	if (Parent&&Parent->SelectItem>=0&&static_cast<bsize>(Parent->SelectItem) == ID)
	{
		if (!Parent->Focused())
		{
			if (Parent->Focused())
				UIPlane.Color = ColorSelectFocus;
			else
				UIPlane.Color = ColorSelect;
		}
	}
	else
	{
		UIPlane.Visible = true;
	}
	BearUIItem::KillFocus();
//	UITexture.Color = Color;
}

void BearUI::Classic::BearUIListItem::Reload()
{
	UIText.Font = Font;
	BearUIItem::Reload();
}

