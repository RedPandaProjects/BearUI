#include "BearUI.hpp"
#ifdef WINDOWS
BearMap<int32, int32>* GWindowsKeys;
#endif


BearUI::BearUI(bsize width, bsize height):m_FocusItem(0), m_CurrentContext(0)
{
	m_Screen.set(static_cast<float>(width), static_cast<float>(height), 1.f / static_cast<float>(width), 1.f / static_cast<float>(height));
}
BearUI::~BearUI()
{
	BEAR_ASSERT(m_CurrentContext == nullptr);
#ifdef WINDOWS
	bear_free(GWindowsKeys);
#endif
	m_VertexBuffersDefaultCurrent = m_VertexBuffersDefault.end();
}


BearUIItem * BearUI::PushItem(BearUIItem * item)
{
	item->Reset();
	item->UI = this;
	m_Items.push_back(item);
	m_StaticItems.push_back(item);
	return item;
}

BearUIStaticItem * BearUI::PushItem(BearUIStaticItem * item)
{
	item->Reset();
	m_StaticItems.push_back(item);
	return item;
}

void BearUI::Resize(bsize width, bsize height)
{
	m_Screen.set(static_cast<float>(width), static_cast<float>(height), 1.f / static_cast<float>(width), 1.f / static_cast<float>(height));
	if (!m_ConstantsScreen.empty())
	{
		bear_copy(m_ConstantsScreen->Lock(), m_Screen.Array, sizeof(float) * 4);
		m_ConstantsScreen->Unlock();
	}
	/*bear_copy(m_screen_constant.Lock(), m_screen.array, sizeof(float) * 4);
	m_screen_constant.Unlock();*/
	m_SizeScreen.set(width, height);
	Reset();
}


void BearUI::Draw(BearFactoryPointer<BearRHI::BearRHIContext>& Context, BearTime time)
{
	m_CurrentContext = Context.get();
	if (m_CurrentContext == nullptr)return;
	if (m_RootSignatureDefault.get() == nullptr)return;
	//m_CurrentContext->SetViewport(0, 0, m_Screen.x, m_Screen.y);
	m_VertexBuffersDefaultCurrent = m_VertexBuffersDefault.begin();
	/*BearRenderInterface::SetViewport(0, 0, m_screen.x, m_screen.y);
	BearRenderInterface::SetVertexState(BearDefaultManager::GetVertexState(DVS_UI));
	BearRenderInterface::SetRasterizerState(BearDefaultManager::GetRasterizerState());
	BearRenderInterface::SetBlendState(BearDefaultManager::GetBlendAlpha(),BearColor::Transparent);
	BearRenderInterface::SetDepthStencilState(BearDefaultManager::GetBearDepthStencilState(), 0);*/
	/*{
		auto b = m_items.rbegin();
		auto e = m_items.rend();
		while (b != e)
		{
			(*b)->Draw(this, time);
			b++;
		}
	}*/
	{
		auto b = m_StaticItems.rbegin();
		auto e = m_StaticItems.rend();
		while (b != e)
		{
			(*b)->Draw(this, time);
			b++;
		}
	}
/*	auto m_position = m_cursor_manager.GetMousePosition();
	{
		if (m_focus_item)
		{
			int32 type = m_focus_item->GetCursor(m_position.x, m_position.y);
			if (type)
			{
				m_cursor_manager.Draw(this, type, time);
				return;
			}
		}
	}
	{
		auto b = m_items.rbegin();
		auto e = m_items.rend();
		while (b != e)
		{
			int32 type = (*b)->GetCursor(m_position.x, m_position.y);
			if(type)
			{
				m_cursor_manager.Draw(this, type, time);
				return;
			}
			b++;
		}
	}
	m_cursor_manager.Draw(this, m_cursor_manager.C_Default, time);*/
	m_CurrentContext = 0;

}

void BearUI::Update(BearTime time)
{
	auto b = m_Items.rbegin();
	auto e = m_Items.rend();
	while (b != e)
	{
		(*b)->Update(time);
		b++;
	}
	
}

