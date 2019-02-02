#pragma once
namespace BearUI
{
	class BEARUI_API BearUIItem:public BearUIStaticItem
	{
		BEAR_CLASS_NO_COPY(BearUIItem);
	public:
		BearUIItem();
		~BearUIItem();
	public:
		bool Enable;
		bool Focus;
	public:
		void PushItem(BearUIItem*item);
		void PushItem(BearUIStaticItem*item);
		void PushItemInBegin(BearUIItem*item);
		void PushItemInBegin(BearUIStaticItem*item);
		void PopItem(BearUIItem*item);
		void PopItem(BearUIStaticItem*item);
		void PopItems();

		virtual void Draw(BearUI * ui ,float time);
		virtual void Update();
		enum Message
		{
			M_MouseLevae,
			M_MouseEnter,
			M_MouseLClick,
			M_MouseRClick,
			M_MouseLUp,
			M_MouseRUP,
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
		void UpdateFocus();

		BearCore::BearVector<BearUIStaticItem*> m_static_items;
		BearCore::BearVector<BearUIItem*> m_items;
		BearUIItem* m_focus_item;
		bool m_mouse_enter;
	};
}