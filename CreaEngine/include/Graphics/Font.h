/***************************************************/
/* Nom:	Font.h
/* Description: Font
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Font_H
#define _Font_H

namespace crea
{

	class CREAENGINE_API Font
	{
	public:

		Font() {}
		virtual ~Font() {}

		// Initialise le Font
		virtual bool loadFromFile(std::string _file) { return false; }
	};

} // namespace crea

#endif // _Font_H