void BearUI::Unload()
{
	{
		{
			m_PipelinesMap.clear();
			m_DescriptorHeapsMap.clear();
		}
		{
			m_RootSignatureDefault.clear();
			m_RootSignatureColor.clear();
		}
		{
			m_ShaderDefaultVS.clear();
			m_ShaderDefaultPS.clear();
			m_ShaderColorVS.clear();
			m_ShaderColorPS.clear();
			m_ShaderFontPS.clear();
		}
		{
			m_ConstantsScreen.clear();
			m_ConstantsColor.clear();
		}
		{

			m_VertexBuffersDefault.clear();
			m_VertexBufferColor.clear();
			m_IndexBuffer.clear();
		}
		m_PipelinesMap.clear();
		m_DescriptorHeapsMap.clear();
		m_SamplerDefault.clear();
	}
/*	m_cursor_manager.Unload();*/
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		(*b)->Unload();
		b++;
	}
}

void BearUI::Reload()
{
	if (*m_ResourcesManager==nullptr)return;
	{
		if (m_RootSignatureDefault.empty())Unload();
		{
			BearRootSignatureDescription RootSignatureDescription;
			
			RootSignatureDescription.UniformBuffers[0].Shader = ST_Vertex;
			RootSignatureDescription.UniformBuffers[1].Shader = ST_Pixel;
			RootSignatureDescription.SRVResources[0].Shader = ST_Pixel;
			RootSignatureDescription.Samplers[0].Shader = ST_Pixel;
			m_RootSignatureDefault = BearRenderInterface::CreateRootSignature(RootSignatureDescription);
		}
		{	
			BearSamplerDescription SamplerDescription;
			SamplerDescription.Filter = SF_ANISOTROPIC;
			SamplerDescription.MaxAnisotropy = 16;
			m_SamplerDefault = BearRenderInterface::CreateSampler(SamplerDescription);
		}
		{
			BearRootSignatureDescription RootSignatureDescription;

			RootSignatureDescription.UniformBuffers[0].Shader = ST_Vertex;
			RootSignatureDescription.UniformBuffers[1].Shader = ST_Pixel;
			m_RootSignatureColor = BearRenderInterface::CreateRootSignature(RootSignatureDescription);
		}
		{
			m_ShaderDefaultPS = m_ResourcesManager->GetShader(BearUIResourcesManager::ST_Default_PS);
			m_ShaderDefaultVS = m_ResourcesManager->GetShader(BearUIResourcesManager::ST_Default_VS);
			m_ShaderColorPS = m_ResourcesManager->GetShader(BearUIResourcesManager::ST_Color_PS);
			m_ShaderColorVS = m_ResourcesManager->GetShader(BearUIResourcesManager::ST_Color_VS);
			m_ShaderFontPS = m_ResourcesManager->GetShader(BearUIResourcesManager::ST_Font_PS);
		}
		{
			m_ConstantsScreen= BearRenderInterface::CreateUniformBuffer();
			m_ConstantsScreen->Create(sizeof(float) * 4, true);

		}
		{
			m_ConstantsColor = BearRenderInterface::CreateUniformBuffer();
			m_ConstantsColor->Create(sizeof(float) * 4, true);
		}
		{
		/*	m_VertexBufferDefault = BearRenderInterface::CreateVertexBuffer();
			m_VertexBufferDefault->Create(sizeof(BearUIVertexManager::Default), 6, true);*/
		}
		{
			m_VertexBufferColor = BearRenderInterface::CreateVertexBuffer();
			m_VertexBufferColor->Create(sizeof(BearUIVertexManager::Color), 6, true);
		}
		{
			m_IndexBuffer  = BearRenderInterface::CreateIndexBuffer();
			BEAR_ASSERT(!m_IndexBuffer.empty());
			m_IndexBuffer->Create( 6, true);
			static uint32 Index[] = { 2,1,0,1,3,0 };
			bear_copy(m_IndexBuffer->Lock(), Index, sizeof(uint32) * 6);
			m_IndexBuffer->Unlock();
		}
		{
			bear_copy(m_ConstantsScreen->Lock(), m_Screen.Array, sizeof(float) * 4);
			m_ConstantsScreen->Unlock();
		}
	}
	{
		//m_cursor_manager.Reload();
		auto b = m_Items.begin();
		auto e = m_Items.end();
		while (b != e)
		{
			(*b)->Reload(*m_ResourcesManager);
			b++;
		}
	}
	
}

