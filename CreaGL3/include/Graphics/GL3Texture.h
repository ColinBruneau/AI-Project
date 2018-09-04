/***************************************************/
/* Nom:	GL3Texture.h
/* Description: GL3Texture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Texture_H
#define _GL3Texture_H

#include "Graphics\Texture.h"

namespace crea
{

	class GL3Texture : public Texture
	{
		//LPDIRECT3DTEXTURE9 
		void* m_pTexture;
	public:
		//LPDIRECT3DTEXTURE9 getTexture() { return m_pTexture; }

		GL3Texture() { m_pTexture = nullptr; }
		~GL3Texture() { SafeDelete(m_pTexture); }

		virtual bool loadFromFile(string _file)
		{/*
			if (FAILED(D3DXCreateTextureFromFile(GL3Facade::Instance().m_pDevice, _file.c_str(), &m_pTexture)))
			{
				cerr << "Failed to load texture Sprite." << endl;
				return false;
			}
			*/
			return true;
		}
	};

} // namespace crea

#endif // _GL3Texture_H
