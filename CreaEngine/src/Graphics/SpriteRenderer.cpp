#include "stdafx.h"

#include "Graphics\SpriteRenderer.h"

namespace crea
{
	SpriteRenderer::SpriteRenderer()
	{
		m_pSprite = nullptr;
		m_pTextureRect = nullptr;
		GameManager* m_pGM = GameManager::getSingleton();
		m_bActive = true;
	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	bool SpriteRenderer::loadFromFileJSON(const string& _filename)
	{
		Json::Value root;
		std::ifstream srStream(_filename, std::ifstream::binary);
		if (srStream.fail())
		{
			cerr << "Can't open SpriteRenderer file: " << _filename << endl;
			return false;
		}
		srStream >> root;

		string szSprite = root["sprite"].asString();
		Sprite* pSprite = m_pGM->getSprite(szSprite);

		string szTexture = root["image"].asString();
		Texture* pTexture = m_pGM->getTexture(szTexture);
		pSprite->setTexture(pTexture);

		setSprite(pSprite);

		return true;
	}

	bool SpriteRenderer::init()
	{
		return true;
	}
	
	bool SpriteRenderer::update()
	{
		return true;
	}
	
	bool SpriteRenderer::draw()
	{
		if (m_pSprite && m_bActive)
		{
			// Set sprite position
			Vector2f vPos = getEntity()->getPosition();
			m_pSprite->setPosition(vPos.getX(), vPos.getY());
			if (m_pTextureRect)
			{
				m_pSprite->setTextureRect(m_pTextureRect->getLeft(), m_pTextureRect->getTop(),
					m_pTextureRect->getWidth(), m_pTextureRect->getHeight());
			}

			// Draw
			m_pSprite->draw();
		}

		return true;
	}
	
	bool SpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