void BearUI::Reset()
{
	//m_cursor_manager.Reset();
	
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		(*b)->Reset();
		b++;
	}
}

void BearUI::KillFocus()
{
	m_FocusItem = 0;
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		(*b)->KillFocus();
		b++;
	}
}

void BearUI::OnMouse(float x, float y)
{
	/*if (m_focus_item&&m_focus_item->OnMouse(x, y))
		return;*/
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
	/*	if ((*b) != m_focus_item)*/
			if ((*b)->OnMouse(x, y))
				break;
		b++;
	}
}

void BearUI::OnKeyDown(BearInput::Key key)
{
/*	if (m_focus_item&&m_focus_item->OnKeyDown(key))
		return;*/

	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		if (/*m_focus_item !=*b&&*/(*b)->OnKeyDown(key))
		{
			m_FocusItem = (*b);
			UpdateFocus();
			break;
		}
		b++;
	}
}

void BearUI::OnKeyUp(BearInput::Key key)
{
	/*if (m_focus_item&&m_focus_item->OnKeyUp(key))
		return;*/
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		if (/*m_focus_item != *b &&*/(*b)->OnKeyUp(key))break;
		b++;
	}
}

void BearUI::UseEventViewport(BearEventWindows & ev)
{
	switch (ev.Type)
	{
	case WET_Active:
		KillFocus();
		break;
	case WET_Resize:
		Resize(static_cast<bsize>(ev.Size.width), static_cast<bsize>(ev.Size.height));

		break;
	case WET_MouseMove:
		OnMouse(ev.Position.x, ev.Position.y);
		break;
	case WET_KeyDown:
		OnKeyDown(ev.Key);
		break;
	case WET_KeyUp:
		OnKeyUp(ev.Key);
		break;
	case WET_Char:
		OnChar(ev.Char);
		break;
	default:

		break;
	}
}

void BearUI::OnChar(bchar16 ch)
{
	if (m_FocusItem)
	{
		m_FocusItem->OnChar(ch);
		return;
	}

	/*auto b = m_items.begin();
	auto e = m_items.end();
	while (b != e)
	{
		if ((*b)->OnChar(ch))
		{
			return;
		}
		b++;
	}*/
}


void BearUI::SetPipeline(BearFactoryPointer<BearRHI::BearRHIShader>& Pixel, BearFactoryPointer<BearRHI::BearRHIShader>& Vertex, BearFlags<uint32> Flag)
{
	PipelineKey Key;
	Key.Pixel = Pixel;
	Key.Vertex = Vertex;
	Key.Flags = Flag;

	auto item = m_PipelinesMap.find(Key);
	if(item==m_PipelinesMap.end())
	{
		BearPipelineDescription PipelineDescription;
		PipelineDescription.InputLayout.Elements[0] = BearInputLayoutElement("POSITION", VF_R32G32_FLOAT, 0);

		if (Flag.test(EPF_Textures))
		{
			PipelineDescription.InputLayout.Elements[1] = BearInputLayoutElement("UV", VF_R32G32_FLOAT, 8);
			PipelineDescription.RootSignature = m_RootSignatureDefault;
		}
		else
		{
			PipelineDescription.RootSignature = m_RootSignatureColor;
		}
		PipelineDescription.Shaders.Pixel = Pixel;
		PipelineDescription.Shaders.Vertex = Vertex;
		m_PipelinesMap.insert(Key, BearRenderInterface::CreatePipeline(PipelineDescription));
		item = m_PipelinesMap.find(Key);
	}
	
	m_CurrentContext->SetPipeline(item->second);
}

