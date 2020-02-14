#include "BearUI.hpp"


BearUIText::BearUIText():Color(BearColor::White), Select(0),SelectStart(0),SelectEnd(0)
{
	Font = 0;
}

BearUIText::~BearUIText()
{
}


void BearUIText::Draw(BearUI * ui,BearTime time)
{
	if (!Font)return;
	//if(Select)
	//ui->RenderSelectZone(this);
	ui->Render(this);
}

void BearUIText::Reset()
{

	if (Font==nullptr)return;
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

float BearUIText::CalcWidth() const
{
	return GetWidth(Font, *Text, Rect.x1, static_cast<EStyleText>(*Style));
}

float BearUIText::CalcHeight() const
{
	if (Font == nullptr)return 0;
	bsize count_ln = GetCountLine(Font, *Text, Rect.x1, static_cast<EStyleText>(*Style));
	float result = static_cast<float>((count_ln - 1)*Font->GetHieght());
	result += static_cast<float>(Font->GetMaxHieght());
	return result;
}

void BearUIText::Unload()
{
	Font = 0;
	UISelectTexture.Unload();
}

void BearUIText::Reload(BearUIResourcesManager* manager)
{
	if (Font == nullptr)Font = manager->GetFont(TEXT(""));
	UISelectTexture.Reload(manager);
}

bsize BearUIText::GetCountLine(const BearFont* font_ref, const bchar * text, float max_wigth , EStyleText eStyleText )
{
	if (!font_ref)return 0;
	auto&font = font_ref->GetListChars();
	bsize size =BearString::GetSize(text);
	BearVector2<float> pos;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ =BearEncoding::ToUTF16(text[i]);
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

float BearUIText::GetWidth(const BearFont* font, const bchar * text, float max_wigth, EStyleText eStyleText, EWigth eWigth)
{

	return GetWidthWithSizeLimit(font, text,BearString::GetSize(text), max_wigth, eStyleText, eWigth);
}

float BearUIText::GetWidthWithSizeLimit(const BearFont* font_ref, const bchar * text, bsize size, float max_wigth, EStyleText eStyleText, EWigth eWigth)
{
	if (font_ref ==0)return 0;
	auto&font = font_ref->GetListChars();
	size =BearMath::min(BearString::GetSize(text), size);
	BearVector2<float> pos;
	float max_x = 0;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ =BearEncoding::ToUTF16(text[i]);
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
			pos.y += font_ref->GetHieght();
			if (eWigth != EWigth::W_LastLine)
				max_x =BearMath::max(pos.x, max_x);
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
					max_x =BearMath::max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance.x;
			}
		}
	}
	if (eWigth == EWigth::W_Max)
		return BearMath::max(pos.x, max_x);
	else if (eWigth == EWigth::W_LastLine)
		return  pos.x;
	return BearMath::max(pos.x, max_x);
}



BearVector2<float> BearUIText::GetMaxHeightCharInLine(const BearFont* font_ref, const bchar * text, EStyleText eStyleText )
{
	if (!font_ref)return 	BearVector2<float>();
	auto&font = font_ref->GetListChars();
	bsize size =BearString::GetSize(text);
	BearVector2<float> pos;
	BearVector2<float> max_y;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ =BearEncoding::ToUTF16(text[i]);
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
