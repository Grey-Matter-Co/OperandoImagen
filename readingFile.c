#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImageOperator.h"

int main()
{
	// inicializacion de parametros
	Image img1, img2, imgResult;
	char path[260];	// 260 porque es la ruta maxima en windows

	//while (1)	// Ciclo para validar si el programa pudo cargar la imagen
	//{
		while (1)	// Ciclo para validar si la ruta del archivo es valida
		{
			printf("ruta del archivo (relativa | absoluta): ");
			gets(path);

			if (strlen(path) == 0)	// verificar si contiene al menos un parametro
				printf("ERROR: Ingresa una ruta \n");	
			else if (strrchr(path, '.') == 0 || (strrchr(path, '.') - path) == 0)	// verificar si contiene un punto y es el de la extension
				printf("ERROR: Incluye la extension \n");
			else
				break;
		}
		
		// lectura de la imagen
		imageLoad(&img1, path);

		// comprobar si la lectura es exitosa
		/*
		if (img1->data == NULL) 
			printf("ERROR: No pudo ser cargada la imagen. Probablemente no exista la imagen o es un formato incorrecto\n solo .jpg, .png, .bmp, .gif");
		else if (img1->width != 32 && img1->width != 64 && img1->width != 128 && img1->height != 32 && img1->height != 64 && img1->height != 128)
			printf("ERROR: Las dimensiones deben ser 32x32px, 64x64px o 128x128px \n");
		else
			break;
		*/
	//}

	// comprobacion de imagen
	//printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", img1->width, img1->height, img1->channels);
		image2Grey(&imgResult, &img1);
		/*
	imgResult->name = img1->name;
	strcat(imgResult->name, "GreyScale");
	*/

		imageSave(&imgResult, "test");

		imageFree(&imgResult);
		imageFree(&img1);

		return 0;
}