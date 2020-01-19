#pragma once
class BEARUI_API BearUICursorBase :public BearUIStaticItem
{
//	BEAR_CLASS_WITHOUT_COPY(BearUICursorBase);
public:
	virtual ~BearUICursorBase();
};
	
class BEARUI_API BearUICursorManager
{
	BEAR_CLASS_WITHOUT_COPY(BearUICursorManager);
	friend class BearUI;
public:
	BearUICursorManager();
	~BearUICursorManager();
	enum ECursor
	{
		C_None = -1,
		C_Default = -2,
	};

	void AddCursor(int32 type, BearRef<BearUICursorBase>&& Cursor);
	void DetachViewport();
	void AttachViewport(BearWindow& viewport);
protected:
	BearVector2<float> GetMousePosition();
	virtual void Draw(BearUI* ui, int32 type_cursor, BearTime time);
	virtual void Reset();
	virtual void Unload();
	virtual void Reload(BearUIResourcesManager* Manager);
private:
	BearMap<int32, BearRef<BearUICursorBase>> m_cursors;
	BearWindow* m_curent_viewport;
};