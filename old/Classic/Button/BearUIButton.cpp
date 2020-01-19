#include "BearUI.hpp"

BearUI::Classic::BearUIButton::BearUIButton():m_call_back(0), m_call_back_class(0), m_press(false), TriangleStyle(BearUITriangle::S_TriangleRight)
{
	UIText.Style = UIText.ST_CenterOfHeight|UIText.ST_CenterOfWidth;
	PushItem(&UIText);
	PushItem(&UITriangle);
	PushItem(&UITexture);
	PushItem(&UITextureBack);
	UITriangle.Visible = true;
}

BearUI::Classic::BearUIButton::~BearUIButton()
{
	if (m_call_back)m_call_back->Destroy();
	m_call_back = 0;
	m_call_back_class = 0;
}


float BearUI::Classic::BearUIButton::CalcWidth() const
{
	return UIText.CalcWidth()+2;
}

float BearUI::Classic::BearUIButton::CalcHeight() const
{
	return UIText.CalcHeight() + 2;
}

void BearUI::Classic::BearUIButton::Update(BearTime time)
{
	BearUIItem::Update(time);
	if (m_press)
	{
		if (m_call_back)m_call_back->Call<void>(m_call_back_class);
	}
	UIText.Position = Position;
	if (Style.test(S_WithoutBackground))
	{
		UITexture.Position = Position;
	}
	else
	{
		UITexture.Position = Position +BearVector2<float>(2, 2);
	}
	UITextureBack.Position = Position;
	UITriangle.Position = Position;
}

void BearUI::Classic::BearUIButton::OnMessage(int32 message)
{
	if (Enable)
	{
		if (Style.test(S_WithoutBackground))
		{
			switch (message)
			{
			case M_MouseEnter:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_MouseEnter][StyleConfig.CT_Plane];
				break;
			case M_MouseLevae:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Plane];
				break;
			case M_MouseLClick:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_MouseClick][StyleConfig.CT_Plane];
				break;
			case M_MouseLUp:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Plane];
				break;
			default:
				break;
			}
		}
		else
		{
			switch (message)
			{
			case M_MouseEnter:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_MouseEnter][StyleConfig.CT_Plane];
				UITextureBack .Color = StyleConfig.Colors[StyleConfig.A_MouseEnter][StyleConfig.CT_Background];
				break;
			case M_MouseLevae:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Plane];
				UITextureBack.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Background];
				break;
			case M_MouseLClick:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_MouseClick][StyleConfig.CT_Plane];
				UITextureBack.Color = StyleConfig.Colors[StyleConfig.A_MouseClick][StyleConfig.CT_Background];
				break;
			case M_MouseLUp:
				UITexture.Color = StyleConfig.Colors[StyleConfig.A_MouseEnter][StyleConfig.CT_Plane];
				UITextureBack.Color = StyleConfig.Colors[StyleConfig.A_MouseEnter][StyleConfig.CT_Background];
				break;
			default:
				break;
			}
		}
		if (Flags.test(F_CallBackPress))
		{
			switch (message)
			{
			case M_MouseLClick:
				m_press = true;
				break;
			case M_MouseLUp:
				m_press = false;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (message)
			{
			case M_MouseLClick:
				if (m_call_back)m_call_back->Call<void>(m_call_back_class);
				break;
			default:
				break;
			}
		}
		
	}
	
	BearUIItem::OnMessage(message);
}

bool BearUI::Classic::BearUIButton::OnMouse(float x, float y)
{
	if (m_press)return true;
	return BearUIItem::OnMouse(x,y);
}

bool BearUI::Classic::BearUIButton::OnKeyDown(BearInput::Key key)
{
	if (m_press)return true;
	return BearUIItem::OnKeyDown(key);
}

bool BearUI::Classic::BearUIButton::OnKeyUp(BearInput::Key key)
{
	if (key == BearInput::KeyMouseLeft)m_press = false;
	return BearUIItem::OnKeyUp(key);
}

void BearUI::Classic::BearUIButton::Reset()
{
	UIText.Rect = Rect;
	UITexture.Rect = Rect;
	UITextureBack.Rect = Rect;

	if (StyleConfig.ShowBackground)
	{
		Style.AND(~S_WithoutBackground);
	}
	else
	{
		Style.OR(S_WithoutBackground);
	}

	if (Style.test(S_WithoutBackground))
	{
		UITextureBack.Visible = true;
		if(Enable)
			UITexture.Color = StyleConfig.Colors[StyleConfig.CT_Plane][StyleConfig.A_Default];
		else
			UITexture.Color = StyleConfig.Colors[StyleConfig.CT_Plane][StyleConfig.A_Disable];
	}
	else
	{
		if (Enable)
			UITexture.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Plane];
		else
			UITexture.Color = StyleConfig.Colors[StyleConfig.A_Disable][StyleConfig.CT_Plane];
		UITexture.Rect.x += 2;
		UITexture.Rect.y += 2;
		UITexture.Rect.x1 -= 4;
		UITexture.Rect.y1 -= 4;

		UITextureBack.Visible = false;
		if (Enable)
			UITextureBack.Color = StyleConfig.Colors[StyleConfig.A_Default][StyleConfig.CT_Background];
		else
			UITextureBack.Color = StyleConfig.Colors[StyleConfig.A_Disable][StyleConfig.CT_Background];
	}
	UITriangle.Visible = !Style.test(EStyle::S_Triangle);
	UITriangle.Rect = Rect;
	UITriangle.Style.clear();
	UITriangle.Scale = 0.5f;
	UITriangle.Style.set(true, TriangleStyle);
	UIText.Visible = Style.test(EStyle::S_Triangle);
	BearUIItem::Reset();
}


void BearUI::Classic::BearUIButton::KillFocus()
{
	m_press = false;
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUIButton::Reload()
{
	UIText.Text = Text;
	UIText.Font = Font;
	BearUIItem::Reload();
}

