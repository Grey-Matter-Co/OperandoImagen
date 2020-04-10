#include "ImageOperator.h"
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

static inline bool str_ends_in(const char *str, const char *ends)
{
    char *pos = strrchr(str, '.');
    return !strcmp(pos, ends);
}

int imageLoad(Image *img, const char *fname)
{
    if (!cfileexists(fname))
        return 0;   //Image no exists
    
    else if ((img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0)) != NULL)
    {
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
        img->width = width;
        img->height = height;
        img->size = size;
        img->channels = channels;
        img->allocation_ = SELF_ALLOCATED;
    }
}

void imageSave(const Image *img, const char *fname)
{
    if (cfileexists(fname))
        printf("El Archivo ya existe \n");
    // Check if the file name ends in one of the .jpg/.JPG/.jpeg/.JPEG or .png/.PNG
    if (str_ends_in(fname, ".jpg") || str_ends_in(fname, ".JPG") || str_ends_in(fname, ".jpeg") || str_ends_in(fname, ".JPEG"))
        stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
    else if (str_ends_in(fname, ".png") || str_ends_in(fname, ".PNG"))
        stbi_write_png(fname, img->width, img->height, img->channels, img->data, img->width * img->channels);
    else
        exit(0);
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
    FILE *file;
    if (file = fopen(fname, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
/*
#include "ImageOperator.h"
#include <math.h>
#include <string.h>

// inclir librerias para trabajar con imagenes, estas declaraciones son obligaroeias (segun el desarrollador de las librerias)
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void imageLoad(Image *img, char *path)
{
    img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    img->size = img->width * img->height * img->channels;
    img->allocation_ = STB_ALLOCATED;

    const char *dot = strrchr(path, '.');
    const char *startFname = strrchr(path, '/') != NULL
                            ? strrchr(path, '/')+1
                            : strrchr(path, '\\') != NULL
                                ? strrchr(path, '\\')+1
                                : path;
    char *fname = calloc(sizeof(char)*(dot-startFname), 1);

    for (int i = 0; i < (dot-startFname); i++)
        *(fname+i) =  *(startFname+i);
        
    img->name = fname;

    img->fileType = strcmp(dot + 1, "png") == 0
                        ? PNG_TYPE
                        : strcmp(dot + 1, "jpg") == 0
                            ? JPG_TYPE
                            : strcmp(dot + 1, "bmp") == 0
                                ? BMP_TYPE
                                : GIF_TYPE;

    printf("%s \n", dot + 1);
    printf("%s \n", img->name);

}

void imageSave(const Image *img, char *path)
{
    char fname[200];
    if (path == NULL)
        strcpy(fname, img->name);
    else
        strcpy(fname, path);

    switch (img->fileType)
    {
        case PNG_TYPE:
            strcat(fname, ".png");
            stbi_write_png(fname, img->width, img->height, img->channels, img, img->width * img->channels);
            break;
        case JPG_TYPE:
            strcat(fname, ".jpg");
            stbi_write_jpg(fname, img->width, img->height, img->channels, img, 100);
            break;
        case BMP_TYPE:
            strcat(fname, ".bmp");
            stbi_write_bmp(fname, img->width, img->height, img->channels, img);
            break;
        case GIF_TYPE:
            strcat(fname, ".gif");
            stbi_write_png(fname, img->width, img->height, img->channels, img, img->width * img->channels);
            break;
        case NO_TYPE:
            printf("%s \n", fname);
            printf("%d \n", strlen(fname));
            printf("%d \n", sizeof(fname) / sizeof(char));
            strcat(fname, ".bmp");
            stbi_write_bmp(fname, img->width, img->height, img->channels, img);
            break;
    }
}

void imageCreate(Image *img, int width, int height, int channels)
{

    img->data = calloc(width * height, 1);

    if (img->data != NULL)
    {
        img->allocation_ = SELF_ALLOCATED;
        img->channels = channels;
        img->fileType = NO_TYPE;
        img->height = height;
        img->size = width * height;
        img->width = width;
    }
    
}

void imageFree(Image *img)
{
    if (img->data != NULL && img->allocation_ != NO_ALLOCATION)
    {
        if (img->allocation_ == STB_ALLOCATED)
            stbi_imageFree(img->data);
        else
            free(img->data);
        
        free(img->name);
    }
    
}

void image2Grey(Image *imgG, const Image *img)
{
    int channels = img->channels == 4 ? 2 : 1;
    imageCreate(imgG, img->width, img->height, channels);
    imgG->name = img->name;
    strcat(imgG->name, "GreyScale");
    for (unsigned char *p = img->data, *pG = imgG->data; p < (img->data + img->size); p += img->channels, pG += imgG->channels)
    {
        printf("%x -> %x", p, img->data + img->size);
        *pG = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
        printf(": pG = %d \n", *pG);
        if (img->channels == 4)
            *(pG + 1) = *(p + 3);
    }
}
*/