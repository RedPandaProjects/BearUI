#pragma once
namespace BearUI
{
	class BEARUI_API BearUICursorBase :public BearUIStaticItem
	{
	//	BEAR_CLASS_NO_COPY(BearUICursorBase);
	public:
		virtual ~BearUICursorBase();
	};
	
	class BEARUI_API BearUICursorManager 
	{
		BEAR_CLASS_NO_COPY(BearUICursorManager);
		friend class BearUI;
	public:
		BearUICursorManager();
		~BearUICursorManager();
		enum ECursor
		{
			C_None = -1,
			C_Default = -2,
		};

		void AddCursor(int32 type, BearCore::BearMemoryRef<BearUICursorBase>&&Cursor);
		void DetachViewport();
		void AttachViewport(BearViewport&viewport);
	protected:
		BearCore::BearVector2<float> GetMousePosition();
		virtual void Draw(BearUI * ui,int32 type_cursor, BearCore::BearTime time);
		virtual void Reset();
		virtual void Unload();
		virtual void Reload();
	private:
		BearCore::BearMap<int32, BearCore::BearMemoryRef<BearUICursorBase>> m_cursors;
		BearViewport*m_curent_viewport;
	};
}