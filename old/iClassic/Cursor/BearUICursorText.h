#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUICursorText:public BearUICursorBase
		{
			BEAR_CLASS_WITHOUT_COPY(BearUICursorText);
		public:
			BearUICursorText(bsize sizeText);
			virtual ~BearUICursorText();
			static constexpr int32 Type = 0xE000000;
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
		
			virtual void Draw(BearUI * ui,BearTime time);
			virtual void Reset();
			virtual void Unload();
			virtual void Reload();
		private:
			BearUITexture UITextureUp;
			BearUITexture UITextureMidle;
			BearUITexture UITextureDown;
			bsize m_size_text;
		};
	}
}