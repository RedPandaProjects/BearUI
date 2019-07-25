#include "BearUI.hpp"

BearUI::Classic::BearUITreeNodeButton::BearUITreeNodeButton():Parent(0), bSwitch(false)
{
	UITriangle.Flags.set(false, UITriangle.UI_NoClip);
	PushItem(&UITriangle);
	UITriangle.Scale = .5f;
}

BearUI::Classic::BearUITreeNodeButton::~BearUITreeNodeButton()
{
}

void BearUI::Classic::BearUITreeNodeButton::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseEnter:
		UITriangle.Color = ColorSelect;
		break;
	case M_MouseLevae:
		UITriangle.Color = Color;
		break;
	case M_MouseLUp:
		bSwitch = !bSwitch;
		if (bSwitch)
		{
			UITriangle.Style.set(false, UITriangle.S_TriangleRight);
			UITriangle.Style.set(true, UITriangle.S_TriangleDown);
			Parent->OnMessage(Parent->M_Deployed_On);
		}
		else
		{
	
			UITriangle.Style.set(true, UITriangle.S_TriangleRight);
			Parent->OnMessage(Parent->M_Deployed_Off);
		}
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUITreeNodeButton::Reset()
{

	UITriangle.Clip = Clip;
	BearUIItem::Reset();
}

void BearUI::Classic::BearUITreeNodeButton::Update()
{
	UITriangle.Clip = Clip;
	UITriangle.Rect = Rect;
	if (bSwitch)
	{
		UITriangle.Style.set(false, UITriangle.S_TriangleRight);
		UITriangle.Style.set(true, UITriangle.S_TriangleDown);
	}
	else
	{

		UITriangle.Style.set(true, UITriangle.S_TriangleRight);
	}
	BearUIItem::Update();
}

void BearUI::Classic::BearUITreeNodeButton::KillFocus()
{
	UITriangle.Color = Color;
	BearUIItem::KillFocus();
}
