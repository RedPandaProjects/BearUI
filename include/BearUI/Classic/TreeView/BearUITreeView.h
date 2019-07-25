#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITreeView :public BearUIItem
		{
			BEAR_CLASS_NO_COPY(BearUITreeView);
		public:
			BearUITreeView();
			~BearUITreeView();
			BearCore::BearColor ColorPlaneBackground;
			BearCore::BearColor ColorPlane;
			BearCore::BearColor ColorSelect;
			BearCore::BearColor ColorSelectFocus;
			BearFontRef Font;


			BearUITreeNode*Find(const bchar*text);
			const BearUITreeNode*Find(const bchar*text)const;

			BearUITreeNode&Add(const bchar*text);

			inline BearUITreeNode*GetSelectNode() { return Select; }
			inline const BearUITreeNode*GetSelectNode() const { return Select; }

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				if (CallBack)CallBack->Destroy();
				CallBack = BearCore::bear_create_class_function_ref(f);
				CallBack_Class = reinterpret_cast<void*>(cl);
			}

#ifdef BEAR_UI_EXPORTS
		public:
#else
		protected:
#endif
			virtual void Reset();
			virtual void Update();
			BearUITreeNode*Select;
			enum EMessage
			{
				M_ClickSelect=0x100,
				M_UpdateScrollBar
			};
			virtual void OnMessage(int32 message);
		private:
			void UpdateScrollBar();
			bool bUpdateScrollBar;
			float ScrollBarHeight;
			bool ViewedAll();
			BearCore::BearClassFunctionRef*CallBack;
			void*CallBack_Class;
			BearCore::BearVector< BearCore::BearMemoryRef< BearUITreeNode>> Nodes;
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
			BearUIScrollBar UIScrollBar;
		};
	}
}