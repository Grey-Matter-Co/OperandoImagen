#include "ImageOperator.h"
#include <math.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int imageExists(const char *fname)
{
    FILE *img;
    if (img = fopen(fname, "r"))    // "r" command to /r/ead image
    {
        fclose(img);
        return 1;
    }
    return 0;
}

int imageLoad(Image *img, char *path)
{
    if (!imageExists(path))
        return 0;   // No exists image
    else if ((img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0)) != NULL)
    {
        img->name = malloc(100 * sizeof(char));
        strcpy(img->name, getFnameFromPath(path));
        img->size = img->width * img->height * img->channels;
        img->allocation_ = STB_ALLOCATED;
    }
    return 1;       // Exists and loaded image
}

char *getFnameFromPath(char *path)
{
    char *dot = strrchr(path, '.');
    *dot = '\0';

    if (*path == '.' || strchr(path, '/') || strchr(path, '\\')) // Is relative or absolute path
        return strrchr(path, '/') != NULL
                   ? strrchr(path, '/') + 1
                   : strrchr(path, '\\') + 1;
    else // img is on lvl from program
        return path;
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

void image2Grey(const Image *img, Image *gray)
{
    //ON_ERROR_EXIT(!(img->allocation_ != NO_ALLOCATION && img->channels >= 3), "The input image must have at least 3 channels.");
    int channels = img->channels == 4 ? 2 : 1;
    imageCreate(gray, img->width, img->height, channels, false);
    //ON_ERROR_EXIT(gray->data == NULL, "Error in creating the image");

    strcat(strcpy(gray->name, img->name), "_GreyScale");

    for (unsigned char *p = img->data, *pg = gray->data; p != img->data + img->size; p += img->channels, pg += gray->channels)
    {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        if (img->channels == 4)
            *(pg + 1) = *(p + 3);
    }
}
