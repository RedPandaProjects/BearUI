#include "BearUI.hpp"
#ifdef WINDOWS
static BearCore::BearMap<int32, int32> LToWinowsKey;
BearCore::BearMap<int32, int32> GFromWinowsKey;
struct Initializer 
{
	Initializer()
	{
		RegisterWindowsKey('A',BearUI::BearInput::KeyA);
		RegisterWindowsKey('B',BearUI::BearInput::KeyB);
		RegisterWindowsKey('C',BearUI::BearInput::KeyC);
		RegisterWindowsKey('D',BearUI::BearInput::KeyD);
		RegisterWindowsKey('E',BearUI::BearInput::KeyE);
		RegisterWindowsKey('F',BearUI::BearInput::KeyF);
		RegisterWindowsKey('G',BearUI::BearInput::KeyG);
		RegisterWindowsKey('H',BearUI::BearInput::KeyH);
		RegisterWindowsKey('I',BearUI::BearInput::KeyI);
		RegisterWindowsKey('J',BearUI::BearInput::KeyJ);
		RegisterWindowsKey('K',BearUI::BearInput::KeyK);
		RegisterWindowsKey('L',BearUI::BearInput::KeyL);
		RegisterWindowsKey('M',BearUI::BearInput::KeyM);
		RegisterWindowsKey('N',BearUI::BearInput::KeyN);
		RegisterWindowsKey('O',BearUI::BearInput::KeyO);
		RegisterWindowsKey('P',BearUI::BearInput::KeyP);
		RegisterWindowsKey('Q',BearUI::BearInput::KeyQ);
		RegisterWindowsKey('R',BearUI::BearInput::KeyR);
		RegisterWindowsKey('S',BearUI::BearInput::KeyS);
		RegisterWindowsKey('T',BearUI::BearInput::KeyT);
		RegisterWindowsKey('U',BearUI::BearInput::KeyU);
		RegisterWindowsKey('V',BearUI::BearInput::KeyV);
		RegisterWindowsKey('W',BearUI::BearInput::KeyW);
		RegisterWindowsKey('X',BearUI::BearInput::KeyX);
		RegisterWindowsKey('Y',BearUI::BearInput::KeyY);
		RegisterWindowsKey('Z',BearUI::BearInput::KeyZ);
		RegisterWindowsKey('0',BearUI::BearInput::KeyNum0);
		RegisterWindowsKey('1',BearUI::BearInput::KeyNum1);
		RegisterWindowsKey('2',BearUI::BearInput::KeyNum2);
		RegisterWindowsKey('3',BearUI::BearInput::KeyNum3);
		RegisterWindowsKey('4',BearUI::BearInput::KeyNum4);
		RegisterWindowsKey('5',BearUI::BearInput::KeyNum5);
		RegisterWindowsKey('6',BearUI::BearInput::KeyNum6);
		RegisterWindowsKey('7',BearUI::BearInput::KeyNum7);
		RegisterWindowsKey('8',BearUI::BearInput::KeyNum8);
		RegisterWindowsKey('9',BearUI::BearInput::KeyNum9);
		RegisterWindowsKey(VK_ESCAPE,BearUI::BearInput::KeyEscape);
		RegisterWindowsKey(VK_LCONTROL,BearUI::BearInput::KeyLControl);
		RegisterWindowsKey(VK_LSHIFT,BearUI::BearInput::KeyLShift);
		RegisterWindowsKey(VK_LMENU,BearUI::BearInput::KeyLAlt);
		RegisterWindowsKey(VK_LWIN,BearUI::BearInput::KeyLSystem);
		RegisterWindowsKey(VK_RCONTROL,BearUI::BearInput::KeyRControl);
		RegisterWindowsKey(VK_RSHIFT,BearUI::BearInput::KeyRShift);
		RegisterWindowsKey(VK_RMENU,BearUI::BearInput::KeyRAlt);
		RegisterWindowsKey(VK_RWIN,BearUI::BearInput::KeyRSystem);
		RegisterWindowsKey(VK_APPS,BearUI::BearInput::KeyMenu);
		RegisterWindowsKey(VK_OEM_4,BearUI::BearInput::KeyLBracket);
		RegisterWindowsKey(VK_OEM_6,BearUI::BearInput::KeyRBracket);
		RegisterWindowsKey(VK_OEM_1,BearUI::BearInput::KeySemiColon);
		RegisterWindowsKey(VK_OEM_COMMA,BearUI::BearInput::KeyComma);
		RegisterWindowsKey(VK_OEM_PERIOD,BearUI::BearInput::KeyPeriod);
		RegisterWindowsKey(VK_OEM_7,BearUI::BearInput::KeyQuote);
		RegisterWindowsKey(VK_OEM_2,BearUI::BearInput::KeySlash);
		RegisterWindowsKey(VK_OEM_5,BearUI::BearInput::KeyBackSlash);
		RegisterWindowsKey(VK_OEM_3,BearUI::BearInput::KeyTilde);
		RegisterWindowsKey(VK_OEM_PLUS,BearUI::BearInput::KeyEqual);
		RegisterWindowsKey(VK_OEM_MINUS,BearUI::BearInput::KeyDash);
		RegisterWindowsKey(VK_SPACE,BearUI::BearInput::KeySpace);
		RegisterWindowsKey(VK_RETURN,BearUI::BearInput::KeyReturn);
		RegisterWindowsKey(VK_BACK,BearUI::BearInput::KeyBackSpace);
		RegisterWindowsKey(VK_TAB,BearUI::BearInput::KeyTab);
		RegisterWindowsKey(VK_PRIOR,BearUI::BearInput::KeyPageUp);
		RegisterWindowsKey(VK_NEXT,BearUI::BearInput::KeyPageDown);
		RegisterWindowsKey(VK_END,BearUI::BearInput::KeyEnd);
		RegisterWindowsKey(VK_HOME,BearUI::BearInput::KeyHome);
		RegisterWindowsKey(VK_INSERT,BearUI::BearInput::KeyInsert);
		RegisterWindowsKey(VK_DELETE,BearUI::BearInput::KeyDelete);
		RegisterWindowsKey(VK_ADD,BearUI::BearInput::KeyAdd);
		RegisterWindowsKey(VK_SUBTRACT,BearUI::BearInput::KeySubtract);
		RegisterWindowsKey(VK_MULTIPLY,BearUI::BearInput::KeyMultiply);
		RegisterWindowsKey(VK_DIVIDE,BearUI::BearInput::KeyDivide);
		RegisterWindowsKey(VK_LEFT,BearUI::BearInput::KeyLeft);
		RegisterWindowsKey(VK_RIGHT,BearUI::BearInput::KeyRight);
		RegisterWindowsKey(VK_UP,BearUI::BearInput::KeyUp);
		RegisterWindowsKey(VK_DOWN,BearUI::BearInput::KeyDown);
		RegisterWindowsKey(VK_NUMPAD0,BearUI::BearInput::KeyNumpad0);
		RegisterWindowsKey(VK_NUMPAD1,BearUI::BearInput::KeyNumpad1);
		RegisterWindowsKey(VK_NUMPAD2,BearUI::BearInput::KeyNumpad2);
		RegisterWindowsKey(VK_NUMPAD3,BearUI::BearInput::KeyNumpad3);
		RegisterWindowsKey(VK_NUMPAD4,BearUI::BearInput::KeyNumpad4);
		RegisterWindowsKey(VK_NUMPAD5,BearUI::BearInput::KeyNumpad5);
		RegisterWindowsKey(VK_NUMPAD6,BearUI::BearInput::KeyNumpad6);
		RegisterWindowsKey(VK_NUMPAD7,BearUI::BearInput::KeyNumpad7);
		RegisterWindowsKey(VK_NUMPAD8,BearUI::BearInput::KeyNumpad8);
		RegisterWindowsKey(VK_NUMPAD9,BearUI::BearInput::KeyNumpad9);
		RegisterWindowsKey(VK_F1,BearUI::BearInput::KeyF1);
		RegisterWindowsKey(VK_F2,BearUI::BearInput::KeyF2);
		RegisterWindowsKey(VK_F3,BearUI::BearInput::KeyF3);
		RegisterWindowsKey(VK_F4,BearUI::BearInput::KeyF4);
		RegisterWindowsKey(VK_F5,BearUI::BearInput::KeyF5);
		RegisterWindowsKey(VK_F6,BearUI::BearInput::KeyF6);
		RegisterWindowsKey(VK_F7,BearUI::BearInput::KeyF7);
		RegisterWindowsKey(VK_F8,BearUI::BearInput::KeyF8);
		RegisterWindowsKey(VK_F9,BearUI::BearInput::KeyF9);
		RegisterWindowsKey(VK_F10,BearUI::BearInput::KeyF10);
		RegisterWindowsKey(VK_F11,BearUI::BearInput::KeyF11);
		RegisterWindowsKey(VK_F12,BearUI::BearInput::KeyF12);
		RegisterWindowsKey(VK_PAUSE,BearUI::BearInput::KeyPause);
		RegisterWindowsKey(VK_LBUTTON,BearUI::BearInput::KeyMouseLeft);
		RegisterWindowsKey(VK_RBUTTON,BearUI::BearInput::KeyMouseRight);
		RegisterWindowsKey(VK_MBUTTON,BearUI::BearInput::KeyMouseMiddle);
	}
	void RegisterWindowsKey(int32 win, BearUI::BearInput::Key key)
	{
		LToWinowsKey.insert(key, win);
		GFromWinowsKey.insert(win,key);
	}
	~Initializer()
	{

	}

};
#endif
bool BearUI::BearInput::KeyState(Key key)
{
#ifdef WINDOWS
	auto item = LToWinowsKey.find(key);
	if (item != LToWinowsKey.end())
		return ::GetKeyState(item->second) & 0x8000;
#endif
	return false;
}

BearCore::BearVector2<float> BearUI::BearInput::GetMousePosition()
{
	POINT P;
	GetCursorPos(&P);
	return BearCore::BearFVector2(static_cast<float>(P.x), static_cast<float>(P.y));
}

void BearUI::BearInput::SetMousePosition(const BearCore::BearVector2<float>& position)
{
	POINT point = { static_cast<LONG>(position.x),  static_cast<LONG>(position.y) };
	SetCursorPos(static_cast<LONG>(position.x), static_cast<LONG>(position.y));
}
