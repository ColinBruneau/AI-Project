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
	protected:
		Entity* m_pEntity; // The entity this component is attached to.

	public:
		Component();
		virtual ~Component();

		inline void setEntity(Entity* _pEntity)	{ m_pEntity = _pEntity; }
		inline Entity* getEntity()				{ return m_pEntity; }

		virtual bool init() = 0;
		virtual bool update() = 0;
		virtual bool draw() = 0;
		virtual bool quit() = 0;

	};

} // namespace crea

#endif
