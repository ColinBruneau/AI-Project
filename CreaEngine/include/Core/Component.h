/***************************************************/
/* Nom:	Component.h
/* Description: Component
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Component_H_
#define __Component_H_

namespace crea
{

	class CREAENGINE_API Component
	{

	public:
		Component();
		virtual ~Component();

		virtual bool init() = 0;
		virtual bool update() = 0;
		virtual bool draw() = 0;
		virtual bool quit() = 0;

	};

} // namespace crea

#endif
