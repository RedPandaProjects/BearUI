#include "BearUI.hpp"
#ifdef WINDOWS
extern BearCore::BearMap<int32, int32> GFromWinowsKey;

static bsize LCount = 0;
LRESULT CALLBACK GlobalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		SetWindowLongPtrW(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams));
		break;
	}
	{
		auto viewport = reinterpret_cast<BearUI::BearViewport*>(GetWindowLongPtrW(handle, GWLP_USERDATA));
		if (viewport) 
		{
			viewport->OnEvent(handle, message, wParam, lParam);
		}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}


static bool LBWindowsClass = false;
static void RegisterWindowsClass(HINSTANCE hInstance)
{
	if (LBWindowsClass)return;
	LBWindowsClass = true;

	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = GlobalOnEvent;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(69, 22, 28));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("BEAR");
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}
BearUI::BearViewport::BearViewport(bsize width, bsize height, bool fullscreen):m_width(width),m_height(height), m_mouse_enter(false)
{
	m_events_item = m_events.end();
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(0);

	RegisterWindowsClass(hInstance);



	DWORD Style = WS_OVERLAPPED | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	{
		RECT rectangle = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
		m_window = CreateWindow(TEXT("BEAR"), TEXT(""), Style, 0, 0, 1, 1, NULL, NULL, hInstance, this);

		AdjustWindowRect(&rectangle, GetWindowLong((HWND)m_window, GWL_STYLE), false);
		SetWindowPos((HWND)m_window, NULL, 0, 0, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, SWP_NOMOVE | SWP_NOZORDER);

		uint32 xpos = static_cast<int32>(((uint32)GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2));
		uint32 ypos = static_cast<int32>(((uint32)GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2));

		SetWindowPos((HWND)m_window, NULL, xpos, ypos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	ShowWindow((HWND)m_window, SW_SHOW);
	if (fullscreen)SetFullScreen(fullscreen);

	Create(m_window, GetSize().x, GetSize().y, fullscreen, false);



}

BearUI::BearViewport::~BearViewport()
{
	DestroyWindow(GetWindowHandle());

}

void BearUI::BearViewport::Resize(bsize width, bsize height)
{
	m_width = width;
	m_height = height;

	if (!m_fullscreen)
	{
		uint32 xpos = static_cast<int32>(((uint32)GetSystemMetrics(SM_CXSCREEN) / 2) - (m_width / 2));
		uint32 ypos = static_cast<int32>(((uint32)GetSystemMetrics(SM_CYSCREEN) / 2) - (m_height / 2));

		RECT rectangle = { 0, 0, static_cast<long>(m_width), static_cast<long>(m_height) };
		AdjustWindowRect(&rectangle, GetWindowLong((HWND)m_window, GWL_STYLE), false);
		long w = rectangle.right - rectangle.left;
		long h = rectangle.bottom - rectangle.top;
		SetWindowPos((HWND)m_window, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
		SetWindowPos((HWND)m_window, NULL, xpos, ypos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos((HWND)m_window, HWND_TOP, 0, 0, static_cast<int32>(m_width), static_cast<int32>(m_height), SWP_FRAMECHANGED);
	}
	BearGraphics::BearViewport::Resize(width, height);


}
void BearUI::BearViewport::SetFullScreen(bool fullscreen)
{
	m_fullscreen = fullscreen;
	if (m_fullscreen)
	{
		SetWindowLong((HWND)m_window, GWL_STYLE, WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE);
		ShowWindow((HWND)m_window, SW_MAXIMIZE);
		Resize(m_width, m_height);
	}
	else
	{
		SetWindowLong((HWND)m_window, GWL_STYLE, WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
		ShowWindow((HWND)m_window, SW_SHOW);
	}
	BearGraphics::BearViewport::SetFullScreen(fullscreen);
}

bool BearUI::BearViewport::Update()
{
	m_events.clear_not_free();
	m_events_item = m_events.end();
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	if (msg.message == WM_QUIT)
		return false;
	m_events_item = m_events.begin();
	return true;
}

BearCore::BearVector2<float> BearUI::BearViewport::GetMousePosition()
{
	return BearCore::BearVector2<float>();
}

void BearUI::BearViewport::SetMousePosition(const BearCore::BearVector2<float>& position)
{
}

void BearUI::BearViewport::SetVsync(bool vsync)
{
	BearGraphics::BearViewport::SetFullScreen(vsync);
}
bool BearUI::BearViewport::GetEvent(BearEventViewport & e)
{
	if (m_events_item == m_events.end())
		return false;
	e = *m_events_item;
	m_events_item++;
	return true;
}

void BearUI::BearViewport::OnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	bint i = 0;
	if (m_events_item == m_events.end()) i = -1;
	else i = m_events.end() - m_events_item;
	BearEventViewport ev;
	BearCore::bear_fill(ev);
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		int32 x = static_cast<int32>(LOWORD(lParam));
		int32 y = static_cast<int32>(HIWORD(lParam));

		RECT zone;
		GetClientRect(GetWindowHandle(), &zone);
		if (m_mouse_enter)
		{
			if ((zone.left > x || zone.right < x) ||
				(zone.top > y || zone.bottom < y))
			{
				ev.Type = EVT_MouseLevae;
				m_events.push_back(ev);
				m_mouse_enter = false;
			}
		
		}
		else
		{
			if ((zone.left <x && zone.right > x) &&
				(zone.top < y && zone.bottom > y))
			{
				ev.Type = EVT_MouseEnter;
				m_events.push_back(ev);
				m_mouse_enter = true;
			}
		}
		ev.Type = EVT_MouseMove;
		ev.Position.x = static_cast<float>(x);
		ev.Position.y = static_cast<float>(y);
		m_events.push_back(ev);
		break;
	}
	case WM_SETFOCUS:
	{
		ev.Type = EVT_Active;
		m_events.push_back(ev);
		break;
	}
	case WM_KILLFOCUS:
	{
		ev.Type = EVT_Deactive;
		m_events.push_back(ev);
		break;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_MENU:
			if (lParam & (1 << 24))
				wParam = VK_RMENU;
			else
				wParam = VK_LMENU;
			break;
		case VK_CONTROL:
			if (lParam & (1 << 24))
				wParam = VK_RCONTROL;
			else
				wParam = VK_LCONTROL;
			break;
		case VK_SHIFT:
			if (lParam & (1 << 24))
				wParam = VK_RSHIFT;
			else
				wParam = VK_LSHIFT;
			break;

		};
		auto item = GFromWinowsKey.find(DWORD(wParam));
		if (item == GFromWinowsKey.end())
			break;
		ev.Type = EVT_KeyDown;
		ev.Key = static_cast< BearInput::Key>(item->second);
		m_events.push_back(ev);
		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		switch (wParam)
		{
		case VK_MENU:
			if (lParam & (1 << 24))
				wParam = VK_RMENU;
			else
				wParam = VK_LMENU;
			break;
		case VK_CONTROL:
			if (lParam & (1 << 24))
				wParam = VK_RCONTROL;
			else
				wParam = VK_LCONTROL;
			break;
		case VK_SHIFT:
			if (lParam & (1 << 24))
				wParam = VK_RSHIFT;
			else
				wParam = VK_LSHIFT;
			break;

		};
		auto item = GFromWinowsKey.find(DWORD(wParam));
		if (item == GFromWinowsKey.end())
			break;
		ev.Type = EVT_KeyUp;
		ev.Key = static_cast<BearInput::Key>(item->second);
		m_events.push_back(ev);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		int16 delta = static_cast<int16>(HIWORD(wParam));
		if (delta > 0)
		{
			ev.Type = EVT_KeyDown;
			ev.Change = delta / 120.f;
			ev.Key = BearInput::KeyMouseScrollUp;
		}
		else if (delta < 0)
		{
			ev.Type = EVT_KeyDown;
			ev.Change = delta / 120.f;
			ev.Key = BearInput::KeyMouseScrollDown;
		}
		m_events.push_back(ev);
		break;
	}
	case WM_LBUTTONDOWN:
	{	
		ev.Type = EVT_KeyDown;
		ev.Key = BearInput::KeyMouseLeft;
		m_events.push_back(ev);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		ev.Type = EVT_KeyDown;
		ev.Key = BearInput::KeyMouseRight;
		m_events.push_back(ev);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		ev.Type = EVT_KeyDown;
		ev.Key = BearInput::KeyMouseMiddle;
		m_events.push_back(ev);
		break;
	}
	case WM_LBUTTONUP:
	{
		ev.Type = EVT_KeyUp;
		ev.Key = BearInput::KeyMouseLeft;
		m_events.push_back(ev);
		break;
	}
	case WM_RBUTTONUP:
	{
		ev.Type = EVT_KeyUp;
		ev.Key = BearInput::KeyMouseRight;
		m_events.push_back(ev);
		break;
	}
	case WM_MBUTTONUP:
	{
		ev.Type = EVT_KeyUp;
		ev.Key = BearInput::KeyMouseMiddle;
		m_events.push_back(ev);
		break;
	}
	case WM_CHAR:
	{
		TCHAR ch = TCHAR(wParam);
		ev.Type = EVT_Char;
		ev.Char = ch;
		m_events.push_back(ev);
		break;
	}
	default:
		return ;
	}

	if (i < 0)
	{
		m_events_item = m_events.end();
	}
	else if (i)
	{
		m_events_item = m_events.begin()+i;
	}
	return;
}
#endif