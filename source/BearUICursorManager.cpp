#include "BearUI.hpp"

BearUICursorBase::~BearUICursorBase()
{
}

BearUICursorManager::BearUICursorManager()
{
	m_curent_viewport = 0;
}

BearUICursorManager::~BearUICursorManager()
{
}

void BearUICursorManager::AddCursor(int32 type,BearRef<BearUICursorBase>&& Cursor)
{
	BEAR_ASSERT(m_cursors.find(type) == m_cursors.end());
	BEAR_ASSERT(type > 0);
	m_cursors.insert(type, Cursor);
}

void BearUICursorManager::DetachViewport()
{
	m_curent_viewport = 0;
}

void BearUICursorManager::AttachViewport(BearWindow & viewport)
{
	m_curent_viewport = &viewport;
}

BearVector2<float> BearUICursorManager::GetMousePosition()
{
	if (m_curent_viewport)
	{
		return m_curent_viewport->GetMousePosition();
	}
	return BearInput::GetMousePosition();
}

void BearUICursorManager::Draw(BearUI * ui, int32 type_cursor,BearTime time)
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

void BearUICursorManager::Reset()
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Reset();
	}

}

void BearUICursorManager::Unload()
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Unload();
	}
}

void BearUICursorManager::Reload(BearUIResourcesManager* Manager)
{
	for (auto begin = m_cursors.begin(), end = m_cursors.end(); begin != end; begin++)
	{
		begin->second->Reload(Manager);
	}
}

