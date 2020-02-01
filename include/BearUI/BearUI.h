#pragma once
class BEARUI_API BearUI
{
	BEAR_CLASS_WITHOUT_COPY(BearUI);
	friend class BearUITexture;
public:
	BearUI(bsize width, bsize height);

	virtual void Resize(bsize width, bsize height);
	void Draw(BearFactoryPointer<BearRHI::BearRHIContext>&Context, BearTime time);
	void Update(BearTime time);
	void Unload();
	void Reload();
	virtual	void Reset();
	void KillFocus();

	void OnMouse(float x,float y);
	void OnKeyDown(BearInput::Key key);
	void OnKeyUp(BearInput::Key key);
	void UseEventViewport(BearEventWindows&event);
	void OnChar(bchar16 ch);

	~BearUI();

	BearUIItem* PushItem(BearUIItem*item);
	BearUIStaticItem* PushItem(BearUIStaticItem*item);
	//inline BearUICursorManager&GetCursorManager() { return m_cursor_manager; }
	template<class C>
	inline void SetResourcesManager()
	{
		m_ResourcesManager = BearRef<BearUIResourcesManager>(bear_new<C>());
	}
	void AttactViewportAsFrameBuffer(BearFactoryPointer<BearRHI::BearRHIViewport> FrameBuffer);
private:
	void UpdateFocus();
	struct 
	{
		BearFactoryPointer<BearRHI::BearRHIViewport> ViewportAsFrameBuffer;
	} FrameBuffer;

	BearFactoryPointer<BearRHI::BearRHIUniformBuffer> m_ConstantsScreen;
	BearFactoryPointer<BearRHI::BearRHIUniformBuffer> m_ConstantsColor;
	BearVector4<float> m_Screen;
	BearFactoryPointer<BearRHI::BearRHIVertexBuffer> m_VertexBufferColor;
	BearVector < BearFactoryPointer<BearRHI::BearRHIVertexBuffer>> m_VertexBuffersDefault;
	typename BearVector < BearFactoryPointer<BearRHI::BearRHIVertexBuffer>>::iterator m_VertexBuffersDefaultCurrent;
	BearFactoryPointer<BearRHI::BearRHIIndexBuffer> m_IndexBuffer;


	BearFactoryPointer<BearRHI::BearRHIShader> m_ShaderDefaultPS;
	BearFactoryPointer<BearRHI::BearRHIShader> m_ShaderDefaultVS;
	BearFactoryPointer<BearRHI::BearRHIShader> m_ShaderColorPS;
	BearFactoryPointer<BearRHI::BearRHIShader> m_ShaderColorVS;
	BearFactoryPointer<BearRHI::BearRHIShader> m_ShaderFontPS;

	BearFactoryPointer<BearRHI::BearRHIRootSignature> m_RootSignatureColor;
	BearFactoryPointer<BearRHI::BearRHIRootSignature> m_RootSignatureDefault;
	BearFactoryPointer<BearRHI::BearRHISampler> m_SamplerDefault;
	BearVector<BearUIItem*> m_Items;
	BearVector<BearUIStaticItem*> m_StaticItems;
		
	BearVector2<bsize> m_SizeScreen;
	BearUIItem* m_FocusItem;

	BearRHI::BearRHIContext* m_CurrentContext;

	BearRef<BearUIResourcesManager> m_ResourcesManager;

	enum EPipelineFlag
	{
		EPF_Textures= 1<<0,
		EPF_Alpha= 1 << 1,
	};
	struct PipelineKey
	{
		BearFactoryPointer<BearRHI::BearRHIShader> Pixel;
		BearFactoryPointer<BearRHI::BearRHIShader> Vertex;
		BearFlags<uint32> Flags;
		bool operator<(const PipelineKey&right)const
		{
			if (Pixel != right.Pixel)return Pixel < right.Pixel;
			if (Vertex != right.Vertex)return Vertex < right.Vertex;
			return *Flags < *right.Flags;
		}
	};
	BearMap< PipelineKey, BearFactoryPointer<BearRHI::BearRHIPipeline>> m_PipelinesMap;

	void SetPipeline(BearFactoryPointer<BearRHI::BearRHIShader>& Pixel, BearFactoryPointer<BearRHI::BearRHIShader>&Vertex, BearFlags<uint32> Flag);

	enum EDescriptorHeapFlag
	{
		DHF_Texture = 1 << 0,
	};
	struct DescriptorHeapKey
	{
		BearFactoryPointer<BearRHI::BearRHITexture2D> Texture;
		BearFlags<uint32> Flags;
		bool operator<(const DescriptorHeapKey& right)const
		{
			if (Texture != right.Texture)return Texture < right.Texture;
			return *Flags < *right.Flags;
		}
	};

	BearMap< DescriptorHeapKey, BearFactoryPointer<BearRHI::BearRHIDescriptorHeap>> m_DescriptorHeapsMap;
	void SetDescriptorHeap(BearFactoryPointer<BearRHI::BearRHITexture2D> Texture, BearFlags<uint32> Flags);
	//	BearUICursorManager m_cursor_manager;
#ifdef BEAR_UI_EXPORTS
public:
#else
private:
#endif
	void Render(BearUITexture* texture);
	void Render(BearUIText* text);
	void RenderSelectZone(BearUIText* text);
	void Render(BearUITriangle* triangle);
};