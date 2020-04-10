#include "ImageOperator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Image img, imgSepia, imgGrey;
    char pathImg[260];

    while (1)   //Whole validation for image input
    {
        printf("ruta de imagen: ");
        scanf("%s", pathImg);

        if (strlen(pathImg) == 0)
            printf("ERROR: Ingresa una ruta \n");
        else if (strchr(pathImg, '.') == NULL)
            printf("Incluye la externsion \n");
        else if (strstr(pathImg, ".jpg") == NULL && strstr(pathImg, ".png") == NULL && strstr(pathImg, ".gif") == NULL && strstr(pathImg, ".bmp") == NULL)
            printf("Externsion no valida. Solo jpg, png, gif, bmp \n");
        else if (!imageLoad(&img, pathImg))
            printf("el archivo %s no existe \n", pathImg);
        else break;
    }

    //imageLoad(&img, "resources\\pinkblue.gif");
    //ON_ERROR_EXIT(img.data == NULL, "Error in loading the image");

    // Convert the images to gray
    Image img_gray, img_shapes_gray;
    image2Grey(&img, &img_gray);

    // Convert the images to sepia
    Image img_sepia, img_shapes_sepia;
    image2Sepia(&img, &img_sepia);

    // Save images
    imageSave(&img_gray, "sky_gray.jpg");
    imageSave(&img_sepia, "sky_sepia.jpg");

    // Release memory
    imageFree(&img);
    imageFree(&img_gray);
    imageFree(&img_sepia);

    system(".\\sky_gray.jpg");
    system(".\\sky_sepia.jpg");
}
