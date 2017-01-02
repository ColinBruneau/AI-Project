/***************************************************/
/* Nom:	DX9Font.h
/* Description: DX9Font
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Font_H
#define _DX9Font_H

#include "Graphics\IFont.h"

namespace crea
{

	class DX9Font : public IFont
	{
		LPD3DXFONT m_pFont;
	public:
		LPD3DXFONT getFont() { return m_pFont; }

		// Initialise le Font
		virtual bool loadFromFile(string _file)
		{
			//return m_font.loadFromFile(_file); // CB: load font instead of creating a new one...

			HRESULT hr = D3DXCreateFont(DX9Facade::Instance().m_pDevice,     //D3D Device
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

			return true;
		}
	};

} // namespace crea

#endif // _DX9Font_H
