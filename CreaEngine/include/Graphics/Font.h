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

		virtual bool loadFromFile(const string& _file) { return false; }

		virtual void setFontSize(int _iSize) {}
	};

} // namespace crea

#endif // _Font_H