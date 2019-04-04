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
		ISprite* m_pSprite;
		ISprite* m_pSelectionSprite;
		IntRect* m_pTextureRect;

	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		inline void setSprite(ISprite* _pSprite) { m_pSprite = _pSprite; }
		inline ISprite* getSprite() { return m_pSprite; }

		void setTextureRect(IntRect* _pTextureRect) { m_pTextureRect = new IntRect(*_pTextureRect); }

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

		virtual Component* clone() 
		{ 
			SpriteRenderer* p = new SpriteRenderer(*this); 
			p->m_pSprite = IFacade::get().createISprite(m_pSprite);
			m_pTextureRect = nullptr;
			return p; 
		}
	};

} // namespace crea

#endif
