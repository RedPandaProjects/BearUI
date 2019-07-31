#include "BearUI.hpp"

BearUI::BearUICursorBase::~BearUICursorBase()
{
}

BearUI::BearUICursorManager::BearUICursorManager()
{
	CurentViewport = 0;
}

BearUI::BearUICursorManager::~BearUICursorManager()
{
}

void BearUI::BearUICursorManager::AddCursor(int32 type, BearCore::BearMemoryRef<BearUICursorBase>&& Cursor)
{
	BEAR_ASSERT(MapCursors.find(type) == MapCursors.end());
	BEAR_ASSERT(type > 0);
	MapCursors.insert(type, Cursor);
}

void BearUI::BearUICursorManager::DetachViewport()
{
	CurentViewport = 0;
}

void BearUI::BearUICursorManager::AttachViewport(BearViewport & viewport)
{
	CurentViewport = &viewport;
}

BearCore::BearVector2<float> BearUI::BearUICursorManager::GetMousePosition()
{
	if (CurentViewport)
	{
		return CurentViewport->GetMousePosition();
	}
	return BearInput::GetMousePosition();
}

void BearUI::BearUICursorManager::Draw(BearUI * ui, int32 type_cursor, BearCore::BearTime time)
{
	switch (type_cursor)
	{
	case C_None:
		if (CurentViewport)CurentViewport->ShowCursor(false);
		break;
	case C_Default:
		if (CurentViewport)CurentViewport->ShowCursor(true);
		break;
	default:
	{
		auto find = MapCursors.find(type_cursor);
		if (find == MapCursors.end())
		{
			if (CurentViewport)CurentViewport->ShowCursor(true);
		}
		else
		{
			if (CurentViewport)CurentViewport->ShowCursor(false);
			find->second->Position = GetMousePosition();
			find->second->Draw(ui, time);
		}
	}
		break;
	}
}

void BearUI::BearUICursorManager::Reset()
{
	for (auto begin = MapCursors.begin(), end = MapCursors.end(); begin != end; begin++)
	{
		begin->second->Reset();
	}

}

void BearUI::BearUICursorManager::Unload()
{
	for (auto begin = MapCursors.begin(), end = MapCursors.end(); begin != end; begin++)
	{
		begin->second->Unload();
	}
}

void BearUI::BearUICursorManager::Reload()
{
	for (auto begin = MapCursors.begin(), end = MapCursors.end(); begin != end; begin++)
	{
		begin->second->Reload();
	}
}

