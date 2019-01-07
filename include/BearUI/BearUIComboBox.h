#pragma once
namespace BearUI
{
	class BEARUI_API BearUIComboBox :public BearUIItem
	{
		BEAR_CLASS_NO_COPY(BearUIComboBox);

	public:
		BearUIComboBox();
		~BearUIComboBox();
		BearCore::BearVector<BearCore::BearString> Items;
		BearCore::BearColor ColorBackground;
		BearCore::BearColor Color;
		bint SelectItem;
		BearFontRef Font;
		template<class CL, typename F>
		inline void SetCallback(CL*cl, F f)
		{
			CallBack = BearCore::bear_create_class_function_ref(f);
			CallBack_Class = reinterpret_cast<void*>(cl);
		}
	public:
		enum MessageComboBox
		{
			MCB_SelectItem,
		};
		virtual void OnMessage(int32 message);
		virtual bool OnMouse(float x, float y);
		virtual bool OnKeyDown(BearInput::Key key);
		virtual bool OnKeyUp(BearInput::Key key);
		virtual void Reset();
		virtual void Update();
		virtual void Draw(BearUI * ui, float time);
		virtual void Unload();
		virtual void Reload();
		virtual void KillFocus();
	private:
		void CBButton();
		void CBListBox();
		BearUIListBox UIListBox;
		BearUIButton UIButton;
		BearUITexture UITexture;
		BearUITexture UITextureBackground;
		BearUIText UIText;
		BearCore::BearClassFunctionRef*CallBack;
		void*CallBack_Class;
	};
}