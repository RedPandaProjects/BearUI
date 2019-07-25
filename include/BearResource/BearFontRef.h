#pragma once
namespace BearUI
{
	class BEARUI_API BearFontRef
	{
	
	public:
		BearFontRef();
		~BearFontRef();

		bool LoadFromTTF(const bchar*file,const bchar16*chars, bsize width, bsize height, bsize size);

		bool LoadFromFile(const bchar*file);
		bool LoadFromStream(const BearCore::BearInputStream&stream);
		bool LoadFromBuffer(const BearCore::BearBufferedReader&stream);
		
		bool SaveToFile(const bchar*file);
		
		void Clear();
		bool IsOne()const;
		bool Empty()const;
		void Swap(BearFontRef&right);
		void Copy(const BearFontRef&right);
		void UnloadTexture();
		void ReloadTexture();
		BearFontRef(BearFontRef&&right);
		BearFontRef(const BearFontRef&right);

		BearFontRef& operator=(const BearFontRef&right);
		BearFontRef& operator=( BearFontRef&&right);

		struct CharInfo
		{
			BearCore::BearFVector2 Size;
			BearCore::BearVector4<float> TextureUV;
			BearCore::BearFVector2 Advance;
			BearCore::BearFVector2 Position;
		};
		inline const BearGraphics::BearTexture2DRef*GetTexture() const
		{
			if (m_data.empty())return 0;
			return &m_data.get()->m_texture;
		}
		inline bsize GetHieght()const
		{
			if (m_data.empty())return 0;
			return m_data.get()->m_size;
		}
		inline bsize GetMaxHieght()const
		{
			if (m_data.empty())return 0;
			return m_data.get()->m_max_hieght;
		}
		inline const BearCore::BearMap<bchar16, CharInfo>*GetListChars()const
		{
			if (m_data.empty())return 0;
			return &m_data.get()->m_chars_info;
		}
	private:
		struct data
		{
			data() :m_size(0) , m_max_hieght(0){}
			~data() {}
			BearCore::BearMap<bchar16, CharInfo>  m_chars_info;
			bsize m_size;
			bsize m_max_hieght;
			BearGraphics::BearImage m_image;
			BearGraphics::BearTexture2DRef m_texture;
		};
		BearCore::BearMemoryMultiRef<data> m_data;
	};
}