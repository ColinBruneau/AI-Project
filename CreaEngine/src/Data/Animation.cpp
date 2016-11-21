#include "stdafx.h"

#include "Data\Animation.h"
#include "Graphics\IGraphics.h"

#include "json\json.h"
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

	bool Animation::loadFromFileJSON(string _filename)
	{
		Json::Value root;
		std::ifstream config_doc(_filename, std::ifstream::binary);
		config_doc >> root;

		Json::Value spritesheet = root["spritesheet"];
		setSpriteSheet(*DataManager::getSingleton()->getTexture(spritesheet.asString()));

		Json::Value frames = root["frames"];
		for (unsigned int iFrame = 0; iFrame < frames.size(); ++iFrame)
		{
			Json::Value frame = frames[iFrame];
			addFrame(IntRect(frame["x"].asInt(), frame["y"].asInt(), frame["w"].asInt(), frame["h"].asInt()));
		}

		Json::Value multiframes = root["multiframes"];
		for (unsigned int imultiFrame = 0; imultiFrame < multiframes.size(); ++imultiFrame)
		{
			Json::Value multiframe = multiframes[imultiFrame];
			for (int i = 0; i < multiframe["frames"].asInt(); i++)
			{
				addFrame(IntRect(	multiframe["x"].asInt()+i*multiframe["offsetx"].asInt(), 
									multiframe["y"].asInt()+i*multiframe["offsety"].asInt(), 
									multiframe["w"].asInt(), 
									multiframe["h"].asInt()));
			}
		}
		return true;
	}
} // namespace crea