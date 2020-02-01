#include "BearUI.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
static uint32 version = ('F')<<24|0x1;
BearFont::BearFont() 
{
}

bool BearFont::LoadFromFile(const bchar*name) 
{
	BearFileStream file;
	if (file.Open(name))
	{
		return LoadFromStream(file);
	}
	return false;
}

bool BearFont::LoadFromStream(const BearInputStream & stream)
{
	m_chars_info.clear_not_free();
	m_image.Clear();

	if (stream.ReadUint32() != version)return false;
	m_size = static_cast<bsize>(stream.ReadUint32())+1;
	uint32 count = stream.ReadUint32();
	for (uint32 i = 0; i < count; i++)
	{
		bchar16 c = stream.ReadUint16();
		CharInfo charinfo;
		charinfo.Size.x = stream.ReadFloat();
		charinfo.Size.y = stream.ReadFloat();
		charinfo.TextureUV.x = stream.ReadFloat();
		charinfo.TextureUV.y = stream.ReadFloat();
		charinfo.TextureUV.x1 = stream.ReadFloat();
		charinfo.TextureUV.y1 = stream.ReadFloat();
		charinfo.Advance.x = stream.ReadFloat();
		charinfo.Position.x = stream.ReadFloat();
		charinfo.Position.y = stream.ReadFloat();
		m_chars_info.insert(c, charinfo);
	}
	bsize width =static_cast<bsize>( stream.ReadUint32());
	bsize height = static_cast<bsize>(stream.ReadUint32());
	bsize size = static_cast<bsize>(stream.ReadUint32());
	m_image.Create(width, height, true, 1, TPF_BC4);
	BEAR_ASSERT(m_image.GetSizeInMemory() == size);
	stream.ReadBuffer(*m_image, size);
	return true;
}

bool BearFont::LoadFromBuffer(const BearBufferedReader & stream)
{
	return LoadFromStream(stream);
}

bool BearFont::SaveToFile(const bchar * name)
{
	BearFileStream file;
	if (file.Open(name,file.M_Write))
	{
		file.WriteUint32(version);
		file.WriteUint32(static_cast<uint32>(m_size));
		file.WriteUint32(static_cast<uint32>(m_chars_info.size()));
		auto b = m_chars_info.begin();
		auto e = m_chars_info.end();
		while(b!=e)
		{
			bchar16 c = b->first;
			CharInfo charinfo;
			file.WriteUint16(c);
			file.WriteFloat(charinfo.Size.x);
			file.WriteFloat(charinfo.Size.y);


			file.WriteFloat(charinfo.TextureUV.x);
			file.WriteFloat(charinfo.TextureUV.y);
			file.WriteFloat(charinfo.TextureUV.x1);
			file.WriteFloat(charinfo.TextureUV.y1);

			file.WriteFloat(charinfo.Advance.x);
			file.WriteFloat(charinfo.Position.x);
			file.WriteFloat(charinfo.Position.y);
			b++;
		}
		file.WriteUint32(static_cast<uint32>(m_image.GetSize().x));
		file.WriteUint32(static_cast<uint32>(m_image.GetSize().y));
		file.WriteUint32(static_cast<uint32>(m_image.GetSizeInMemory()));
		file.WriteBuffer(*m_image, m_image.GetSizeInMemory());
		return true;
	}
	return false;
}

BearFont::~BearFont()
{
}


void BearFont::Clear()
{
	m_chars_info.clear_not_free();
	m_image.Clear();
}

bool BearFont::Empty() const
{
	return m_image.Empty() || m_chars_info.size() == 0;
}

BearFactoryPointer<BearRHI::BearRHITexture2D> BearFont::CreateTexture() const
{
	if (m_image.Empty())
		return BearFactoryPointer<BearRHI::BearRHITexture2D>();
	return BearRenderInterface::CreateTexture2D(m_image.GetSize().x, m_image.GetSize().y, m_image.GetMips(), m_image.GetDepth(), m_image.GetFormat(),TU_STATIC, *m_image);
}


