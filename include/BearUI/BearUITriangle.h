#pragma once
class BEARUI_API BearUITriangle :public BearUIStaticItem
{
	friend class BearUI;
	BEAR_CLASS_WITHOUT_COPY(BearUITriangle);
public:
	BearUITriangle();
	~BearUITriangle();
public:
	BearColor Color;
	float Scale;
	enum EStyle
	{
		S_TriangleUp   =0,
		S_TriangleDown =1,
		S_TriangleLeft =3 ,
		S_TriangleRight=7,
	};
private:
	virtual float  CalcWidth() const;
	virtual float  CalcHeight() const;
public:
	virtual void Draw(BearUI * ui,BearTime time);
	virtual void Reset();
	virtual void Unload();
	virtual void Reload(BearUIResourcesManager* Manager);
private:
	BearUIVertexManager::Color m_vertex[3];

};