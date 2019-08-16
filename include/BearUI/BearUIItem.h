#pragma once
namespace BearUI
{
	class BEARUI_API  BearUI;
	class BEARUI_API BearUIItem:public BearUIStaticItem
	{
		friend BearUI;
		BEAR_CLASS_NO_COPY(BearUIItem);
	public:
		BearUIItem();
		~BearUIItem();
	public:
		bool Enable;
		inline bool Focused()const { return m_focus; }
		bool MouseEntered()const { return m_mouse_enter; }
		
	protected:
		void PushItem(BearUIItem*item);
		void PushItem(BearUIStaticItem*item);
		void PushItemInBegin(BearUIItem*item);
		void PushItemInBegin(BearUIStaticItem*item);
		void PopItem(BearUIItem*item);
		void PopItem(BearUIStaticItem*item);
		void PopItems();

		virtual void Draw(BearUI * ui , BearCore::BearTime time);
		virtual void Update(BearCore::BearTime time);
		enum EMessage
		{
			M_MouseLevae,
			M_MouseEnter,
			M_MouseLClick,
			M_MouseRClick,
			M_MouseLUp,
			M_MouseRUp,
		};
		virtual void OnMessage(int32 message);
		virtual bool OnMouse(float x, float y);
		virtual bool OnKeyDown(BearInput::Key key);
		virtual bool OnKeyUp(BearInput::Key key);
		virtual void Reset();
		virtual void KillFocus();
		virtual void Unload();
		virtual void Reload();
		virtual bool OnChar(bchar16 ch);
		virtual int32 GetCursor(float x, float y);

		inline BearCore::BearVector2<float> GetMouseLastPosition() {return m_mouse_last_position;}
	protected:
		BearUI*UI;
	private:
		BearCore::BearVector2<float> m_mouse_last_position;
		void UpdateFocus();
		bool m_focus;
		BearCore::BearVector<BearUIStaticItem*> m_static_items;
		BearCore::BearVector<BearUIItem*> m_items;
		BearUIItem* m_focus_item;
		bool m_mouse_enter;
	};
}