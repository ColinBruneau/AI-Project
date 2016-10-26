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

#include "Data\AnimatedSprite.h"

namespace crea
{
	AnimatedSprite::AnimatedSprite(Time& frameTime, bool paused, bool looped) :
		m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped), m_texture(NULL)
	{

	}

	void AnimatedSprite::setAnimation(Animation& animation)
	{
		m_animation = &animation;
		m_texture = m_animation->getSpriteSheet();
		m_currentFrame = 0;
		m_currentTime = 0.f;
	}

	void AnimatedSprite::setFrameTime(Time& time)
	{
		m_frameTime = time;
	}

	void AnimatedSprite::play()
	{
		m_isPaused = false;
	}

	void AnimatedSprite::play(Animation& animation)
	{
		if (getAnimation() != &animation)
			setAnimation(animation);
		play();
	}

	void AnimatedSprite::pause()
	{
		m_isPaused = true;
	}

	void AnimatedSprite::stop()
	{
		m_isPaused = true;
		m_currentFrame = 0;
		m_currentTime = 0.f;
	}

	void AnimatedSprite::setLooped(bool looped)
	{
		m_isLooped = looped;
	}

    Animation* AnimatedSprite::getAnimation() 
	{
		return m_animation;
	}

	FloatRect AnimatedSprite::getLocalBounds() 
	{
		IntRect rect = m_animation->getFrame(m_currentFrame);

		float width = (float) std::abs(rect.getWidth());
		float height = (float) std::abs(rect.getHeight());

		return FloatRect(0.f, 0.f, width, height);
	}

	FloatRect AnimatedSprite::getGlobalBounds() 
	{
		return getTransform().transformRect(getLocalBounds());
	}

	bool AnimatedSprite::isLooped() 
	{
		return m_isLooped;
	}

	bool AnimatedSprite::isPlaying() 
	{
		return !m_isPaused;
	}

	Time AnimatedSprite::getFrameTime() 
	{
		return m_frameTime;
	}

	IntRect AnimatedSprite::getFrame()
	{
		if (m_animation)
		{
			return m_animation->getFrame(m_currentFrame);
		}
		return IntRect();
	}

	void AnimatedSprite::update(Time& deltaTime)
	{
		// if not paused and we have a valid animation
		if (!m_isPaused && m_animation)
		{
			// add delta time
			m_currentTime += deltaTime;

			// if current time is bigger then the frame time advance one frame
			if (m_currentTime >= m_frameTime)
			{
				// reset time, but keep the remainder
				//m_currentTime = Imicroseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
				int cur = m_currentTime.asMicroseconds();
				int mod = m_frameTime.asMicroseconds();
				int res = cur % mod;
				m_currentTime.setAsMicroSeconds(res);

				// get next Frame index
				if (m_currentFrame + 1 < m_animation->getSize())
					m_currentFrame++;
				else
				{
					// animation has ended
					m_currentFrame = 0; // reset to start

					if (!m_isLooped)
					{
						m_isPaused = true;
					}

				}

				//current frame is set, not reseting the time
			}
		}
	}
} // namespace crea