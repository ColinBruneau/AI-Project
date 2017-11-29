/***************************************************/
/* Nom:	DX9Renderer.h
/* Description: DX9Renderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Renderer_H
#define _DX9Renderer_H

#include "IFacade.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace crea
{

	class DX9Renderer
	{
	public:
		~DX9Renderer();

		// Renvoie l'instance du renderer
		static DX9Renderer& Instance();

		// Initialise le renderer
		virtual void Initialize();

		// Boucle de rendu
		virtual bool Update();

		// Démarre le rendu de la scène
		virtual void BeginScene() const;

		// Termine le rendu de la scène
		virtual void EndScene() const;

		// Quitte le renderer
		virtual void Quit() const;

	private:
		// Données membres
		DX9Renderer();

		// Instance du renderer chargée
		LPDIRECT3DDEVICE9 m_Device;

	};

} // namespace crea

#endif // _DX9Renderer_H