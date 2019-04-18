/***************************************************/
/* Nom:	ScriptFactory.h
/* Description: ScriptFactory
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _ScriptFactory_H
#define _ScriptFactory_H

namespace crea
{
	class CREAENGINE_API ScriptFactory {
	public:
		ScriptFactory()
		{
		}

		virtual ~ScriptFactory()
		{
		}
		virtual Script* create(const string& _szName) = 0;
	};

} // namespace crea

#endif // _ScriptFactory_H