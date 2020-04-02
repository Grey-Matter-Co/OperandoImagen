#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// inclir librerias para trabajar con imagenes, estas declaraciones son obligaroeias (segun el desarrollador de las librerias)
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void main()
{
	// inicializacion de parametros
	int width, height, channels;	
	char path[260];	// 260 porque es la ruta maxima en windows
	unsigned char *img;

	while (1)	// Ciclo para validar si el programa pudo cargar la imagen
	{
		while (1)	// Ciclo para validar si la ruta del archivo es valida
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
		img = stbi_load(path, &width, &height, &channels, 0);

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

	// Convert the input image to gray
	size_t img_size = width * height * channels;
 	int gray_channels = channels == 4 ? 2 : 1;
	size_t gray_img_size = width * height * gray_channels;

	unsigned char *gray_img = malloc(gray_img_size);
	if(gray_img == NULL) 
	{
		printf("Unable to allocate memory for the gray image.\n");
		exit(1);
	}

	for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) 
	{
		printf("(%d, %d, %d, %d), ", *p, *(p + 1), *(p + 2), *(p + 3));
		if ((p-img)% width == 0 )
			printf("\n");
		*pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
		if(channels == 4)
			*(pg + 1) = *(p + 3);
	}

	stbi_write_jpg("test.jpg", width, height, gray_channels, gray_img, 100);
}