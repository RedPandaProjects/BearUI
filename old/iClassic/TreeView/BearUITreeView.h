#pragma once
namespace BearUI
{
	namespace Classic
	{
		class BEARUI_API BearUITreeView :public BearUIItem
		{
			friend BearUITreeNodeButton;
			friend BearUITreeNode;
			BEAR_CLASS_WITHOUT_COPY(BearUITreeView);
		public:
			BearUITreeView();
			~BearUITreeView();
			BearColor ColorPlaneBackground;
			BearColor ColorPlane;
			BearColor ColorSelect;
			BearColor ColorSelectFocus;
			BearFontRef Font;


			BearUITreeNode*Find(const bchar*text);
			const BearUITreeNode*Find(const bchar*text)const;

			BearUITreeNode&Add(const bchar*text);

			inline BearUITreeNode*GetSelectNode() { return Select; }
			inline const BearUITreeNode*GetSelectNode() const { return Select; }

			template<class CL, typename F>
			inline void SetCallback(CL*cl, F f)
			{
				if (m_call_back)m_call_back->Destroy();
				m_call_back =bear_create_class_function_ref(f);
				m_call_back_class = reinterpret_cast<void*>(cl);
			}
		private:
			virtual float  CalcWidth() const;
			virtual float  CalcHeight() const;
		protected:
			virtual void Reload();
			virtual void Reset();
			virtual void Update(BearTime time);
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
			BearClassFunctionRef*m_call_back;
			void*m_call_back_class;
			BearVector<BearMemoryRef< BearUITreeNode>> Nodes;
			BearUITexture UIPlane;
			BearUITexture UIPlaneBackground;
			BearUIScrollBar UIScrollBar;
		};
	}
}