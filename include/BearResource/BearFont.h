#pragma once
class BEARUI_API BearFont
{
	BEAR_CLASS_WITHOUT_COPY(BearFont)
public:
	BearFont();
	~BearFont();

	bool LoadFromTTF(const bchar* file, const bchar16* chars, bsize width, bsize height, bsize size);

	bool LoadFromFile(const bchar* file);
	bool LoadFromStream(const BearInputStream& stream);
	bool LoadFromBuffer(const BearBufferedReader& stream);

	bool SaveToFile(const bchar* file);

	void Clear();

	bool Empty()const;

	struct CharInfo
	{
		BearFVector2 Size;
		BearVector4<float> TextureUV;
		BearFVector2 Advance;
		BearFVector2 Position;
	};
	BearFactoryPointer<BearRHI::BearRHITexture2D>   CreateTexture() const;
	inline bsize GetHieght()const
	{
		return m_size;
	}
	inline bsize GetMaxHieght()const
	{
		return m_max_hieght;
	} 
	inline const BearMap<bchar16, CharInfo>& GetListChars()const
	{
		return m_chars_info;
	}
private:
	BearMap<bchar16, CharInfo>  m_chars_info;
	bsize m_size;
	bsize m_max_hieght;
	BearImage m_image;
};