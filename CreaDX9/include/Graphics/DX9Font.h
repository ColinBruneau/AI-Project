/***************************************************/
/* Nom:	DX9Font.h
/* Description: DX9Font
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Font_H
#define _DX9Font_H

#include "Graphics\Font.h"

namespace crea
{

	class DX9Font : public Font
	{
		LPD3DXFONT m_pFont;
		string m_szFont;
		int m_iHeight;
	public:
		DX9Font() 
		{ 
			m_pFont = nullptr;
			m_szFont = "";
			m_iHeight = 10;
		}
		~DX9Font() { SafeRelease(m_pFont); }

		LPD3DXFONT getFont() { return m_pFont; }

		string getFontShortName(string& _s)
		{
			int startPos = _s.rfind("/");
			int endPos = _s.rfind(".");
			return _s.substr(startPos + 1, endPos - startPos - 1);
		}

		// Initialise le Font
		virtual bool loadFromFile(string _file)
		{
			SafeRelease(m_pFont);
			m_szFont = _file;
			AddFontResourceEx(_file.c_str(), FR_PRIVATE, 0);
			HRESULT hr = D3DXCreateFont(DX9Facade::Instance().m_pDevice,     //D3D Device
				m_iHeight,        //Font height
				0,                //Font width
				FW_NORMAL,        //Font Weight
				0,                //MipLevels
				false,            //Italic
				DEFAULT_CHARSET,  //CharSet
				OUT_DEFAULT_PRECIS, //OutputPrecision
				DEFAULT_QUALITY, //Quality
				DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
				getFontShortName(_file).c_str(),//pFacename,
				&m_pFont);         //ppFont
			if (FAILED(hr))
			{
				OutputDebugString("Failed to create font.\n");
			}

			return true;
		}

		virtual void setFontSize(int _iSize)
		{
			if (m_iHeight != _iSize)
			{
				m_iHeight = _iSize;
				loadFromFile(m_szFont);
			}
		}

	};

} // namespace crea

#endif // _DX9Font_H
