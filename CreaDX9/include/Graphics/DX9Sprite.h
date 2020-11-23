/***************************************************/
/* Nom:	DX9Sprite.h
/* Description: DX9Sprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Sprite_H
#define _DX9Sprite_H

#include "Graphics\Sprite.h"

namespace crea
{

	class DX9Sprite : public Sprite
	{
		LPD3DXSPRITE m_pSprite;
		LPDIRECT3DTEXTURE9 m_pTexture;
		RECT *m_pRect;
		D3DXVECTOR2 *m_pCenter;
		float m_fRotation;
		D3DXVECTOR2 *m_pScaleCenter;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_Position;
		D3DCOLOR m_color;

	public:

		DX9Sprite::DX9Sprite()
		{
			//init translation
			m_Position.x = 0.0f;
			m_Position.y = 0.0f;

			//init rectangle
			m_pRect = nullptr;

			//init center
			m_pCenter = nullptr;

			//init de la rotation
			m_fRotation = 0.0f;

			//init du centre de scale
			m_pScaleCenter = nullptr;

			//init du scale
			m_pScale = nullptr;

			//init color
			m_color = D3DCOLOR_XRGB(255, 255, 255);

			//init pointeur texture
			m_pTexture = nullptr;

			//creation du sprite
			if (FAILED(D3DXCreateSprite(DX9Facade::Instance().m_pDevice, &m_pSprite)))
			{
				OutputDebugString("Failed to create Sprite.\n");
			}

		}

		virtual DX9Sprite::~DX9Sprite()
		{
			SafeDelete(m_pRect);
			SafeDelete(m_pCenter);
			SafeDelete(m_pScaleCenter);
			SafeDelete(m_pScale);
			SafeRelease(m_pTexture);
			SafeRelease(m_pSprite);
		}

		// Build 2D transformation matrix in XY plane. NULL arguments are treated as identity.
		// Mout = Morig-1 * Ms * Mt
		D3DXMATRIX* myMatrixTransformation2D
		(D3DXMATRIX *pOut, 
			CONST D3DXVECTOR2* pOrigin,
			CONST D3DXVECTOR2* pScaling,
			CONST D3DXVECTOR2* pTranslation)
		{
			D3DXMATRIX Morig, Ms, Mt;
			D3DXMatrixIdentity(pOut);
			if (pOrigin)
			{
				D3DXMatrixTranslation(&Morig, pOrigin->x, pOrigin->y, 0.0f);
				float fDet = 0.f;
				D3DXMatrixInverse(pOut, &fDet, &Morig);
			}
			if (pScaling)
			{
				D3DXMatrixScaling(&Ms, pScaling->x, pScaling->y, 1.0f);
				D3DXMatrixMultiply(pOut, pOut, &Ms);
			}
			if (pTranslation)
			{
				//cout << pTranslation->x << " " << pTranslation->y << endl;
				D3DXMatrixTranslation(&Mt, pTranslation->x, pTranslation->y, 0.0f);
				D3DXMatrixMultiply(pOut, pOut, &Mt);
			}
			return pOut;
		}

		virtual void draw()
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

			// Build our matrix to rotate, scale and position our sprite
			D3DXMATRIX mat;

			// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
			myMatrixTransformation2D(&mat, m_pScaleCenter, m_pScale, &m_Position);

			// Tell the sprite about the matrix
			m_pSprite->SetTransform(&mat);

			// Draw the sprite 
			m_pSprite->Draw(m_pTexture, m_pRect, NULL, NULL, m_color);

			// Thats it
			m_pSprite->End();
		}

		virtual void setTexture(Texture* _pTexture)
		{
			DX9Texture* pTexture = (DX9Texture*)_pTexture;
			m_pTexture = (LPDIRECT3DTEXTURE9)pTexture->getTexture();
		}

		virtual void setPosition(float _x, float _y)
		{
			m_Position.x = _x;
			m_Position.y = _y;
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			if (!m_pRect)
				m_pRect = new RECT();
			
			m_pRect->left = _x;
			m_pRect->top = _y;
			m_pRect->bottom = _y + _h;
			m_pRect->right = _x + _w;			
		}

		virtual void setScale(float _x, float _y)
		{
			if (!m_pScale)
				m_pScale = new D3DXVECTOR2();

			m_pScale->x = _x;
			m_pScale->y = _y;
		}

		virtual void setOrigin(float _x, float _y)
		{
			if (!m_pScaleCenter)
				m_pScaleCenter = new D3DXVECTOR2(); // CB: why do we need (0,0), not nothing, nor (36, 36) in DirectX? 
			
			m_pScaleCenter->x = _x;
			m_pScaleCenter->y = _y;
		}

		virtual Sprite* clone()
		{
			return new DX9Sprite(*this);
		}
	};

} // namespace crea

#endif // _DX9Sprite_H
