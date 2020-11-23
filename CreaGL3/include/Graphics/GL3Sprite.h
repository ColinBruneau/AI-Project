/***************************************************/
/* Nom:	GL3Sprite.h
/* Description: GL3Sprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Sprite_H
#define _GL3Sprite_H

#include "Graphics\Sprite.h"
#include "Graphics\GL3Shape.h"
#include "Graphics\GL3Material.h"

namespace crea
{

	class GL3Sprite : public Sprite
	{
		GL3Material* m_pMaterial;
		GL3RectangleShape m_quad;
		IntRect m_textureRect;
		bool m_bShaderApplied = false;
		Texture* m_pTexture = nullptr;

	public:

		GL3Sprite::GL3Sprite()
		{
			// Clone the sprite material
			m_pMaterial = (GL3Material*)GameManager::getSingleton()->getMaterial("sprite.mat", true);
			m_textureRect.m_iW = 0;
			m_textureRect.m_iH = 0;
		}

		virtual GL3Sprite::~GL3Sprite()
		{
		}

		virtual void draw()
		{			
			// Pre Draw
			if (m_pMaterial != nullptr)
			{
				// Apply shader on shape
				if (!m_bShaderApplied)
				{
					if (m_pMaterial)
						m_pMaterial->setTexture(0, "texture1", m_pTexture);

					m_pMaterial->applyShaderToShape(&m_quad);
					m_bShaderApplied = true;
				}

				// Use our shader on Entity
				m_pMaterial->use();

			}

			m_quad.draw();

			// Post Draw
			if (m_pMaterial != nullptr)
			{
				// Unset shader
				m_pMaterial->unuse();
			}
		}

		virtual void setTexture(Texture* _pTexture)
		{
			// update quad with new texture sizes and window sizes
			if (m_pTexture != _pTexture)
			{
				m_pTexture = _pTexture;
				GL3Texture* pTexture = (GL3Texture*)m_pTexture;
				m_quad.setTextureSize(pTexture->getWidth(), pTexture->getHeight());

				//When texture changes, adjust display size but also make sure to reset texture rect...
				m_quad.setDisplaySize(pTexture->getWidth(), pTexture->getHeight());
				m_textureRect = IntRect (0, 0, 1, 1);

				GameManager* pGM = GameManager::getSingleton();
				IntRect r = pGM->getWindowRect();
				m_quad.setWindowSize(r.getWidth(), r.getHeight()); 
				m_bShaderApplied = false; // to reapply texture
			}
		}

		Texture* getTexture()
		{
			return m_pTexture;
		}

		virtual void setPosition(float _x, float _y)
		{
			// todo: sprite position (GL3)
			//m_Position.x = _x;
			//m_Position.y = _y;
			m_quad.setPosition(_x, _y);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			IntRect _rect(_x, _y, _w, _h);
			if (m_textureRect != _rect)
			{
				m_textureRect = _rect;
				float w = (float)m_textureRect.m_iW;
				float h = (float)m_textureRect.m_iH;
				//m_quad.setSize(w, h);
				GL3Texture* pTexture = (GL3Texture*)m_pTexture;
				if (pTexture)
				{
					w = (float)pTexture->getWidth();
					h = (float)pTexture->getHeight();
				}
				FloatRect rectNormalised;
				rectNormalised.m_fX = _rect.m_iX / w;
				rectNormalised.m_fY = _rect.m_iY / h;
				rectNormalised.m_fW = _rect.m_iW / w;
				rectNormalised.m_fH = _rect.m_iH / h;
				// UV
				VertexUV uv[] = {
					{ rectNormalised.m_fX , 1 - rectNormalised.m_fY - rectNormalised.m_fH},// bottom left
					{ rectNormalised.m_fX, 1 - rectNormalised.m_fY},// top left 
					{ rectNormalised.m_fX + rectNormalised.m_fW, 1 - rectNormalised.m_fY - rectNormalised.m_fH },// bottom right
					{ rectNormalised.m_fX + rectNormalised.m_fW, 1 - rectNormalised.m_fY }// top right 
				};
				
				m_quad.setVerticesUV(uv, 4); 
				m_quad.setDisplaySize(_rect.m_iW, _rect.m_iH);
			}
		}

		virtual void setScale(float _x, float _y)
		{
			// todo: sprite scale (GL3)
			//m_pScale->x = _x;
			//m_pScale->y = _y;
			m_quad.setScale(_x, _y);
		}

		virtual void setOrigin(float _x, float _y)
		{
			// todo: sprite origin (GL3)
			//m_pScaleCenter->x = _x;
			//m_pScaleCenter->y = _y;
			m_quad.setOrigin(_x, _y);
		}

		virtual GL3Sprite* clone() 
		{
			GL3Sprite* pSprite = new GL3Sprite();
			// Material is already a clone
			pSprite->setTexture(this->m_pTexture);
			//todo: ici il faudrait cloner le quad correctement!
			pSprite->m_quad = this->m_quad;
			return pSprite;
		}
	};

} // namespace crea

#endif // _GL3Sprite_H
