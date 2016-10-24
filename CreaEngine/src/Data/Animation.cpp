#include "stdafx.h"
////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "Data\Animation.h"
#include "Graphics\IGraphics.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace crea
{
	Animation::Animation() : m_texture(NULL)
	{

	}

	void Animation::addFrame(IntRect rect)
	{
		m_frames.push_back(rect);
	}

	void Animation::setSpriteSheet(ITexture& texture)
	{
		m_texture = &texture;
	}

	ITexture* Animation::getSpriteSheet()
	{
		return m_texture;
	}

	std::size_t Animation::getSize()
	{
		return m_frames.size();
	}

	IntRect& Animation::getFrame(std::size_t n)
	{
		return m_frames[n];
	}

	string getParam(string _s, int _i)
	{
		istringstream iss(_s);
		string token;
		int i = 0;
		getline(iss, token, ':');
		while (getline(iss, token, ','))
		{
			if (i == _i)
			{
				return token;
			}
			i++;
		}
		return "";
	}

	bool Animation::loadFromFile(string _filename)
	{
		ifstream isFile;
		char caLine[256];
		int iLine = 0;
		int x = 0, y = 0, sizex = 0, sizey = 0;

		// On ouvre le fichier
		isFile.open(_filename, ios::in);
		if (isFile.fail())
		{
			cerr << "erreur d'ouverture " << _filename << endl;
			return false;
		}

		do
		{
			// On parcoure le fichier
			isFile.getline(caLine, sizeof(caLine));
			iLine++;
			switch (iLine)
			{
			case 1: // spritesheet
				setSpriteSheet(*DataManager::getSingleton()->getTexture(caLine));
				break;
			case 2: // format
				break;
			case 3: // filter
				break;
			case 4: // repeat
				break;
			case 5: // frame
				break;
			case 6: // rotate
				break;
			case 7: // xy
				x = stoi(getParam(caLine, 0)); 
				y = stoi(getParam(caLine, 1));
				break;
			case 8: // size
				sizex = stoi(getParam(caLine, 0));
				sizey = stoi(getParam(caLine, 1));
				break;
			case 9: // orig
				break;
			case 10: // offset
				break;
			case 11: // index
				addFrame(IntRect(x, y, sizex, sizey)); // CB: for now index is not used, order in file is important (to do : use a map)
				iLine = 4; // repeat frame loading
				break;
			default:
				break;
			}
		} while (!isFile.eof());

		isFile.close();
		return true;
	}

} // namespace crea