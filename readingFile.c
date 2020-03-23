#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// inclir librerias para trabajar con imagenes
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void main()
{
	// inicializacion de parametros
	int width, height, channels;	
	char path[260];	// 260 porque es la ruta maxima en windows

	while (1)
	{
		while (1)
		{
			printf("ruta del archivo (relativa | absoluta): ");
			scanf("%s", &path);

			if (strlen(path) == 0)	// verificar si contiene al menos un parametro
				printf("ERROR: Ingresa una ruta \n");	
			else if (strrchr(path, '.') == 0 || (strrchr(path, '.') - path) == 0)	// verificar si contiene un punto y es el de la extension
				printf("ERROR: Incluye la extension \n");
			else
				break;
		}
		
		// lectura de la imagen
		unsigned char *img = stbi_load(path, &width, &height, &channels, 0);

		// comprobar si la lectura es exitosa
		if (img == NULL) 
			printf("ERROR: No pudo ser cargada la imagen. Probablemente no exista la imagen o es un formato incorrecto\n solo .jpg, .png, .bmp, .gif");	
		else if (width != 32 && width != 64 && width != 128 && height != 32 && height != 64 && height != 128)
			printf("ERROR: Las dimensiones deben ser 32x32px, 64x64px o 128x128px \n");
		else
			break;
		
	}

	// comprobacion de imagen
	printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
}