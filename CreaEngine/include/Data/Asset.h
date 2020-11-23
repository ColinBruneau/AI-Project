/***************************************************/
/* Nom:	Asset.h
/* Description: Asset
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Asset_H_
#define __Asset_H_

namespace crea
{

	class CREAENGINE_API Asset
	{

	public:
		Asset();
		virtual ~Asset();

		virtual bool loadFromFile(const string& _name) = 0;
		virtual Asset* clone() = 0;

	};

} // namespace crea

#endif
