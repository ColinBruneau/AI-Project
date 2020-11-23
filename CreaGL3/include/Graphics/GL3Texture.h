/***************************************************/
/* Nom:	GL3Texture.h
/* Description: GL3Texture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Texture_H
#define _GL3Texture_H

#include "Graphics\Texture.h"

namespace crea
{

	class GL3Texture : public Texture
	{
	protected:
		string m_name;
		unsigned int m_texture;
		bool m_transparency;
		unsigned char* m_data;
		int m_width, m_height, m_nrChannels;
		static bool m_flipVerticallyOnLoad;

		void send();

	public:
		GL3Texture();
		virtual ~GL3Texture();

		inline void setID(unsigned int _id) { m_texture = _id; }
		inline unsigned int getID() { return m_texture; }

		inline void setTransparency(bool _transparency) { m_transparency = _transparency; send(); }
		inline bool getTransparency() { return m_transparency; }

		static void flipVerticallyOnLoad(bool _flipVerticallyOnLoad) { m_flipVerticallyOnLoad = _flipVerticallyOnLoad; }

		inline int getWidth() { return m_width; }
		inline int getHeight() { return m_height; }
		inline int getChannels() { return m_nrChannels; }

		virtual bool loadFromFile(const string& _name);

		// use the texture
		virtual void bind(unsigned int _channel);
		virtual void unbind(unsigned int _channel);
	};

} // namespace crea

#endif // _GL3Texture_H
