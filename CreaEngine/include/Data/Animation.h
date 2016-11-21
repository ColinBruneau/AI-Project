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

#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#include <vector>

namespace crea
{
	class IntRect;

	class CREAENGINE_API Animation
	{
	public:
		Animation();

		void addFrame(IntRect rect);
		void setSpriteSheet(ITexture& texture);

		inline ITexture* getSpriteSheet()		{ return m_texture; }
		inline size_t getSize()					{ return m_frames.size(); }
		inline IntRect& getFrame(std::size_t n) { return m_frames[n]; }
		inline string getName()					{ return m_szName; }
		inline Time& getDuration()				{ return m_duration; }
		inline bool getLooping()				{ return m_bLooping; }
		 
		bool loadFromFileJSON(string _filename);

	private:
		string m_szName;
		vector<IntRect> m_frames;
		ITexture* m_texture;
		Time m_duration;
		bool m_bLooping;
	};

} // namespace crea

#endif // ANIMATION_INCLUDE