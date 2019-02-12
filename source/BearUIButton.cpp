#include "BearUI.hpp"

BearUI::BearUIButton::BearUIButton():CallBack(0),CallBack_Class(0), bPress(false)
{
	UIText.Style = UIText.ST_CenterOfHeight|UIText.ST_CenterOfWidth;
	PushItem(&UIText);
	PushItem(&UITexture);
	PushItem(&UITextureBack);
}

BearUI::BearUIButton::~BearUIButton()
{
	if (CallBack)CallBack->Destroy();
	CallBack = 0;
	CallBack_Class = 0;
}
/*
inline void BearUI::BearUIButton::ClearCallBack()
{
	if (CallBack)CallBack->Destroy();
	CallBack = 0;
	CallBack_Class = 0;
}*/

void BearUI::BearUIButton::Draw(BearUI * ui, float time)
{
	BearUIItem::Draw(ui, time);
}

void BearUI::BearUIButton::Update()
{
	BearUIItem::Update();
	if (bPress)
	{
		if (CallBack)CallBack->Call<void>(CallBack_Class);
	}
	UIText.Position = Position;
	if (Style.test(B_WithoutBackground))
	{
		UITexture.Position = Position;
	}
	else
	{
		UITexture.Position = Position + BearCore::BearVector2<float>(2, 2);
	}
	UITextureBack.Position = Position;
}

void BearUI::BearUIButton::OnMessage(int32 message)
{
	if (Enable)
	{
		if (Style.test(B_WithoutBackground))
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
		if (Flags.test(B_CallBackPress))
		{
			switch (message)
			{
			case M_MouseLClick:
				bPress = true;
				break;
			case M_MouseLUp:
				bPress = false;
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
				if (CallBack)CallBack->Call<void>(CallBack_Class);
				break;
			default:
				break;
			}
		}
		
	}
}

bool BearUI::BearUIButton::OnMouse(float x, float y)
{
	if (bPress)return true;
	return BearUIItem::OnMouse(x,y);
}

bool BearUI::BearUIButton::OnKeyDown(BearInput::Key key)
{
	if (bPress)return true;
	return BearUIItem::OnKeyDown(key);
}

bool BearUI::BearUIButton::OnKeyUp(BearInput::Key key)
{
	if (key == BearInput::KeyMouseLeft)bPress = false;
	return BearUIItem::OnKeyUp(key);
}

void BearUI::BearUIButton::Reset()
{
	UIText.Rect = Rect;
	UIText.Text = Text;
	UIText.Font = Font;
	UITexture.Rect = Rect;
	UITextureBack.Rect = Rect;

	if (StyleConfig.ShowBackground)
	{
		Style.AND(~B_WithoutBackground);
	}
	else
	{
		Style.OR(B_WithoutBackground);
	}

	if (Style.test(B_WithoutBackground))
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
	BearUIItem::Reset();
}

void BearUI::BearUIButton::Unload()
{
	BearUIItem::Unload();
}

void BearUI::BearUIButton::Reload()
{
	BearUIItem::Reload();
}

void BearUI::BearUIButton::KillFocus()
{
	bPress = false;
	BearUIItem::KillFocus();
}

