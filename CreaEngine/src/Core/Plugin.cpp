#include "stdafx.h"

#include "Core\Plugin.h"

namespace crea
{
	/*
	template <class T>
	inline Plugin<T>::Plugin() :
	m_Library(NULL)
	{

	}

	template <class T>
	inline Plugin<T>::~Plugin()
	{
		if (m_Library)
			FreeLibrary(m_Library);
	}
	template <class T>
	inline T* Plugin<T>::Load(const std::string& Filename)
	{
		// Chargement de la bibliothèque dynamique
		m_Library = LoadLibrary(Filename.c_str());
		assert(m_Library); // Impossible de charger la bibliothèque dynamique

		// Récupération de la fonction
		PtrFunc Function = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "StartPlugin"));
		assert(Function); // Impossible de trouver la fonction 'StartPlugin'

		return Function();
	}
	*/
} // namespace crea