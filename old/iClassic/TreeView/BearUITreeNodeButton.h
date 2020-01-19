#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITreeNode;
		class BEARUI_API BearUITreeNodeButton :public BearUIItem
		{
			friend BearUITreeNode;
		public:
			BEAR_CLASS_WITHOUT_COPY(BearUITreeNodeButton);
			BearUITreeNodeButton();
			~BearUITreeNodeButton();
			BearColor Color;
			BearColor ColorSelect;

		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void Update(BearTime time);
			
			BearUITreeNode*Parent;
			virtual void KillFocus();
			bool bSwitch;
		private:
			BearUITriangle UITriangle;
		
		};
	}
}