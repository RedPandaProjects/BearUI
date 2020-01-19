#pragma once
class BearUI;
class BEARUI_API BearUITexture :public BearUIStaticItem
{
	friend class BearUI;
	BEAR_CLASS_WITHOUT_COPY(BearUITexture);
public:
	BearUITexture();
	~BearUITexture();
private:
	virtual float  CalcWidth() const;
	virtual float  CalcHeight() const;
public:
	BearVector4<float> TextureUV;
	BearFactoryPointer<BearRHI::BearRHITexture2D> Texture;
	BearColor Color;
	float Rotation;

	virtual void Draw(BearUI* ui, BearTime time);
	virtual void Reset();
	virtual void Unload();
	virtual void Reload(BearUIResourcesManager* Manager);
private:
	BearUIVertexManager::Default m_vertex[4];

};