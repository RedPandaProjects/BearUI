#include "BearUI.hpp"

BearUI::BearUIComboBox::BearUIComboBox() :SelectItem(-1), CallBack(0)
{
	PushItem(&UIButton);
	PushItem(&UIText);
	PushItem(&UITexture);
	PushItem(&UITextureBackground);
	PushItem(&UIListBox);
	UIListBox.SetCallback(this, &BearUIComboBox::CBListBox);
	UIButton.SetCallback(this, &BearUIComboBox::CBButton);
	Flags. or (UI_NoMouseEnter);
}

BearUI::BearUIComboBox::~BearUIComboBox()
{
	if (CallBack)CallBack->Destroy();
}

void BearUI::BearUIComboBox::OnMessage(int32 message)
{
	switch (message)
	{
	case MCB_SelectItem:
		if (CallBack)CallBack->Call<void>(CallBack_Class);
		break;
	}
}

bool BearUI::BearUIComboBox::OnMouse(float x, float y)
{
	return BearUIItem::OnMouse(x,y);;
}

bool BearUI::BearUIComboBox::OnKeyDown(BearInput::Key key)
{
	return BearUIItem::OnKeyDown(key);;
}

bool BearUI::BearUIComboBox::OnKeyUp(BearInput::Key key)
{
	return BearUIItem::OnKeyUp(key);
}

void BearUI::BearUIComboBox::Reset()
{
	float size = static_cast<float>(Font.GetHieght())+2;
	UIButton.Size.set(size + 4, size + 4);
	UIButton.Position.set(Position.x+ (Size.x-(size +4)), Position.y);
	UIButton.Font = Font;
	UIButton.Text = TEXT("V");
	UIButton.StyleConfig = BearUIButton::StyleWithoutBackground();
	UIButton.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);


	UITextureBackground.Rect = Rect;
	UITextureBackground.Rect.y1 = size + 4;
	
	UITexture.Rect = UITextureBackground.Rect;
	UITexture.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UITexture.Color = UIButton.StyleConfig.Colors[UIButton.StyleConfig.A_Default][UIButton.StyleConfig.CT_Plane];
	UITextureBackground.Color = UIButton.StyleConfig.Colors[UIButton.StyleConfig.A_MouseEnter][UIButton.StyleConfig.CT_Plane];

	UIListBox.Position.set(Position.x,Position.y + size + 4);
	UIListBox.Size.set(Size.x, Size.y - size - 4);
	UIListBox.Visible = true;

	UIListBox.Items = Items;
	UIListBox.Font = Font;

	UIText.Rect = UITextureBackground.Rect;
	UIText.Size.x -= size + 4;
	UIText.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIText.Clip = UIText.Rect;
	UIText.Flags. and (~UIFlags::UI_NoClip);
	UIText.Font = Font;
	UIText.Text = TEXT("");
	if (Items.size() < SelectItem)
	{
		SelectItem = -1;
	}
	if (SelectItem >= 0)
	{
		UIText.Text = Items[SelectItem];
	}
	BearUIItem::Reset();
}

void BearUI::BearUIComboBox::Update()
{
	BearUIItem::Update();
}

void BearUI::BearUIComboBox::Draw(BearUI * ui, float time)
{
	BearUIItem::Draw(ui,time);
}

void BearUI::BearUIComboBox::Unload()
{
	BearUIItem::Unload();
}

void BearUI::BearUIComboBox::Reload()
{
	BearUIItem::Reload();

}

void BearUI::BearUIComboBox::KillFocus()
{
	UIListBox.Visible = true;
	BearUIItem::KillFocus();
}

void BearUI::BearUIComboBox::CBButton()
{
	UIListBox.Visible = false;
}

void BearUI::BearUIComboBox::CBListBox()
{
	UIListBox.Visible = true;
	SelectItem = UIListBox.SelectItem;
	UIText.Text = Items[SelectItem];
	UIText.Reset();
	OnMessage(MCB_SelectItem);
}
