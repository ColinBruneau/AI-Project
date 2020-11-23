/***************************************************/
/* Nom:	DX9Texture.h
/* Description: DX9Texture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Texture_H
#define _DX9Texture_H

#include "Graphics\Texture.h"

namespace crea
{

	class DX9Texture : public Texture
	{
		LPDIRECT3DTEXTURE9 m_pTexture;
	public:
		LPDIRECT3DTEXTURE9 getTexture() { return m_pTexture; }

		DX9Texture() { m_pTexture = nullptr; }
		virtual ~DX9Texture() { SafeRelease(m_pTexture); }

		virtual inline void setTransparency(bool _transparency) { /*todo: handletransparency for DX9*/ }

		virtual inline bool getTransparency() { return false; }

		virtual bool loadFromFile(const string& _file)
		{
			if (FAILED(D3DXCreateTextureFromFile(DX9Facade::Instance().m_pDevice, _file.c_str(), &m_pTexture)))
			{
				cerr << "Failed to load texture Sprite." << endl;
				return false;
			}
			return true;
		}

		virtual void bind(unsigned int _channel) {}

		virtual void unbind(unsigned int _channel) {}
	};

} // namespace crea

#endif // _DX9Texture_H
