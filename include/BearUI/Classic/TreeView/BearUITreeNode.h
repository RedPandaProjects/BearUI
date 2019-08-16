#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITreeView;
		class BEARUI_API BearUITreeNode:public BearUIItem
		{
			friend BearUITreeNodeButton;
			friend BearUITreeView;
			BEAR_CLASS_NO_COPY(BearUITreeNode);
		public:
			BearUITreeNode();
			~BearUITreeNode();
			BearFontRef Font;
			BearCore::BearString Data;
			BearCore::BearString Text;
			BearCore::BearColor ColorSelect;
			BearCore::BearColor ColorSelectFocus;

			BearUITreeNode*Find(const bchar*text);
			const BearUITreeNode*Find(const bchar*text)const;

			BearUITreeNode&Add(const bchar*text);
			virtual float  CalcHeight() const;
		private:
			virtual float  CalcWidth() const;
		
		protected:
			BearUITreeView*Parent;

			virtual void Reset();
			
			enum EMessage
			{
				M_Deployed_On = 0x100,
				M_Deployed_Off,
			};
			virtual bool OnMouse(float x, float y);
			virtual void Update(BearCore::BearTime time);
			virtual void OnMessage(int32 message);
			virtual void KillFocus();
			virtual bool OnKeyDown(BearInput::Key key);
			void PushNodesToParent();
			void NodesWrap();
			virtual void Reload();
		private:
			float WidthShift;
			bool Deployed;
			BearCore::BearVector< BearCore::BearMemoryRef< BearUITreeNode>> Nodes;
			BearUIText UIText;
			BearUITexture UIPlane;
			BearUITexture UIBackgroundPlane;
			BearUITreeNodeButton UIButton;
			float Height;
		};
	}
}