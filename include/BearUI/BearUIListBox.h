#pragma once
namespace BearUI
{
	class BEARUI_API BearUIListBox :public BearUIItem
	{
		BEAR_CLASS_NO_COPY(BearUIListBox);

	public:
		BearUIListBox();
		~BearUIListBox();
		BearCore::BearVector<BearCore::BearString> Items;
		bint SelectItem;
		BearCore::BearColor ColorBackground;
		BearFontRef Font;


		template<class CL, typename F>
		inline void SetCallback(CL*cl, F f)
		{
			CallBack = BearCore::bear_create_class_function_ref(f);
			CallBack_Class = reinterpret_cast<void*>(cl);
		}
	public:
		virtual void Draw(BearUI * ui, float time);
		virtual void Update();
		enum MessageListBox
 		{
			LB_SelectedItem=0x100,
		};
		virtual void OnMessage(int32 message);
		virtual bool OnMouse(float x, float y);
		virtual bool OnKeyDown(BearInput::Key key);
		virtual bool OnKeyUp(BearInput::Key key);
		virtual void Reset();
		virtual void KillFocus();
		virtual void Unload();
		virtual void Reload();
	private:

		BearCore::BearClassFunctionRef*CallBack;
		void*CallBack_Class;
		void CBSelectedItem(BearUIListItem*item);
		void CBScrollBar();
		BearCore::BearVector<BearCore::BearMemoryRef<BearUIListItem>> UIItems;
		BearUITexture UIBackground;
		BearUIScrollBar UIScrollBar;
	};
}