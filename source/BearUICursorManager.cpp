#include "BearUI.hpp"

BearUI::BearUICursorBase::~BearUICursorBase()
{
}

BearUI::BearUICursorManager::BearUICursorManager()
{
	m_curent_viewport = 0;
}

BearUI::BearUICursorManager::~BearUICursorManager()
{
}

void BearUI::BearUICursorManager::AddCursor(int32 type, BearCore::BearMemoryRef<BearUICursorBase>&& Cursor)
{
	BEAR_ASSERT(m_cursors.find(type) == m_cursors.end());
	BEAR_ASSERT(type > 0);
	m_cursors.insert(type, Cursor);
}

void BearUI::BearUICursorManager::DetachViewport()
{
	m_curent_viewport = 0;
}

void BearUI::BearUICursorManager::AttachViewport(BearViewport & viewport)
{
	m_curent_viewport = &viewport;
}

BearCore::BearVector2<float> BearUI::BearUICursorManager::GetMousePosition()
{
	if (m_curent_viewport)
	{
		return m_curent_viewport->GetMousePosition();
	}
	return BearInput::GetMousePosition();
}

void BearUI::BearUICursorManager::Draw(BearUI * ui, int32 type_cursor, BearCore::BearTime time)
{
	switch (type_cursor)
	{
	case C_None:
		if (m_curent_viewport)m_curent_viewport->ShowCursor(false);
		break;
	case C_Default:
		if (m_curent_viewport)m_curent_viewport->ShowCursor(true);
		break;
	default:
	{
		auto find = m_cursors.find(type_cursor);
		if (find == m_cursors.end())
		{
			if (m_curent_viewport)m_curent_viewport->ShowCursor(true);
		}
		else
		{
			if (m_curent_viewport)m_curent_viewport->ShowCursor(false);
			find->second->Position = GetMousePosition();
			find->second->Draw(ui, time);
		}
	}
		break;
	}
}

void BearUI::BearUICursorManager::Reset()
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Reset();
	}

}

void BearUI::BearUICursorManager::Unload()
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Unload();
	}
}

void BearUI::BearUICursorManager::Reload()
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Reload();
	}
}

