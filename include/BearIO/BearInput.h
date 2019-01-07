#pragma once
namespace BearUI
{

	class BearInput
	{
		BEAR_CLASS_STATIC(BearInput);
	public:
		enum Key
		{
#define KEY(A) Key##A,
#include "..\BearIO\BearKeys.h"
			Key_Count,
		};
		static bool KeyState(Key key);
		static	BearCore::BearVector2<float> GetMousePosition();
		static void SetMousePosition(const BearCore::BearVector2<float>&position);
	};
}