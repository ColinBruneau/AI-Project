/***************************************************/
/* Nom:	Plugin.h
/* Description: Plugin
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IPlugin_H
#define _IPlugin_H
#include <windows.h>

namespace crea
{

	template <class T>
	class Plugin
	{
	public:

		//----------------------------------------------------------
		// Constructeur par d�faut
		//----------------------------------------------------------
		inline Plugin() :
			m_Library(NULL)
		{

		}

		//----------------------------------------------------------
		// Destructeur
		//----------------------------------------------------------
		inline ~Plugin()
		{
			if (m_Library)
				FreeLibrary(m_Library);
		}

		//----------------------------------------------------------
		// Charge la DLL et r�cup�re un pointeur sur l'objet
		//----------------------------------------------------------
		T* Load(const std::string& Filename)
		{
			// Chargement de la biblioth�que dynamique
			m_Library = LoadLibrary(Filename.c_str());
			assert(m_Library); // Impossible de charger la biblioth�que dynamique

			// R�cup�ration de la fonction
			PtrFunc Function = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "StartPlugin"));
			assert(Function); // Impossible de trouver la fonction 'StartPlugin'

			return Function();
		}

	private:

		//----------------------------------------------------------
		// Types
		//----------------------------------------------------------
		typedef T* (*PtrFunc)();

		//----------------------------------------------------------
		// Donn�es membres
		//----------------------------------------------------------
		HMODULE m_Library; // Handle de la DLL
	};

} // namespace crea

#endif // _IPlugin_H