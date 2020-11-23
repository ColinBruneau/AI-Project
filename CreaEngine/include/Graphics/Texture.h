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

		virtual ~Texture() {}

		virtual inline void setTransparency(bool _transparency) { }

		virtual inline bool getTransparency() { return false; }

		virtual bool loadFromFile(const string& _file) { return false; }

		virtual void bind(unsigned int _channel) {}

		virtual void unbind(unsigned int _channel) {}

	};

} // namespace crea

#endif // __Texture_H