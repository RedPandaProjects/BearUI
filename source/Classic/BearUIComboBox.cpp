#include "BearUI.hpp"

BearUI::Classic::BearUIComboBox::BearUIComboBox() :SelectItem(-1), CallBack(0)
{
	ColorPlaneBackground.Set(uint8(100), uint8(100), uint8(100));
	ColorPlane.Set(uint8(20), uint8(20), uint8(20));
	PushItem(&UIButton);
	PushItem(&UIText);
	PushItem(&UITexture);
	PushItem(&UITextureBackground);
	PushItem(&UIListBox);
	UIListBox.SetCallback(this, &BearUIComboBox::CBListBox);
	UIButton.SetCallback(this, &BearUIComboBox::CBButton);
	Flags. OR (UI_NoMouseEnter);
}

BearUI::Classic::BearUIComboBox::~BearUIComboBox()
{
	if (CallBack)CallBack->Destroy();
}

void BearUI::Classic::BearUIComboBox::OnMessage(int32 message)
{
	switch (message)
	{
	case M_SelectItem:
		if (CallBack)CallBack->Call<void>(CallBack_Class);
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUIComboBox::Reset()
{
	float size = static_cast<float>(Font.GetMaxHieght())+2;
	UIButton.Size.set(size + 4, size + 4);
	UIButton.Position.set(Position.x+ (Size.x-(size +4)), Position.y);
	UIButton.Style.set(true, UIButton.S_Triangle);
	UIButton.TriangleStyle = BearUITriangle::S_TriangleDown;
	UIButton.StyleConfig = BearUIButton::StyleWithoutBackgroundDark();
	UIButton.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);


	UITextureBackground.Rect = Rect;
	UITextureBackground.Rect.y1 = size + 4;
	
	UITexture.Rect = UITextureBackground.Rect;
	UITexture.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UITexture.Color = ColorPlane;
	UITextureBackground.Color = ColorPlaneBackground;

	UIListBox.Position.set(Position.x,Position.y + size + 4);
	UIListBox.Size.set(Size.x, Size.y - size - 4);
	UIListBox.Visible = true;

	UIListBox.Items = Items;
	UIListBox.Font = Font;

	UIText.Rect = UITextureBackground.Rect;
	UIText.Size.x -= size + 4;
	UIText.Rect += BearCore::BearVector4<float>(1, 1, -2, -2);
	UIText.Clip = UIText.Rect;
	UIText.Flags. AND (~UI_NoClip);
	UIText.Font = Font;
	UIText.Text = TEXT("");
	if (static_cast<bint>(Items.size()) < SelectItem)
	{
		SelectItem = -1;
		UIListBox.SelectItem = -1;
	}
	if (SelectItem >= 0)
	{
		UIText.Text = Items[SelectItem];
		UIListBox.SelectItem = SelectItem;
	}
	BearUIItem::Reset();
}

void BearUI::Classic::BearUIComboBox::KillFocus()
{
	UIListBox.Visible = true;
	BearUIItem::KillFocus();
}

void BearUI::Classic::BearUIComboBox::CBButton()
{
	UIListBox.Visible = false;
}

void BearUI::Classic::BearUIComboBox::CBListBox()
{
	UIListBox.Visible = true;
	SelectItem = UIListBox.SelectItem;
	UIText.Text = Items[SelectItem];
	UIText.Reset();
	OnMessage(M_SelectItem);
}