void BearUI::SetDescriptorHeap(BearFactoryPointer<BearRHI::BearRHITexture2D> Texture, BearFlags<uint32> Flags)
{
	DescriptorHeapKey Key;
	Key.Texture = Texture;
	Key.Flags = Flags;
	auto item = m_DescriptorHeapsMap.find(Key);
	if (item == m_DescriptorHeapsMap.end())
	{
		BearDescriptorHeapDescription DescriptorHeapDescription;
		if (Flags.test(DHF_Texture))
		{
			DescriptorHeapDescription.RootSignature = m_RootSignatureDefault;
		//	DescriptorHeapDescription.SRVResurces[0] =Texture;
//			DescriptorHeapDescription.Samplers[0] = m_SamplerDefault;
		}
		else
		{
			DescriptorHeapDescription.RootSignature = m_RootSignatureColor;
		}
		//DescriptorHeapDescription.UniformBuffers[0] = m_ConstantsScreen;
	//	DescriptorHeapDescription.UniformBuffers[1] = m_ConstantsColor;
		m_DescriptorHeapsMap.insert(Key,BearRenderInterface::CreateDescriptorHeap( DescriptorHeapDescription));
		item = m_DescriptorHeapsMap.find(Key);
	}
	m_CurrentContext->SetDescriptorHeap(item->second);
}

