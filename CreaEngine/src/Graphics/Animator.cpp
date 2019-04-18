#include "stdafx.h"

#include "Graphics\Animator.h"
#include "Core\GameManager.h"
#include "Core\TimeManager.h"
#include "Core\EntityManager.h"
#include "Graphics\Sprite.h"

namespace crea
{
	Animator::Animator()
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::setSprite(Sprite* _pSprite)
	{
		m_pSprite = _pSprite;
	}

	void Animator::setAnimation(Animation& animation)
	{
		m_pAnimation = &animation;
		m_currentFrame = 0;
		m_currentTime = 0.f;
	}

	void Animator::setFrameTime(Time& time)
	{
		m_frameTime = time;
	}

	Animation* Animator::getAnimation()
	{
		return m_pAnimation;
	}

	bool Animator::isPlaying()
	{
		return !m_isPaused;
	}

	Time Animator::getFrameTime()
	{
		return m_frameTime;
	}

	IntRect Animator::getFrame()
	{
		if (m_pAnimation)
		{
			return m_pAnimation->getFrame(m_currentFrame);
		}
		return IntRect();
	}

	void Animator::play()
	{
		m_isPaused = false;
	}

	void Animator::play(Animation& animation)
	{
		if (getAnimation() != &animation)
			setAnimation(animation);
		play();
	}

	void Animator::pause()
	{
		m_isPaused = true;
	}

	void Animator::stop()
	{
		m_isPaused = true;
		m_currentFrame = 0;
		m_currentTime = 0.f;
	}

	bool Animator::loadFromFileJSON(const string& _filename)
	{
		// TD Animation
		Json::Value root;
		std::ifstream srStream(_filename, std::ifstream::binary);
		if (srStream.fail())
		{
			cerr << "Can't open SpriteRenderer file: " << _filename << endl;
			return false;
		}
		srStream >> root;

		string szSprite = root["sprite"].asString();
		GameManager* pGM = GameManager::getSingleton();
		m_pSprite = pGM->getSprite(szSprite);

		return true;
	}

	bool Animator::init()
	{
		return true;
	}

	bool Animator::update()
	{
		// if sprite not set, try to get it from SpriteRenderer
		if (!m_pSprite)
		{
			SpriteRenderer* pSr = getEntity()->getComponent<SpriteRenderer>();
			if (pSr)
			{
				m_pSprite = pSr->getSprite();
			}
		}

		// if not paused and we have a valid animation
		if (!m_isPaused && m_pAnimation)
		{
			// add delta time
			m_currentTime += (TimeManager::getSingleton()->getFrameTime()*m_pAnimation->getSpeed());

			// Get the current animation frame
			float fScaledTime = (float)(m_currentTime.asSeconds() / m_pAnimation->getDuration().asSeconds());
			int iNumFrames = m_pAnimation->getSize();
			m_currentFrame = (int)(fScaledTime * iNumFrames);

			// If the animation is looping, calculate the correct frame
			if (m_pAnimation->getLooping())
			{
				m_currentFrame %= iNumFrames;
			}
			else if (m_currentFrame >= iNumFrames) // If the current frame is greater than the number of frames
			{
				m_currentFrame = iNumFrames - 1; // Show last frame
			}
		}

		if (m_pSprite && m_pAnimation)
		{
			m_pSprite->setTexture(m_pAnimation->getSpriteSheet());

			IntRect rect = m_pAnimation->getFrame(m_currentFrame);
			float fFlipH = (rect.getWidth() < 0) ? -1.0f : 1.0f;// width < 0 means flipH
			float fFlipV = (rect.getHeight() < 0) ? -1.0f : 1.0f;// height < 0 means flipV

			m_pSprite->setTextureRect(
				rect.getLeft(),
				rect.getTop(),
				rect.getWidth()*(int)fFlipH,
				rect.getHeight()*(int)fFlipV);

			m_pSprite->setScale(fFlipH, fFlipV);

			// CB: SpriteRenderer is already setting the position
		}
		return true;
	}

	bool Animator::draw()
	{
		return true;
	}

	bool Animator::quit()
	{
		return true;
	}

} // namespace crea
