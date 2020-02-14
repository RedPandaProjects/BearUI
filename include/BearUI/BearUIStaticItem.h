#pragma once
class BearUI;
class BEARUI_API BearUIStaticItem
{
	BEAR_CLASS_WITHOUT_COPY(BearUIStaticItem);
protected:
	BearUIStaticItem();
	~BearUIStaticItem();
public:
	union 
	{
		BearVector4<float> Rect;
		struct
		{
			BearVector2<float> Position;
			BearVector2<float> Size;
		};
	};
	BearVector4<float> Clip;
	enum EFlags
	{
		UI_NoClip = 1 << 31,
		UI_NoMouseEnter = 1 << 30,
	};
	BearFlags<int64> Flags;
	BearFlags<int64> Style;
	bool Visible;
public:
	virtual float  CalcWidth() const;
	virtual float  CalcHeight() const;
	virtual void Draw(BearUI* ui, BearTime time);
	virtual void Reset();
	virtual void Unload();
	virtual void Reload(BearUIResourcesManager* Manager);
};