void BearUI::Render(BearUITexture * texture)
{
	if (texture->Texture.empty())return;
	if (!texture->Flags.test(BearUIStaticItem::UI_NoClip)&&!texture->Clip.inZone(texture->Rect))
	{
		return;
	}


	if (texture->Flags.test(BearUIStaticItem::UI_NoClip))
	{
		m_CurrentContext->SetScissor(false, 0, 0, 0, 0);
	}
	else
	{
		m_CurrentContext->SetScissor(true, texture->Clip.x, texture->Clip.y, texture->Clip.x+ texture->Clip.x1, texture->Clip.y+ texture->Clip.y1);
	}

	bear_copy(reinterpret_cast<float*>(m_ConstantsColor->Lock()), texture->Color.R32G32B32A32, 4);
	m_ConstantsColor->Unlock();
	SetPipeline(m_ShaderDefaultPS, m_ShaderDefaultVS, EPF_Textures);
	SetDescriptorHeap(texture->Texture, DHF_Texture);

	BearFactoryPointer<BearRHI::BearRHIVertexBuffer>* VertexBufferDefault=0;
	if (m_VertexBuffersDefaultCurrent == m_VertexBuffersDefault.end())
	{
		m_VertexBuffersDefault.push_back(BearRenderInterface::CreateVertexBuffer());
		m_VertexBuffersDefault.back()->Create(sizeof(BearUIVertexManager::Default), 6, true);
		VertexBufferDefault = &m_VertexBuffersDefault.back();
		m_VertexBuffersDefaultCurrent = m_VertexBuffersDefault.end();
	}
	else
	{
		VertexBufferDefault = &*m_VertexBuffersDefaultCurrent;
		m_VertexBuffersDefaultCurrent++;
	}
	bear_copy(reinterpret_cast<BearUIVertexManager::Default*>((*VertexBufferDefault)->Lock()), texture->m_vertex, 4);
	(*VertexBufferDefault)->Unlock();
	m_CurrentContext->SetVertexBuffer((*VertexBufferDefault));
	m_CurrentContext->SetIndexBuffer(m_IndexBuffer);
	m_CurrentContext->DrawIndex(6);
	if (!texture->Flags.test(BearUIStaticItem::UI_NoClip))
	{
		m_CurrentContext->SetScissor(false, 0, 0, 0, 0);
	}
}
/*
void BearUI::Render(BearUIRenderTarget * texture)
{
	if (!texture->Flags.test(BearUIStaticItem::UI_NoClip) && !texture->Clip.inZone(texture->Rect))
	{
		return;
	}
	if (!texture->Flags.test(BearUIRenderTarget::F_Alpha))
		BearRenderInterface::SetBlendState(BearDefaultManager::GetBlend(),BearColor::Transparent);
	BearRenderInterface::SetVertexShader(BearDefaultManager::GetVertexShader(DVS_UI));
	BearRenderInterface::SetPixelShader(BearDefaultManager::GetPixelShader(DPS_UITexture));


	BearRenderInterface::SetVertexShaderConstants(0, m_screen_constant);

	if (texture->Flags.test(BearUIStaticItem::UI_NoClip))
	{
		BearRenderInterface::DisableScissor();
	}
	else
	{
		BearRenderInterface::SetScissor(texture->Clip.x, texture->Clip.y, texture->Clip.x + texture->Clip.x1, texture->Clip.y + texture->Clip.y1);
	}

	bear_copy(reinterpret_cast<float*>(m_color_constant.Lock()), texture->Color.GetFloat().array, 4);
	m_color_constant.Unlock();
	BearRenderInterface::SetPixelShaderConstants(0, m_color_constant);

	BearRenderInterface::SetPixelShaderResource(0, texture->RenderTarget, BearDefaultManager::GetSamplerState());
	bear_copy(reinterpret_cast<BearVertexDefault*>(m_vertex_buffer.Lock()), texture->m_vertex, 4);
	m_vertex_buffer.Unlock();
	BearRenderInterface::SetVertexBuffer(m_vertex_buffer);
	BearRenderInterface::SetIndexBuffer(m_index_buffer);
	BearRenderInterface::DrawIndexed(6);
	BearRenderInterface::DisableScissor();

	if(!texture->Flags.test(BearUIRenderTarget::F_Alpha))
	BearRenderInterface::SetBlendState(BearDefaultManager::GetBlendAlpha(),BearColor::Transparent);
}
*/
void BearUI::Render(BearUIText * text)
{
	

	/*BearVertexDefault vertex[4];

	bsize size = text->Text.size();
	if (text->Font->Empty() || !size)return;

	BearRenderInterface::SetPixelShader(BearDefaultManager::GetPixelShader(DPS_UIText));
	BearRenderInterface::SetVertexShader(BearDefaultManager::GetVertexShader(DVS_UI));

	BearRenderInterface::SetVertexShaderConstants(0, m_screen_constant);

	if (text->Flags.test(BearUIStaticItem::UI_NoClip))
	{
		BearRenderInterface::DisableScissor();
	}
	else
	{
		BearRenderInterface::SetScissor(text->Clip.x, text->Clip.y, text->Clip.x + text->Clip.x1, text->Clip.y + text->Clip.y1);
	}

	bear_copy(reinterpret_cast<float*>(m_color_constant.Lock()), text->Color.GetFloat().array, 4);
	m_color_constant.Unlock();

	BearRenderInterface::SetPixelShaderConstants(0, m_color_constant);
	BearRenderInterface::SetPixelShaderResource(0, *text->Font->GetTexture(), BearDefaultManager::GetSamplerState());
	BearRenderInterface::SetVertexBuffer(m_vertex_buffer);
	BearRenderInterface::SetIndexBuffer(m_index_buffer);

	auto&font = *text->Font->GetListChars();
	auto pos = text->Position+text->ShiftPosition;

	float up = 0;
	if (text->Style.is(BearUIText::ST_CenterOfHeight))
	{
		auto vec2 = BearUIText::GetMaxHeightCharInLine(text->Font,*text->Text,static_cast<BearUIText::EStyleText>(*text->Style));
		float temp = text->Size.y - vec2.x;
	
		temp =temp/ 2;
		temp -= vec2.y;
		up = roundf(temp);
		//up = -up;
	}
	BearVector4<float> TextureUV;

	for (bsize i = 0; i < size; i++)
	{
		bchar16 ch_ =BearEncoding::ToUTF16(text->Text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y += text->Font->GetHieght();
			pos.x = text->Position.x+ text->ShiftPosition.x;
			if (text->Style.is(BearUIText::ST_CenterOfHeight))
			{
				auto vec2 = BearUIText::GetMaxHeightCharInLine(text->Font, *text->Text, static_cast<BearUIText::EStyleText>(*text->Style));
				float temp = text->Size.y - vec2.x;

				temp = temp / 2;
				temp -= vec2.y;
				up = roundf(temp);
			}
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item != font.end())
			{

				TextureUV = item->second.TextureUV;
				if (pos.x + item->second.Advance.x > text->Rect.x1 + text->Position.x&&text->Style.test(text->ST_MaxWidth))
				{
					pos.y += text->Font->GetHieght();
					pos.x = text->Position.x;
					if (text->Style.is(BearUIText::ST_CenterOfHeight))
					{
						auto vec2 = BearUIText::GetMaxHeightCharInLine(text->Font, *text->Text, static_cast<BearUIText::EStyleText>(*text->Style));
						float temp = text->Size.y - vec2.x;

						temp = temp / 2;
						temp -= vec2.y;
						up = roundf(temp);
					}
				}

				{
					float x = pos.x + item->second.Position.x, y = pos.y + item->second.Position.y + up;
					float width = item->second.Size.x;
					float height = item->second.Size.y;

					x = floor(x);
					y = floor(y);
					width = floor(width);
					height = floor(height);
					if (text->Flags.test(BearUIStaticItem::UI_NoClip) || text->Clip.inZone(BearVector4<float>(x, y, width, height)))
					{

						vertex[0].Position.set(x, y + height);
						vertex[1].Position.set(x + width, y);
						vertex[2].Position.set(x, y);
						vertex[3].Position.set(x + width, y + height);
						vertex[0].TextureUV.set(TextureUV.x, TextureUV.y + TextureUV.y1);
						vertex[1].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y);
						vertex[2].TextureUV.set(TextureUV.x, TextureUV.y);
						vertex[3].TextureUV.set(TextureUV.x1 + TextureUV.x, TextureUV.y1 + TextureUV.y);

						bear_copy(reinterpret_cast<BearVertexDefault*>(m_vertex_buffer.Lock()), vertex, 4);
						m_vertex_buffer.Unlock();

						BearRenderInterface::DrawIndexed(6);
					}


				}
				pos.x += item->second.Advance.x;
			}
		}

	}
	BearRenderInterface::DisableScissor();*/
}

