#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITreeNode;
		class BEARUI_API BearUITreeNodeButton :public BearUIItem
		{
		public:
			BEAR_CLASS_NO_COPY(BearUITreeNodeButton);
			BearUITreeNodeButton();
			~BearUITreeNodeButton();
			BearCore::BearColor Color;
			BearCore::BearColor ColorSelect;
#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			virtual void OnMessage(int32 message);
			virtual void Reset();
			virtual void Update();
			
			BearUITreeNode*Parent;
			virtual void KillFocus();
			bool bSwitch;
		private:
			BearUITriangle UITriangle;
		
		};
	}
}