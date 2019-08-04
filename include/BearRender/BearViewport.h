#pragma once
namespace BearUI
{

	enum BearEventViewportType
	{
		EVT_KeyDouble,
		EVT_KeyDown,
		EVT_KeyUp,
		EVT_Char,
		EVT_Resize,
		EVT_Deactive,
		EVT_Active,
		EVT_MouseMove,
		EVT_MouseEnter,
		EVT_MouseLevae,
		EVT_None,
	};
	struct BearEventViewport
	{
		BearEventViewport() { BearCore::bear_fill(*this); }
	
		BearEventViewportType Type;
		BearInput::Key Key;
		union
		{
			float Change;
			struct
			{
				float x;
				float y;
			} Position;
			struct
			{
				float width;
				float height;
			} Size;
			bchar16 Char;
		};
		
	};

	class BEARUI_API BearViewport:public BearGraphics::BearViewport
	{
		BEAR_CLASS_NO_COPY(BearViewport);

	
		
	public:
		enum TypeWindow
		{
			TW_POPUP = 1,
			TW_ONLY_CLOSED=4,
			TW_WIHTOUT_CLOSED = 2,
			
		};
		BearViewport(bsize width = 0x400,bsize height=0x300,bool fullscreen=false, BearCore::BearFlags<int32> flags=0);
		~BearViewport();
		virtual void Resize(bsize width, bsize height);
		virtual void SetFullScreen(bool fullscreen);
		virtual void SetVsync(bool vsync);
		virtual bool Update();
		void  ShowCursor(bool show);
		BearCore::BearVector2<float> GetMousePosition();
		void SetMousePosition(const BearCore::BearVector2<float>&position);
		bool GetEvent(BearEventViewport&e);
		


		inline
#ifdef WINDOWS
			HWND
#elif LINUX
			void*
#endif
		GetWindowHandle() const
		{
			return m_window;
		}

		bool IsFullScreen()const
		{
			return m_fullscreen;
		}
		inline BearCore::BearFVector2 GetSizeFloat()const
		{
			return BearCore::BearVector2<float>(static_cast<float>(m_width), static_cast<float>(m_height));
		}

		inline BearCore::BearVector2<bsize> GetSize()const
		{
			return BearCore::BearVector2<bsize>(m_width, m_height);
		}
#ifndef BEAR_UI_EXPORTS
	private:
#endif
#ifdef WINDOWS
		void OnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
#endif

	private:
		
#ifdef WINDOWS
		bool m_MouseShow;
		HWND
#elif LINUX
		void*
#endif
		m_window;


		BearCore::BearVector<BearEventViewport>  m_events;
		BearCore::BearVector<BearEventViewport>::iterator  m_events_item;

		bsize m_width, m_height;
		bool m_fullscreen;
		bool m_mouse_enter;
	};
}