void BearUI::RenderSelectZone(BearUIText * text)
{
	bsize size = text->Text.size();
	if (text->Font->Empty() || !size)return;
	auto&font = text->Font->GetListChars();
	auto pos = text->Position + text->ShiftPosition;
	text->UISelectTexture.Size.y = static_cast<float>(text->Font->GetHieght());

	bsize start = text->SelectStart;
	bsize end = text->SelectEnd;

	if (start > end)bear_swap(start, end);
	if (start >= size)return;
	if (end > size)end=size;

	for (bsize i = 0; i < end; i++)
	{
		bchar16 ch_ =BearEncoding::ToUTF16(text->Text[i]);
		if (ch_ == TEXT(' '))
		{
			auto item = font.find(ch_);
		
			text->UISelectTexture.Position = pos;
			text->UISelectTexture.Size.x = item->second.Advance.x;
			if (i >= start)text->UISelectTexture.Draw(this, 0);
			pos.x += item->second.Advance.x;
		}
		else if (ch_ == TEXT('\t'))
		{
			ch_ = TEXT(' ');
			auto item = font.find(ch_);
			text->UISelectTexture.Position = pos;
			text->UISelectTexture.Size.x = item->second.Advance.x * 4;
			if (i >= start)text->UISelectTexture.Draw(this, 0);
			pos.x += item->second.Advance.x * 4;
		}
		else if (ch_ == TEXT('\n'))
		{
			pos.y += text->Font->GetHieght();
			pos.x = text->Position.x + text->ShiftPosition.x;
		}
		else if (ch_ != TEXT('\r'))
		{
			auto item = font.find(ch_);
			if (item != font.end())
			{

				if (pos.x + item->second.Advance.x > text->Rect.x1 + text->Position.x&&text->Style.test(text->ST_MaxWidth))
				{
					pos.y += text->Font->GetHieght();
					pos.x = text->Position.x;
					
				}

				{
					text->UISelectTexture.Position = pos;
					text->UISelectTexture.Size.x = item->second.Advance.x;
					if (i >= start)	text->UISelectTexture.Draw(this, 0);
				}
				pos.x += item->second.Advance.x;
			}
		}

	}

}

