#pragma once
namespace BearUI
{
	class BEARUI_API BearUI
	{
		BEAR_CLASS_STATIC(BearUI);
		friend class BearUITexture;
	public:
		BearUI(bsize width, bsize height);

		void Resize(bsize width, bsize height);
		void Draw(float time);
		void Update(float time);
		void Unload();
		void Reload();
		void Reset();
		void KillFocus();

		void OnMouse(float x,float y);
		void OnKeyDown(BearInput::Key key);
		void OnKeyUp(BearInput::Key key);

		~BearUI();

		enum FontLang
		{
			F_ENG,
			F_RUS,
		};
		BearFontRef GetFont(FontLang lang,bsize size);

		BearUIItem* PushItem(BearUIItem*item);
		BearUIStaticItem* PushItem(BearUIStaticItem*item);
#ifdef BEAR_UI_EXPORTS
	public:
#else
	private:
#endif
		void Render(BearUITexture*texture);
		void Render(BearUIText*text);
	private:
		void UpdateFocus();


		BearGraphics::BearShaderConstantsRef m_color_constant;
		BearGraphics::BearShaderConstantsRef m_screen_constant;

		BearCore::BearVector4<float> m_screen;
		BearGraphics::BearVertexBufferRef m_vertex_buffer;
		BearGraphics::BearIndexBufferRef m_index_buffer;
	

		BearCore::BearVector<BearUIItem*> m_items;
		BearCore::BearVector<BearUIStaticItem*> m_static_items;
		

		struct FontInfo
		{
			FontInfo(FontLang lang, bsize size) :Lang(lang), Size(size) {}
			FontLang Lang;
			bsize Size;
			inline bool operator<(const FontInfo&info)const
			{
				if (Lang == info.Lang)
				{
					return Size < info.Size;
				}
				return Lang < info.Lang;
			}
		};
		BearCore::BearMap<FontInfo, BearFontRef> m_fonts;

		BearCore::BearVector2<bsize> m_size_screen;

		BearUIItem* m_focus_item;
	};
}