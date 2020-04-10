#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


enum allocation_type
{
    NO_ALLOCATION,
    SELF_ALLOCATED,
    STB_ALLOCATED
};

typedef struct
{
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation_;
} Image;

int imageLoad(Image *img, const char *fname);
void imageCreate(Image *img, int width, int height, int channels, bool zeroed);
void imageSave(const Image *img, const char *fname);
void imageFree(Image *img);
void image2Grey(const Image *orig, Image *gray);
void image2Sepia(const Image *orig, Image *sepia);
int cfileexists(const char *fname);
    /*
#pragma once 

#include <stdint.h>
#include <stdlib.h>

#define FILETYPE_PNG 0
#define FILETYPE_JPG 1
#define FILETYPE_BMP 2
#define FILETYPE_GIF 3

enum allocationType
{
    NO_ALLOCATION,
    SELF_ALLOCATED,
    STB_ALLOCATED
};

enum fileType
{
    NO_TYPE,
    PNG_TYPE, 
    JPG_TYPE,
    BMP_TYPE,
    GIF_TYPE
};

typedef struct
{
    char *name;
    enum fileType fileType;
    int width;
    int height;
    int channels;
    size_t size;
    unsigned char * data;
    enum allocationType allocation_;
}
Image;

void imageLoad(Image *img, char *path);
void imageSave(const Image *img, char *path);
void imageFree(Image *img);
void image2Grey(Image *imgGrey, const Image *img);
*/