/** REQUIRIMENTS
 * 10 imagenes en grises y 10 en color
 * - sumar 1 imagen de color con una en grises preseleccionada y guardar el resultado
 * - Producto cartesiano de las 10 imagenes grises
 * - Producto cartesiano de las 20 imagenes (color y grises)
 * - restar a 1 imagen de color una imagen gris
 */
#include "ImageOperator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALIDSIZE 128

void getImageWValidation(Image *img);

int main()
{
    Image img1, img2, imgSepia, imgGrey;

    getImageWValidation(&img1);
    //getImageWValidation(img2);

    // Operates images
    image2Grey(&img1, &imgGrey);

    // Save resultant images
    imageSave(&imgGrey);

    // Release memory
    imageFree(&img1);
    imageFree(&imgGrey);

    char command[300] = ".\\";
    strcat(command, imgGrey.name);
    system(command);
}

void getImageWValidation(Image *img)
{
    while (1) // Whole validation for image input
    {
        char path[260];

        printf("ruta de imagen: ");
        scanf("%s", path);

        if (strlen(path) == 0)
            printf("ERROR: Ingresa una ruta \n");
        else if (strchr(path, '.') == NULL)
            printf("Incluye la externsion \n");
        else if (strstr(path, ".jpg") == NULL && strstr(path, ".png") == NULL && strstr(path, ".gif") == NULL && strstr(path, ".bmp") == NULL)
            printf("Externsion no valida. Solo jpg, png, gif, bmp \n");
        else if (!imageLoad(img, path))
            printf("el archivo \"%s\" no existe \n", path);
        else if (img->width != VALIDSIZE || img->height != VALIDSIZE)
            printf("el archivo \"%s\" debe medir %dpx x %dpx \n", path, VALIDSIZE, VALIDSIZE);
        else break;
    }
}