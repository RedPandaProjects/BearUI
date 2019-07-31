#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUICursorText:public BearUICursorBase
		{
			BEAR_CLASS_NO_COPY(BearUICursorText);
		public:
			BearUICursorText(bsize sizeText);
			virtual ~BearUICursorText();
			static constexpr int32 Type = 0xE000000;
		protected:
			virtual void Draw(BearUI * ui, BearCore::BearTime time);
			virtual void Reset();
			virtual void Unload();
			virtual void Reload();
		private:
			BearUITexture UITextureUp;
			BearUITexture UITextureMidle;
			BearUITexture UITextureDown;
			bsize SizeText;
		};
	}
}