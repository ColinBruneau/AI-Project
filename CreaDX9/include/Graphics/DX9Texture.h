/***************************************************/
/* Nom:	DX9Texture.h
/* Description: DX9Texture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Texture_H
#define _DX9Texture_H

#include "Graphics\ITexture.h"

namespace crea
{

	class DX9Texture : public ITexture
	{
		LPDIRECT3DTEXTURE9 m_pTexture;
	public:
		LPDIRECT3DTEXTURE9 getTexture() { return m_pTexture; }

		DX9Texture()
		{
		}

		~DX9Texture()
		{
		}

		virtual bool loadFromFile(string _file)
		{
			//return m_texture.loadFromFile(_file);
			if (FAILED(D3DXCreateTextureFromFile(DX9Facade::Instance().m_pDevice, _file.c_str(), &m_pTexture)))
			{
				cerr << "Failed to load texture Sprite." << endl;
				return false;
			}
			return true;
		}
	};

} // namespace crea

#endif // _DX9Texture_H
