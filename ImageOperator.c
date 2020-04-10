#include "ImageOperator.h"
#include <math.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int imageLoad(Image *img, char *path)
{
    if (!cfileexists(path))
        return 0;   //Image no exists

    else if ((img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0)) != NULL)
    {
        img->name = malloc(100 * sizeof(char));
        strcpy(img->name, getNameFromPath(path));
        img->size = img->width * img->height * img->channels;
        img->allocation_ = STB_ALLOCATED;
    }

    return 1;
}

void imageCreate(Image *img, int width, int height, int channels, bool zeroed)
{
    size_t size = width * height * channels;
    if (zeroed)
        img->data = calloc(size, 1);
    else
        img->data = malloc(size);

    if (img->data != NULL)
    {
        img->name = malloc(100 * sizeof(char));
        img->width = width;
        img->height = height;
        img->size = size;
        img->channels = channels;
        img->allocation_ = SELF_ALLOCATED;
    }
}

void imageSave(const Image *img)
{
    stbi_write_bmp(strcat(img->name, ".bmp"), img->width, img->height, img->channels, img->data);
}

void imageFree(Image *img)
{
    if (img->allocation_ != NO_ALLOCATION && img->data != NULL)
    {
        if (img->allocation_ == STB_ALLOCATED)
            stbi_image_free(img->data);
        else
            free(img->data);
        img->data = NULL;
        img->width = 0;
        img->height = 0;
        img->size = 0;
        img->allocation_ = NO_ALLOCATION;
    }
}

void image2Grey(const Image *orig, Image *gray)
{
    //ON_ERROR_EXIT(!(orig->allocation_ != NO_ALLOCATION && orig->channels >= 3), "The input image must have at least 3 channels.");
    int channels = orig->channels == 4 ? 2 : 1;
    imageCreate(gray, orig->width, orig->height, channels, false);
    //ON_ERROR_EXIT(gray->data == NULL, "Error in creating the image");

    strcat(strcpy(gray->name, orig->name), "_GreyScale");

    for (unsigned char *p = orig->data, *pg = gray->data; p != orig->data + orig->size; p += orig->channels, pg += gray->channels)
    {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        if (orig->channels == 4)
            *(pg + 1) = *(p + 3);
    }
}

void image2Sepia(const Image *orig, Image *sepia)
{
    //ON_ERROR_EXIT(!(orig->allocation_ != NO_ALLOCATION && orig->channels >= 3), "The input image must have at least 3 channels.");
    imageCreate(sepia, orig->width, orig->height, orig->channels, false);
    //ON_ERROR_EXIT(sepia->data == NULL, "Error in creating the image");

    // Sepia filter coefficients from https://stackoverflow.com/questions/1061093/how-is-a-sepia-tone-created
    for (unsigned char *p = orig->data, *pg = sepia->data; p != orig->data + orig->size; p += orig->channels, pg += sepia->channels)
    {
        *pg = (uint8_t)fmin(0.393 * *p + 0.769 * *(p + 1) + 0.189 * *(p + 2), 255.0);       // red
        *(pg + 1) = (uint8_t)fmin(0.349 * *p + 0.686 * *(p + 1) + 0.168 * *(p + 2), 255.0); // green
        *(pg + 2) = (uint8_t)fmin(0.272 * *p + 0.534 * *(p + 1) + 0.131 * *(p + 2), 255.0); // blue
        if (orig->channels == 4)
            *(pg + 3) = *(p + 3);
    }
}

int cfileexists(const char *fname)
{
    /* try to open file to read */
    FILE *img;
    if (img = fopen(fname, "r"))
    {
        fclose(img);
        return 1;
    }
    return 0;
}

char *getNameFromPath(char *path)
{
    char *dot = strrchr(path, '.');
    *dot = '\0';

    if ( *path == '.' || strchr(path, '/') ||  strchr(path,'\\') ) // Is relative or absolute path
        return strrchr(path, '/') != NULL
                    ? strrchr(path, '/') + 1
                    : strrchr(path, '\\') +1;
    else    // img is on lvl from program
        return path;
}