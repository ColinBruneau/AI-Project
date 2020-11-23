-inclure glad.h

- ajouter glad.c au projet

- Appeller cette fonction dans l'init:
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGL())
		{
			std::cout << "Can't load OpenGL function pointers with GLAD" << endl;
			return;
		}

- mais les fonctions glBegin, etc. ne sont plus reconnues?