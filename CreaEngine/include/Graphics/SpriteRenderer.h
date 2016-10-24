/***************************************************/
/* Nom:	SpriteRenderer.h
/* Description: SpriteRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SpriteRenderer_H_
#define __SpriteRenderer_H_

#include "Core\Component.h"

namespace crea
{
	class ISprite;

	class CREAENGINE_API SpriteRenderer : public Component
	{
		ISprite* m_pSprite;

	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		inline void setSprite(ISprite* _pSprite) { m_pSprite = _pSprite; }

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

	};

} // namespace crea

#endif
