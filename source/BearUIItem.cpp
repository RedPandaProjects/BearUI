#include "BearUI.hpp"

BearUI::BearUIItem::BearUIItem():m_mouse_enter(false), Focus(0), m_focus_item(0), Enable(true)
{
}

BearUI::BearUIItem::~BearUIItem()
{
}

void BearUI::BearUIItem::PushItem(BearUIItem * item)
{
	item->Reset();
	m_items.push_back(item);
	m_static_items.push_back(item);
}

void BearUI::BearUIItem::PushItem(BearUIStaticItem * item)
{
	item->Reset();
	m_static_items.push_back(item);
}

void BearUI::BearUIItem::PushItemInBegin(BearUIItem * item)
{
	item->Reset();
	m_items.insert(m_items.begin(),item);
	m_static_items.insert(m_static_items.begin(), item);
}

void BearUI::BearUIItem::PushItemInBegin(BearUIStaticItem * item)
{
	item->Reset();
	m_static_items.insert(m_static_items.begin(), item);
}

void BearUI::BearUIItem::PopItem(BearUIItem * item)
{
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

void BearUI::BearUIItem::PopItem(BearUIStaticItem * item)
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

void BearUI::BearUIItem::PopItems()
{
	m_static_items.clear_not_free();
	m_items.clear_not_free();
}

void BearUI::BearUIItem::Update()
{
	if (Visible)return;
	{
		auto b = m_items.begin();
		auto e = m_items.end();
		while (b != e)
		{
			(*b)->Update();
			b++;
		}
	}
}

void BearUI::BearUIItem::Draw(BearUI * ui, float time)
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


void BearUI::BearUIItem::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseEnter:
		m_mouse_enter = true;
		break;
	case M_MouseLevae:
		m_mouse_enter = false;
		break;
	}

}

bool BearUI::BearUIItem::OnMouse(float x, float y)
{
	if (Visible)return false;
	MouseLastPosition.set(x, y);
	if (m_focus_item)
		if (m_focus_item->OnMouse(x, y))
		{
			auto b = m_items.begin();
			auto e = m_items.end();
			while (b != e)
			{
				if((*b)->m_mouse_enter&&m_focus_item!=*b)
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
				if ((*b)->m_mouse_enter)
				{
					(*b)->OnMessage(M_MouseLevae);
				}
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
		if (m_mouse_enter) 
		{
			OnMessage(M_MouseLevae);
		//	printf("Levae %p\r\n", this);
		}
	}
	return false;
}

bool BearUI::BearUIItem::OnKeyDown(BearInput::Key key)
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
			Focus = true;
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
			Focus = true;
			OnMessage(M_MouseLClick);
			return true;
		}
		else
		{
			Focus = false;
		}
	}
	else if(key == BearInput::KeyMouseRight)
	{
		OnMessage(M_MouseRClick);
		return true;
	}
	return false;
}

bool BearUI::BearUIItem::OnKeyUp(BearInput::Key key)
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

void BearUI::BearUIItem::Reset()
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

void BearUI::BearUIItem::KillFocus()
{
	Focus = false;
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

void BearUI::BearUIItem::Unload()
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

void BearUI::BearUIItem::Reload()
{
	BearUIStaticItem::Reload();
	{
		auto b = m_static_items.begin();
		auto e = m_static_items.end();
		while (b != e)
		{
			(*b)->Reload();
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

bool BearUI::BearUIItem::OnChar(bchar16 ch)
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

bool BearUI::BearUIItem::MouseEntered()
{
	return m_mouse_enter;
}

void BearUI::BearUIItem::UpdateFocus()
{
	auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if (*b != m_focus_item) { (*b)->Focus = false; (*b)->KillFocus(); }
		b++;
	}
}
