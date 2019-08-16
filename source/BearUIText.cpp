#include "BearUI.hpp"


BearUI::BearUIText::BearUIText():Color(BearCore::BearColor::White), Select(0),SelectStart(0),SelectEnd(0)
{
}

BearUI::BearUIText::~BearUIText()
{
}


void BearUI::BearUIText::Draw(BearUI * ui, BearCore::BearTime time)
{
	if (Font.Empty())return;
	if(Select)
	ui->RenderSelectZone(this);
	ui->Render(this);
}

void BearUI::BearUIText::Reset()
{

	if (Font.Empty())return;
	ShiftPosition.set(0, 0);
/*	if (Style.test(ST_CenterOfHeight))
	{
		float  size_height =static_cast<float>( GetCountLine(*Text)*Font.GetHieght());
		ShiftPosition.y =floorf( (Size.y- size_height) / 2);
	}*/
	if (Style.test(ST_CenterOfWidth))
	{
		float  size_width = CalcWidth();
		ShiftPosition.x = floorf((Size.x) / 2 - size_width / 2);
	}
	UISelectTexture.Flags.set(Flags.test(UI_NoClip), UI_NoClip);
	UISelectTexture.Clip = Clip;
	UISelectTexture.Color = ColorSelect;
	UISelectTexture.Reset();
}

float BearUI::BearUIText::CalcWidth() const
{
	return GetWidth(Font, *Text, Rect.x1, static_cast<EStyleText>(*Style));
}

float BearUI::BearUIText::CalcHeight() const
{
	bsize count_ln = GetCountLine(Font, *Text, Rect.x1, static_cast<EStyleText>(*Style));
	float result = static_cast<float>((count_ln - 1)*Font.GetHieght());
	result += static_cast<float>(Font.GetMaxHieght());
	return result;
}

void BearUI::BearUIText::Unload()
{
	Font.UnloadTexture();
	UISelectTexture.Unload();
}

void BearUI::BearUIText::Reload()
{
	Font.ReloadTexture();
	UISelectTexture.Reload();
}

bsize BearUI::BearUIText::GetCountLine(const BearFontRef & font_ref, const bchar * text, float max_wigth , EStyleText eStyleText )
{
	if (font_ref.Empty())return 0;
	auto&font = *font_ref.GetListChars();
	bsize size = BearCore::BearString::GetSize(text);
	BearCore::BearVector2<float> pos;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n') && !(eStyleText&ST_OneLine))
		{
			pos.y++;
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item != font.end())
			{
				if (pos.x + item->second.Advance.x > max_wigth&&(eStyleText&ST_MaxWidth))
				{
					pos.y += 1;
					pos.x = 0;
				}
				else
				{
					pos.x += item->second.Advance.x;
				}
			}
		}
	}
	return static_cast<bsize>(pos.y) + 1;
}

float BearUI::BearUIText::GetWidth(const BearFontRef & font, const bchar * text, float max_wigth, EStyleText eStyleText, EWigth eWigth)
{

	return GetWidthWithSizeLimit(font, text, BearCore::BearString::GetSize(text), max_wigth, eStyleText, eWigth);
}

float BearUI::BearUIText::GetWidthWithSizeLimit(const BearFontRef & font_ref, const bchar * text, bsize size, float max_wigth, EStyleText eStyleText, EWigth eWigth)
{
	if (font_ref.Empty())return 0;
	auto&font = *font_ref.GetListChars();
	size = BearCore::bear_min(BearCore::BearString::GetSize(text), size);
	BearCore::BearVector2<float> pos;
	float max_x = 0;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n') && (!(eStyleText&ST_OneLine)))
		{
			pos.y += font_ref.GetHieght();
			if (eWigth != EWigth::W_LastLine)
				max_x = BearCore::bear_max(pos.x, max_x);
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance.x > max_wigth&&(eStyleText&ST_MaxWidth))
			{
				pos.y += 1;
				if (eWigth != EWigth::W_LastLine)
					max_x = BearCore::bear_max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance.x;
			}
		}
	}
	if (eWigth == EWigth::W_Max)
		return  BearCore::bear_max(pos.x, max_x);
	else if (eWigth == EWigth::W_LastLine)
		return  pos.x;
	return  BearCore::bear_max(pos.x, max_x);
}



BearCore::BearVector2<float> BearUI::BearUIText::GetMaxHeightCharInLine(const BearFontRef & font_ref, const bchar * text, EStyleText eStyleText )
{
	if (font_ref.Empty())return 	BearCore::BearVector2<float>();
	auto&font = *font_ref.GetListChars();
	bsize size = BearCore::BearString::GetSize(text);
	BearCore::BearVector2<float> pos;
	BearCore::BearVector2<float> max_y;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n') && (!(eStyleText&ST_OneLine)))
		{
			return max_y;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;

			pos.x += item->second.Advance.x;
			if (max_y.x < item->second.Size.y)
			{
				max_y.set(item->second.Size.y, item->second.Position.y);
			}

		}
	}
	return  max_y;
}
