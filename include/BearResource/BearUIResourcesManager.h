#pragma once
class BEARUI_API BearUIResourcesManager
{
public:
	/*--------BASE----------
	|	default.ps
	|   default.vs
	|   color.ps
	|   color.vs
	|   font.ps
	-----------------------*/
	enum UIShaderType
	{
		ST_Default_PS,
		ST_Default_VS,
		ST_Color_PS,
		ST_Color_VS,
		ST_Font_PS
	};
	virtual BearFactoryPointer<BearRHI::BearRHIShader> GetShader(UIShaderType Type) = 0;

	/*--------BASE----------
	|	"\0" - default
	|
	-----------------------*/
	virtual BearFactoryPointer<BearRHI::BearRHITexture2D> GetTexture(const bchar* name) = 0;
	/*--------BASE----------
	|	"\0" - default
	|
	-----------------------*/
	virtual BearFont* GetFont(const bchar* name) = 0;
	virtual BearFactoryPointer<BearRHI::BearRHITexture2D> GetTextureFromFont(const bchar* name) = 0;

	virtual ~BearUIResourcesManager();
	
};