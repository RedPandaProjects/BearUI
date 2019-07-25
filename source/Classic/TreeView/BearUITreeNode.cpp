#include "BearUI.hpp"

BearUI::Classic::BearUITreeNode::BearUITreeNode():Deployed(false), Parent(0)
{
	ColorSelect.Set(uint8(67), uint8(67), uint8(67));
	ColorSelectFocus.Set(uint8(0), uint8(120), uint8(200));
	UIText.Flags.set(false, UIText.UI_NoClip);
	UIText.Style = UIText.ST_CenterOfHeight ;
	UIPlane.Flags.set(false, UIText.UI_NoClip);
	UIPlane.Visible = false;
	WidthShift = 8;
}

BearUI::Classic::BearUITreeNode::~BearUITreeNode()
{
}

BearUI::Classic::BearUITreeNode * BearUI::Classic::BearUITreeNode::Find(const bchar * text)
{
	auto item = BearCore::bear_find_if(Nodes.begin(), Nodes.end(), [text](const BearCore::BearMemoryRef< BearUITreeNode> &a) {return a->Text == text; });
	if (item == Nodes.end())
		return NULL;
	return **item;
}

const  BearUI::Classic::BearUITreeNode * BearUI::Classic::BearUITreeNode::Find(const bchar * text) const
{
	auto item = BearCore::bear_find_if(Nodes.begin(), Nodes.end(), [text](const BearCore::BearMemoryRef< BearUITreeNode> &a) {return a->Text == text; });
	if (item == Nodes.end())
		return NULL;
	return **item;
}

BearUI::Classic::BearUITreeNode & BearUI::Classic::BearUITreeNode::Add(const bchar * text)
{
	auto *Node = BearCore::bear_new< BearUITreeNode>();
	Node->Text = text;
	Nodes.push_back(Node);
	Reset();
	return *Node;
}

void BearUI::Classic::BearUITreeNode::Reset()
{
	if (Font.Empty())return;
	Height = 0;
	PopItems();
	UIText.Clip = Clip;
	UIText.Font = Font;
	UIText.Text = Text;
	UIButton.Parent = this;
	UIButton.Color = BearCore::BearColor::White;
	UIButton.ColorSelect = ColorSelectFocus;
	UIButton.Clip = Clip;
	UIPlane.Clip = Clip;
	UIPlane.Color = ColorSelectFocus;
	UIButton.ColorSelect = ColorSelectFocus;
	PushItem(&UIText);
	PushItem(&UIButton);
	PushItem(&UIPlane);

	for (auto b = Nodes.begin(), e = Nodes.end(); b != e; b++)
	{
		(*b)->Font = Font;
		(*b)->Parent = Parent;
		(*b)->Reset();
		(*b)->Clip = Clip;
		if (!Parent)
			PushItem(**b);
	}
	Update();
	BearUIItem::Reset();
}

void BearUI::Classic::BearUITreeNode::Update()
{
	Height = 0;
	Size.y = static_cast<float>(Font.GetHieght()) + 2;

	UIText.Clip = Clip;
	UIText.Rect = Rect;
	UIText.Rect += BearCore::BearVector4<float>(static_cast<float>(Font.GetHieght()) + WidthShift, 1, -2 - static_cast<float>(Font.GetHieght()) - WidthShift, -2);
	UIPlane.Rect = Rect;
	UIPlane.Rect += BearCore::BearVector4<float>(2, 0, -4, 0);
	UIPlane.Clip = Clip;


	UIButton.Position = Position;
	UIButton.Position.x += WidthShift;
	UIButton.Size.y = static_cast<float>(Font.GetHieght());
	UIButton.Size.x = static_cast<float>(Font.GetHieght());
	UIButton.Clip = Clip;



	Height += Size.y;
	if (Nodes.size())
		UIButton.Visible = false;
	else
		UIButton.Visible = true;

	float width_shift = UIText.GetMaxSizeLine(TEXT("   ")) + 8 + static_cast<float>(Font.GetHieght()) + WidthShift;

	for (auto b = Nodes.begin(), e = Nodes.end(); b != e; b++)
	{
		(*b)->Visible = !Deployed;

		(*b)->Position = Position;
		(*b)->Position.y += Height;
		(*b)->Size = Size;
		(*b)->Clip = Clip;
		(*b)->WidthShift = width_shift;
		(*b)->Update();
		if(Deployed)
		Height += (*b)->GetHeight();
	}

	BearUIItem::Update();
}

void BearUI::Classic::BearUITreeNode::OnMessage(int32 message)
{
	switch (message)
	{
	case M_MouseLClick:
		UIPlane.Color = ColorSelectFocus;
		UIPlane.Visible = false;
		UIButton.ColorSelect = ColorSelect;
		if (Parent) 
		{
			Parent->Select = this;
			Parent->OnMessage(Parent->M_ClickSelect);
		}
		break;
	case M_Deployed_On:
	
		Deployed = true;
		if (Parent)
		{
			Parent->OnMessage(Parent->M_UpdateScrollBar);
		}
		break;
	case M_Deployed_Off:
		NodesWrap();
		if (Parent)
		{
			Parent->OnMessage(Parent->M_UpdateScrollBar);
		}
		break;
	default:
		break;
	}
	BearUIItem::OnMessage(message);
}

void BearUI::Classic::BearUITreeNode::KillFocus()
{	
	if (Parent&&Parent->Select == this)
	{
		if (Parent->Focused())
		{
			UIPlane.Color = ColorSelectFocus;
			UIButton.ColorSelect = ColorSelect;
		}
		else
		{
			UIPlane.Color = ColorSelect;
			UIButton.ColorSelect = ColorSelectFocus;
		}
	}
	else
	{
		UIPlane.Visible = true;
	}
	BearUIItem::KillFocus();
}

bool BearUI::Classic::BearUITreeNode::OnKeyDown(BearInput::Key key)
{
	if (UIButton.OnKeyDown(key))return false;
	return BearUIItem::OnKeyDown(key);
}

void BearUI::Classic::BearUITreeNode::PushNodesToParent()
{
	BEAR_ASSERT(Parent);
	for (auto b = Nodes.begin(), e = Nodes.end(); b != e; b++)
	{
		Parent->PushItem(**b);
		(*b)->PushNodesToParent();
	}
}

void BearUI::Classic::BearUITreeNode::NodesWrap()
{
	Deployed = false;
	UIButton.bSwitch = false;
	for (auto b = Nodes.begin(), e = Nodes.end(); b != e; b++)
	{
		(*b)->UIButton.bSwitch = false;
		(*b)->NodesWrap();
	}
}
