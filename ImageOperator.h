#pragma once
#include <stdlib.h>
#include <stdio.h>
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
    int channels;
    int width;
    int height;
    size_t size;
    uint8_t *data;
    char *name;
    enum allocation_type allocation_;
} Image;

int imageExists(const char *fname);
int imageLoad(Image *img, char *path);
char *getFnameFromPath(char *path);
void imageCreate(Image *img, int width, int height, int channels, bool zeroed);
void imageSave(const Image *img);
void imageFree(Image *img);
void image2Grey(const Image *img, Image *gray);