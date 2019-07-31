#include "BearUI.hpp"
#include <math.h>



BearUI::BearUIText::BearUIText():Color(BearCore::BearColor::White), Select(0),SelectStart(0),SelectEnd(0)
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
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n')&&!Flags.test(F_IgnoreLine))
		{
			pos.y ++;
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item != font.end())
			{
				if (pos.x + item->second.Advance.x > Rect.x1&&Style.test(ST_MaxWidth))
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
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n') && !Flags.test(F_IgnoreLine))
		{
			pos.y += Font.GetHieght();
			max_x = BearCore::bear_max(pos.x, max_x);
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance.x > Rect.x1&&Style.test(ST_MaxWidth))
			{
				pos.y += 1;
				max_x = BearCore::bear_max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance.x;
			}
		}
	}
	return  BearCore::bear_max(pos.x, max_x);
}

float BearUI::BearUIText::GetMaxSizeLine(const bchar * text, bsize size) const
{
	if (Font.Empty())return 0;
	auto&font = *Font.GetListChars();
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
		else if (ch_ == TEXT('\n') && !Flags.test(F_IgnoreLine))
		{
			pos.y += Font.GetHieght();
			max_x = BearCore::bear_max(pos.x, max_x);
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance.x > Rect.x1&&Style.test(ST_MaxWidth))
			{
				pos.y += 1;
				max_x = BearCore::bear_max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance.x;
			}
		}
	}
	return  BearCore::bear_max(pos.x, max_x);
}

float BearUI::BearUIText::GetSizeLastLine(const bchar * text) const
{
	return GetSizeLastLine(text, BearCore::BearString::GetSize(text));
}

float BearUI::BearUIText::GetSizeLastLine(const bchar * text, bsize size) const
{
	if (Font.Empty())return 0;
	auto&font = *Font.GetListChars();
	size = BearCore::bear_min(BearCore::BearString::GetSize(text), size);
	BearCore::BearVector2<float> pos;
//	float max_x = 0;
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
		else if (ch_ == TEXT('\n') && !Flags.test(F_IgnoreLine))
		{
			pos.y += Font.GetHieght();
			//max_x = BearCore::bear_max(pos.x, max_x);
			pos.x = 0;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance.x > Rect.x1&&Style.test(ST_MaxWidth))
			{
				pos.y += 1;
				//max_x = BearCore::bear_max(pos.x, max_x);
				pos.x = 0;
			}
			else
			{
				pos.x += item->second.Advance.x;
			}
		}
	}
	return  pos.x;
}


float BearUI::BearUIText::GetMaxHeightCharInLine(const bchar * text) const
{
	if (Font.Empty())return 0;
	auto&font = *Font.GetListChars();
	bsize size = BearCore::BearString::GetSize(text);
	BearCore::BearVector2<float> pos;
	float max_y = 0;
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
		else if (ch_ == TEXT('\n') && !Flags.test(F_IgnoreLine))
		{
			return max_y;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item == font.end())continue;
			if (pos.x + item->second.Advance.x > Rect.x1&&Style.test(ST_MaxWidth))
			{
				pos.y += 1;
				pos.x = 0;
				return max_y;
			}
			else
			{
				pos.x += item->second.Advance.x;
				max_y = BearCore::bear_max(item->second.Size.y, max_y);
			}
		}
	}
	return  max_y;
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
	UISelectTexture.Flags.set(Flags.test(UI_NoClip), UI_NoClip);
	UISelectTexture.Clip = Clip;
	UISelectTexture.Color = ColorSelect;
	UISelectTexture.Reset();
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
