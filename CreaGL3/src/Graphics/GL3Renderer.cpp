#include "stdafx.h"

#include "DX9Renderer.h"


namespace crea
{
	DX9Renderer::DX9Renderer()
	{

	}

	DX9Renderer::~DX9Renderer()
	{

	}

	// Renvoie l'instance du renderer
	DX9Renderer& DX9Renderer::Instance()
	{
		static DX9Renderer s_Instance;
		return s_Instance;
	}

	void DX9Renderer::Initialize()
	{
		// a compléter
	}

	bool DX9Renderer::Update()
	{
		// a compléter
		return true;
	}

	void DX9Renderer::BeginScene() const
	{
		m_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00008080, 1.0f, 0x00);
		m_Device->BeginScene();
	}

	void DX9Renderer::EndScene() const
	{
		m_Device->EndScene();
		m_Device->Present(NULL, NULL, NULL, NULL);
	}

	void DX9Renderer::Quit() const
	{

	}

	extern "C" __declspec(dllexport) DX9Renderer* StartPlugin()
	{
		return &DX9Renderer::Instance();
	}

} // namespace crea