/***************************************************/
/* Nom:	SpriteRenderer.h
/* Description: SpriteRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SpriteRenderer_H_
#define __SpriteRenderer_H_

#include "Core\Component.h"
#include "Core\Math.h"

namespace crea
{

	class CREAENGINE_API SpriteRenderer : public Component
	{
		Sprite* m_pSprite;
		Material* m_pMaterial;
		bool m_bShaderApplied;
		IntRect* m_pTextureRect;
		GameManager* m_pGM;
		bool m_bActive;

	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		inline void setSprite(Sprite* _pSprite) { m_pSprite = _pSprite; }
		inline Sprite* getSprite() { return m_pSprite; }

		inline void setMaterial(Material* _pMaterial) { m_pMaterial = _pMaterial; }
		Material* getMaterial() { return m_pMaterial; }

		void setTextureRect(IntRect* _pTextureRect) { m_pTextureRect = new IntRect(*_pTextureRect); }
		inline void setActive(bool _bActive) { m_bActive = _bActive; }
		
		bool loadFromFileJSON(const string& _filename);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

		virtual Component* clone() 
		{ 
			SpriteRenderer* p = new SpriteRenderer(*this); 
			p->m_pSprite = m_pSprite->clone();
			if (m_pTextureRect)
			{
				p->m_pTextureRect = new IntRect(*m_pTextureRect);
			}
			return p;
		}
	};

} // namespace crea

#endif
