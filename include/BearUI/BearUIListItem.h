#pragma once
namespace BearUI
{
	class BEARUI_API BearUIListItem :public BearUIItem
	{
		BEAR_CLASS_NO_COPY(BearUIListItem);

	public:
		BearUIListItem();
		~BearUIListItem();
		bsize ID;
		BearCore::BearString Text;
		BearCore::BearColor Color;
		BearCore::BearColor ColorSelected;
		BearFontRef Font;
		static float GetHieght(const BearFontRef&font);

		template<class CL, typename F>
		inline void SetCallback(CL*cl, F f)
		{
			if (CallBack)CallBack->Destroy();
			CallBack = BearCore::bear_create_class_function_ref(f);
			CallBack_Class = reinterpret_cast<void*>(cl);
		}
	public:
		virtual void Draw(BearUI * ui, float time);
		virtual void Update();
		enum Message
		{
			M_MouseLevae,
			M_MouseEnter,
			M_MouseLClick,
			M_MouseRClick,
			M_MouseLUp,
			M_MouseRUP,
		};
		virtual void OnMessage(int32 message);
		virtual bool OnMouse(float x, float y);
		virtual bool OnKeyDown(BearInput::Key key);
		virtual bool OnKeyUp(BearInput::Key key);
		virtual void Reset();
		virtual void KillFocus();
		void KillSelect();
		virtual void Unload();
		virtual void Reload();
	private:
		BearUIText UIText;
		BearUITexture UITexture;
		BearCore::BearClassFunctionRef*CallBack;
		void*CallBack_Class;
	};
}