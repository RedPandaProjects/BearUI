#include "BearUI.hpp"
#include <math.h>



BearUI::BearUIText::BearUIText():Color(BearCore::BearColor::White)
{
}

BearUI::BearUIText::~BearUIText()
{
}

bsize BearUI::BearUIText::GetCountLine(const bchar * text) const
{
	if (Font.Empty())return 0;
	auto&font = *Font.GetListChars();
	bsize size = BearCore::BearString::GetSize(text);
	BearCore::BearVector2<float> pos;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance * 4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y ++;
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item != font.end())
			{
				if (pos.x + item->second.Advance > Rect.x1&&Style.test(ST_MaxWidth))
				{
					pos.y += 1;
					pos.x = 0;
				}
				else
				{
					pos.x += item->second.Advance;
				}
			}
		}
	}
	return static_cast<bsize>( pos.y)+1;
}

float BearUI::BearUIText::GetMaxSizeLine(const bchar * text) const
{
	if (Font.Empty())return 0;
	auto&font = *Font.GetListChars();
	bsize size = BearCore::BearString::GetSize(text);
	BearCore::BearVector2<float> pos;
	float max_x = 0;
	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ = BearCore::BearEncoding::ToUTF16(text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance * 4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y += Font.GetHieght();
			max_x = BearCore::bear_max(pos.x, max_x);
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance > Rect.x1&&Style.test(ST_MaxWidth))
			{
				pos.y += 1;
				max_x = BearCore::bear_max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance;
			}
		}
	}
	return  BearCore::bear_max(pos.x, max_x);
}


void BearUI::BearUIText::Draw(BearUI * ui, float time)
{
	ui->Render(this);
}

void BearUI::BearUIText::Reset()
{

	if (Font.Empty())return;
	ShiftPosition.set(0, 0);
	if (Style.test(ST_CenterOfHeight))
	{
		float  size_height =static_cast<float>( GetCountLine(*Text)*Font.GetHieght());
		ShiftPosition.y =floorf( (Size.y) / 2 - size_height/2);
	}
	if (Style.test(ST_CenterOfWidth))
	{
		float  size_width = GetMaxSizeLine(*Text);
		ShiftPosition.x = floorf((Size.x) / 2 - size_width / 2);
	}
}

void BearUI::BearUIText::Unload()
{
	Font.UnloadTexture();
}

void BearUI::BearUIText::Reload()
{
	Font.ReloadTexture();
}