void BearUI::Render(BearUITriangle * triangle)
{
	/*if (!triangle->Flags.test(BearUIStaticItem::UI_NoClip) && !triangle->Clip.inZone(triangle->Rect))
	{
		return;
	}
	BearVertexDefault vertex[3];
	BearRenderInterface::SetVertexShader(BearDefaultManager::GetVertexShader(DVS_UI));
	BearRenderInterface::SetPixelShader(BearDefaultManager::GetPixelShader(DPS_UITexture));


	BearRenderInterface::SetVertexShaderConstants(0, m_screen_constant);

	if (triangle->Flags.test(BearUIStaticItem::UI_NoClip))
	{
		BearRenderInterface::DisableScissor();
	}
	else
	{
		BearRenderInterface::SetScissor(triangle->Clip.x, triangle->Clip.y, triangle->Clip.x + triangle->Clip.x1, triangle->Clip.y + triangle->Clip.y1);
	}

	bear_copy(reinterpret_cast<float*>(m_color_constant.Lock()), triangle->Color.GetFloat().array, 4);
	m_color_constant.Unlock();
	BearRenderInterface::SetPixelShaderConstants(0, m_color_constant);

	BearRenderInterface::SetPixelShaderResource(0, BearDefaultManager::GetTexture2D(), BearDefaultManager::GetSamplerState());

	auto rect = triangle->Rect;
	triangle->Size.set(rect.x1*triangle->Scale, rect.y1*triangle->Scale);

	triangle->Position +=BearFVector2((rect.x1- triangle->Size.x)/2.f, (rect.y1 - triangle->Size.y) / 2.f);
	if (triangle->Style.is(BearUITriangle::S_TriangleRight))
	{
		vertex[0].Position.set(triangle->Position.x, triangle->Position.y);
		vertex[1].Position.set(triangle->Position.x, triangle->Position.y+triangle->Size.y);
		vertex[2].Position.set(triangle->Position.x + triangle->Size.x, triangle->Position.y + triangle->Size.y/2.f);
	}
	else if (triangle->Style.is(BearUITriangle::S_TriangleLeft))
	{
		vertex[0].Position.set(triangle->Position.x, triangle->Position.y + triangle->Size.y / 2.f);
		vertex[1].Position.set(triangle->Position.x + triangle->Size.x, triangle->Position.y + triangle->Size.y);
		vertex[2].Position.set(triangle->Position.x + triangle->Size.x, triangle->Position.y );
	}
	else if (triangle->Style.is(BearUITriangle::S_TriangleDown))
	{
		vertex[0].Position.set(triangle->Position.x, triangle->Position.y);
		vertex[1].Position.set(triangle->Position.x + triangle->Size.x / 2.f, triangle->Position.y + triangle->Size.y);
		vertex[2].Position.set(triangle->Position.x + triangle->Size.x, triangle->Position.y);
	}
	else
	{

		vertex[0].Position.set(triangle->Position.x + triangle->Size.x / 2.f, triangle->Position.y);
		vertex[1].Position.set(triangle->Position.x , triangle->Position.y + triangle->Size.y);
		vertex[2].Position.set(triangle->Position.x + triangle->Size.x, triangle->Position.y + triangle->Size.y);
	}
	triangle->Rect = rect;
	bear_copy(reinterpret_cast<BearVertexDefault*>(m_vertex_buffer.Lock()), vertex, 3);
	m_vertex_buffer.Unlock();
	BearRenderInterface::SetVertexBuffer(m_vertex_buffer);
	BearRenderInterface::SetIndexBuffer(m_index_buffer);
	BearRenderInterface::DrawIndexed(3);
	BearRenderInterface::DisableScissor();*/
}

void BearUI::AttactViewportAsFrameBuffer(BearFactoryPointer<BearRHI::BearRHIViewport> frameBuffer)
{
	FrameBuffer.ViewportAsFrameBuffer = frameBuffer;
}

void BearUI::UpdateFocus()
{
	auto b = m_Items.begin();
	auto e = m_Items.end();
	while (b != e)
	{
		if (*b != m_FocusItem)(*b)->KillFocus();
		b++;
	}
}

