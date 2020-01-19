#include "BearUI.hpp"

BearUIItem::BearUIItem():m_mouse_enter(false), m_focus(0), m_focus_item(0), Enable(true), UI(0)
{
}

BearUIItem::~BearUIItem()
{
}


void BearUIItem::PushItem(BearUIItem * item)
{
	item->Reset();
	item->UI = UI;
	m_items.push_back(item);
	m_static_items.push_back(item);
}

void BearUIItem::PushItem(BearUIStaticItem * item)
{
	item->Reset();
	m_static_items.push_back(item);
}

void BearUIItem::PushItemInBegin(BearUIItem * item)
{
	item->Reset();
	item->UI = UI;
	m_items.insert(m_items.begin(),item);
	m_static_items.insert(m_static_items.begin(), item);
}

void BearUIItem::PushItemInBegin(BearUIStaticItem * item)
{
	item->Reset();
	m_static_items.insert(m_static_items.begin(), item);
}

void BearUIItem::PopItem(BearUIItem * item)
{
	item->UI = 0;
	{
		auto i = dynamic_cast<BearUIStaticItem*>(item);
		if (i)PopItem(i);
	}
	{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			if ((*b) == item)
			{
				m_items.erase(b);
				return;
			}
				b++;
		}
	}
}

void BearUIItem::PopItem(BearUIStaticItem * item)
{
	{
		auto b = m_static_items.begin();
		auto e = m_static_items.end();
		while (b != e)
		{
			if ((*b) == item)
			{
				m_static_items.erase(b);
				return;
			}
			b++;
		}
	}
}

void BearUIItem::PopItems()
{
	{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->UI = 0;
			b++;
		}
	}
	m_static_items.clear_not_free();
	m_items.clear_not_free();
}

void BearUIItem::Update(BearTime time)
{
	if (Visible)return;
	{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->Update(time);
			b++;
		}
	}
}

void BearUIItem::Draw(BearUI * ui,BearTime time)
{
	if (Visible)return;
	{
		auto b = m_static_items.rbegin();
		auto e = m_static_items.rend();
		while (b != e)
		{
			(*b)->Draw(ui, time);
			b++;
		}
	}
	/*{
		auto b = m_items.rbegin();
		auto e = m_items.rend();
		while (b != e)
		{
			(*b)->Draw(ui, time);
			b++;
		}
	}*/
}


void BearUIItem::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseEnter:
		m_mouse_enter = true;
		break;
	case M_MouseLevae:
	{
		{
			auto b = m_items.begin();
			auto e = m_items.end();
			while (b != e)
			{
				(*b)->OnMessage(M_MouseLevae);
				b++;
			}
		}
		m_mouse_enter = false;
	}
		break;
	}

}

bool BearUIItem::OnMouse(float x, float y)
{
	if (Visible)return false;
	m_mouse_last_position.set(x, y);
	if (m_focus_item)
		if (m_focus_item->OnMouse(x, y))
		{
			auto b = m_items.begin();
			auto e = m_items.end();
			while (b != e)
			{
				if(m_focus_item!=*b)
				(*b)->OnMessage(M_MouseLevae);
				b++;
			}
			return true;
		}

	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if ((*b)->OnMouse(x, y))
		{
			b++;
			while (b != e)
			{
				/*if ((*b)->m_mouse_enter)
				{*/
					(*b)->OnMessage(M_MouseLevae);
				//}
			//	printf("Levae %p\r\n", (*b));
				b++;
			
			}
			return true;
		}
		b++;
	}
	if ((!Flags.test(UI_NoMouseEnter))&&(Flags.test(UI_NoClip)||((x >= Clip.x&&x <= Clip.x + Clip.x1) && (y >= Clip.y&&y <= Clip.y + Clip.y1))) &&(x >= Position.x&&x <= Position.x+Size.x)&& (y >= Position.y&&y <= Position.y+Size.y))
	{
		
		if (!m_mouse_enter)
		{
			OnMessage(M_MouseEnter);
		}
		return true;
	}
	else
	{
	/*	if (m_mouse_enter) 
		{*/
			OnMessage(M_MouseLevae);
			
		//}
	}
	return false;
}

bool BearUIItem::OnKeyDown(BearInput::Key key)
{
	if (Visible)return false;
	if (m_focus_item)
		if (m_focus_item->OnKeyDown(key))
			return true;
	m_focus_item = 0;
	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if ((*b)->OnKeyDown(key))
		{
			m_focus = true;
			m_focus_item = *b;
			UpdateFocus();
			return true;
		}
		b++;
	}
	if (key == BearInput::KeyMouseLeft)
	{
		if (m_mouse_enter)
		{
			m_focus = true;
			OnMessage(M_MouseLClick);
			return true;
		}
		else
		{
			m_focus = false;
		}
	}
	else if(key == BearInput::KeyMouseRight)
	{
		OnMessage(M_MouseRClick);
		//return true;
	}
	return false;
}

bool BearUIItem::OnKeyUp(BearInput::Key key)
{
	if (Visible)return false;
	if (m_focus_item &&m_focus_item->OnKeyUp(key))return true;
	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if (*b!= m_focus_item &&(*b)->OnKeyUp(key))
			return true;
		b++;
	}
	if (m_mouse_enter)
	{
		if (key == BearInput::KeyMouseLeft)
		{
			OnMessage(M_MouseLUp);
			return true;
		}
		else if  (key == BearInput::KeyMouseRight)
		{
			OnMessage(M_MouseRUp);
			return true;
		}
	}
	return false;
}

void BearUIItem::Reset()
{
	KillFocus();
	{
		auto b = m_static_items.begin();
		auto e = m_static_items.end();
		while (b != e)
		{
			(*b)->Reset();
			b++;
		}
	}
	
	/*{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->Reset();
			b++;
		}
	}*/

	m_mouse_enter = false;
}

void BearUIItem::KillFocus()
{
	m_focus = false;
	m_focus_item = 0;
	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		(*b)->KillFocus();
		b++;
	}
	m_mouse_enter = false;
}

void BearUIItem::Unload()
{
	{
		auto b = m_static_items.begin();
		auto e = m_static_items.end();
		while (b != e)
		{
			(*b)->Unload();
			b++;
		}
	}
	/*{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->Unload();
			b++;
		}
	}*/
	
}

void BearUIItem::Reload(BearUIResourcesManager* Manager)
{
	BearUIStaticItem::Reload(Manager);
	{
		auto b = m_static_items.begin();
		auto e = m_static_items.end();
		while (b != e)
		{
			(*b)->Reload(Manager);
			b++;
		}
	}
	/*{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->Reload();
			b++;
		}
	}*/
}

bool BearUIItem::OnChar(bchar16 ch)
{
	if (Visible)return false;
	if (m_focus_item)
	{
		m_focus_item->OnChar(ch);
		return true;
	}

	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if ((*b)->OnChar(ch))
		{
			return true;
		}
		b++;
	}
	return false;
}

int32 BearUIItem::GetCursor(float x,float y)
{
	if (Visible)return false;
	if (m_focus_item)
	{
		int32 type = m_focus_item->GetCursor(x,y);
		if (type)return type;
	}

	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		int32 type = (*b)->GetCursor(x,y);
		if (type)return type;
		b++;
	}
	return 0;
}


void BearUIItem::UpdateFocus()
{
	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if (*b != m_focus_item) { (*b)->m_focus = false; (*b)->KillFocus(); }
		b++;
	}
}
