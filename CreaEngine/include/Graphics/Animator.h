/***************************************************/
/* Nom:	Animator.h
/* Description: Animator
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Animator_H_
#define __Animator_H_

#include "Core\Component.h"
#include "Core\Math.h"
#include "Core\TimeManager.h"
#include "Graphics\SpriteRenderer.h"
#include "Data\Animation.h"

namespace crea
{

	class CREAENGINE_API Animator : public Component
	{
		Sprite* m_pSprite;
		Animation* m_pAnimation;
		Time m_frameTime;
		Time m_currentTime;
		int m_currentFrame;
		bool m_isPaused;

	public:
		Animator();
		virtual ~Animator();

		void setSprite(Sprite* _pSprite);
		void setAnimation(Animation& animation);
		void setFrameTime(Time& time);

		Animation* getAnimation();
		Time getFrameTime();
		IntRect getFrame();

		bool isPlaying();

		void play();
		void play(Animation& animation);
		void pause();
		void stop();

		bool loadFromFileJSON(const string& _filename);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

		virtual Component* clone()
		{
			Animator* pAnimator = new Animator(*this);
			pAnimator->m_pSprite = nullptr;
			if (pAnimator->m_pAnimation)
				pAnimator->m_pAnimation = m_pAnimation->clone();
			/*
			if (pAnimator->m_pSprite)
				pAnimator->m_pSprite = m_pSprite->clone();
			if (pAnimator->m_pAnimation)
				pAnimator->m_pAnimation = m_pAnimation->clone();
			*/
			return pAnimator;
		}
	};

} // namespace crea

#endif
