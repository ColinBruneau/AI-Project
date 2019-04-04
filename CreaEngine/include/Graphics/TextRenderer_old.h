/***************************************************/
/* Nom:	TextRenderer.h
/* Description: TextRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __TextRenderer_H_
#define __TextRenderer_H_

#include "Core\Component.h"

namespace crea
{
	class IText;

	class CREAENGINE_API TextRenderer : public Component
	{
		IText* m_pText;
		IntRect* m_pTextureRect;

	public:
		TextRenderer();
		virtual ~TextRenderer();

		inline void setText(IText* _pText) { m_pText = _pText; }
		void setTextureRect(IntRect* _pTextureRect) { m_pTextureRect = new IntRect(*_pTextureRect); }

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