bool BearFont::LoadFromTTF(const bchar * file, const bchar16 * chars, bsize width, bsize height, bsize size)
{
	BearFileStream font_file;
	if (!font_file.Open(file))
		return false;

	BearMemoryStream font(font_file);

	FT_Library library = 0;
	FT_Face     face = 0;
	if (FT_Init_FreeType(&library))
	{
		FT_Done_FreeType(library);
		return false;
	}
	if (FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(font.Begin()), static_cast<FT_Long>(font.Size()), 0, &face))
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
		return false;
	}

	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	FT_Set_Char_Size(face, 0,static_cast<FT_F26Dot6>( size * 64),static_cast<FT_UInt>( width), static_cast<FT_UInt>(height));
	FT_Set_Pixel_Sizes(face, 0, static_cast<FT_UInt>(size));;
	bsize chars_size =BearString::GetSize(chars) + 1;

	uint32 x_t = 0, y_t = 0;
	uint32 max_y = 0;
	uint32 size_texture = static_cast<uint32>(bear_recommended_size(static_cast<bsize>(sqrtf(static_cast<float>(chars_size*size*size)))));

	m_image.Create(size_texture, size_texture, 1, 1, TPF_R8);
	m_image.Fill(BearColor::Transparent);

	m_size =  static_cast<bsize>(face->size->metrics.height) / static_cast<bsize>(1 << 6);
	m_max_hieght = m_size;
	for (bsize i = 0; i < chars_size; i++) {

		bchar16 id = chars_size ==i+1 ?L' ':chars[i];
		BEAR_ASSERT(id != L'\r' && id != L'\n' && id != L'	');
		FT_Load_Char(face, id, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT| FT_LOAD_RENDER);
		FT_Glyph glyphDesc;
		FT_Get_Glyph(face->glyph, &glyphDesc);

		FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(glyphDesc)->bitmap;
		unsigned char *data = bitmap.buffer;
		uint32 width_char = bitmap.width;
		uint32 height_char = bitmap.rows;

		BearImage char_img;
		char_img.Create(width_char, height_char, 1, 1, TPF_R8);
		char_img.Fill(BearColor::Black);




		for (uint32 y = 0; y < height_char; ++y)
		{
			for (uint32 x = 0; x < width_char; ++x)
			{

				bsize index = static_cast<bsize> (x + y * width_char);
				((uint8*)*char_img)[index] = data[x];
			}
			data += bitmap.pitch;
		}

		max_y =BearMath::max(height_char, max_y);
		if (x_t + width_char > size_texture)
		{
			x_t = 0; y_t += max_y;
			max_y = 0;
		}

		m_image.Append(x_t, y_t, char_img, 0, 0);

		bsize x = x_t;
		bsize y = y_t;

		x_t += width_char;

		

		float advance = static_cast<float>(face->glyph->metrics.horiAdvance) / static_cast<float>(1 << 6);
		/*float pos_x = static_cast<float>(face->glyph->metrics.horiBearingX) / static_cast<float>(1 << 6);
		float pos_y =/* static_cast<float>(m_size) - ((static_cast<float>(face->glyph->metrics.vertBearingY) / static_cast<float>(1 << 6)));*/
		//BEAR_ASSERT(pos_y >= 0);

		CharInfo charinfo;
		charinfo.Size.x = (static_cast<float>(face->glyph->metrics.width) / static_cast<float>(1 << 6));
		charinfo.Size.y = (static_cast<float>(face->glyph->metrics.height) / static_cast<float>(1 << 6));
		charinfo.TextureUV.x = x / static_cast<float>(size_texture);
		charinfo.TextureUV.y = y / static_cast<float>(size_texture);
		charinfo.TextureUV.x1 = width_char / static_cast<float>(size_texture);
		charinfo.TextureUV.y1 = height_char / static_cast<float>(size_texture);
		charinfo.Advance.x = advance;
		charinfo.Advance.y = static_cast<float>(face->glyph->advance.y >> 6);
		charinfo.Position.x = static_cast<float>(face->glyph->bitmap_left);
		charinfo.Position.y = size - (static_cast<float>(face->glyph->metrics.horiBearingY) / static_cast<float>(1 << 6));
		m_chars_info.insert(id, charinfo);
		m_max_hieght =BearMath::max(m_max_hieght,static_cast<bsize>( charinfo.Position.y + charinfo.Size.y));
	}
	m_image.GenerateMipmap();
	m_image.Convert(TPF_BC4);

	FT_Done_Face(face);
	FT_Done_FreeType(library);
	return true;
}