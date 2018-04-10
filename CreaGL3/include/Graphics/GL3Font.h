/***************************************************/
/* Nom:	GL3Font.h
/* Description: GL3Font
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Font_H
#define _GL3Font_H

#include "Graphics\IFont.h"

namespace crea
{

	class GL3Font : public IFont
	{
		//LPD3DXFONT 
		void* m_pFont;
	public:
		GL3Font() { m_pFont = nullptr; }
		~GL3Font() { SafeDelete(m_pFont); }

		//LPD3DXFONT 
		void* getFont() { return m_pFont; }

		// Initialise le Font
		virtual bool loadFromFile(string _file)
		{
			/*
			HRESULT hr = D3DXCreateFont(GL3Facade::Instance().m_pDevice,     //D3D Device
				0,               //Font height
				0,                //Font width
				FW_NORMAL,        //Font Weight
				0,                //MipLevels
				false,            //Italic
				DEFAULT_CHARSET,  //CharSet
				OUT_DEFAULT_PRECIS, //OutputPrecision
				DEFAULT_QUALITY, //Quality
				DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
				_file.c_str(),          //pFacename,
				&m_pFont);         //ppFont
			if (FAILED(hr))
			{
				OutputDebugString("Failed to create font.\n");
			}
			*/
			return true;
		}
	};

} // namespace crea

#endif // _GL3Font_H
