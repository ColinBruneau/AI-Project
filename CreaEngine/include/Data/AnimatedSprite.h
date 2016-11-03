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

#ifndef ANIMATEDSPRITE_INCLUDE
#define ANIMATEDSPRITE_INCLUDE

#include "Data\Animation.h"
#include "Graphics\Transformable.h"
#include "Core\Time.h"
#include "Graphics\IGraphics.h"

namespace crea
{
	class Transformable;

	class CREAENGINE_API AnimatedSprite : public Transformable
	{
	public:
		explicit AnimatedSprite(Time& frameTime = Time(0.2f), bool paused = false, bool looped = true);

		void update(Time& deltaTime);
		void setAnimation(Animation& animation);
		void setFrameTime(Time& time);
		void play();
		void play( Animation& animation);
		void pause();
		void stop();
		void setLooped(bool looped);
		Animation* getAnimation() ;
		FloatRect getLocalBounds() ;
		FloatRect getGlobalBounds() ;
		bool isLooped() ;
		bool isPlaying() ;
		Time getFrameTime() ;
		IntRect getFrame();
		ITexture* getTexture() { return m_texture; }
		
	private:
		Animation* m_animation;
		Time m_frameTime;
		Time m_currentTime;
		std::size_t m_currentFrame;
		bool m_isPaused;
		bool m_isLooped;
		ITexture* m_texture;

	};

} // namespace crea

#endif // ANIMATEDSPRITE_INCLUDE
