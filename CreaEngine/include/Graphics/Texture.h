/***************************************************/
/* Nom:	Texture.h
/* Description: Texture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Texture_H
#define __Texture_H

namespace crea
{
	class CREAENGINE_API Texture
	{
	public:

		Texture() {}

		~Texture() {}

		virtual bool loadFromFile(const string& _file) { return false; }

	};

} // namespace crea

#endif // __Texture_H