/***************************************************/
/* Nom:	AnimatedSpriteRenderer.h
/* Description: AnimatedSpriteRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AnimatedSpriteRenderer_H_
#define __AnimatedSpriteRenderer_H_

#include "Core\Component.h"
#include "Data\AnimatedSprite.h"

namespace crea
{

	class CREAENGINE_API AnimatedSpriteRenderer : public Component
	{
		AnimatedSprite* m_pAnimatedSprite;
		ISprite* m_pSprite;

	public:
		AnimatedSpriteRenderer(string _szName);
		virtual ~AnimatedSpriteRenderer();

		inline void setAnimatedSprite(AnimatedSprite* _pAnimatedSprite) { m_pAnimatedSprite = _pAnimatedSprite; }

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

	};

} // namespace crea

#endif
