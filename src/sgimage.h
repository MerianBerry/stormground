#pragma once
#include "sg.h"

void sgSetImagePixel (SGimage *img, int x, int y, SGcolor c);

SGcolor sgGetImagePixel (SGimage *img, int x, int y);

SGimage sgGenImage (int width, int height, int channels);

int sgGLImageTextureType (SGimage *img);

void sgGenImageTexture (SGimage *img, int mip, int wrap_s, int wrap_t,
                         int min_filter, int max_filter);

void sgBindImageTexture (SGimage *img);

void sgUpdateImageTexture (SGimage *img, int mip, int x, int y);

void sgClearImage (SGimage *img);

void sgFreeImage (SGimage *img);

void sgFreeImageTexture (SGimage *img);

int sgGenTextures2D (int min_filter, int mag_filter, int wrap_s, int wrap_t,
                      int format, int w, int h, int n, SGtexture *texturev);

void sgBindTexture (SGtexture tex, int rw);

void sgUnbindTexture (void);

void sgRegenerateTexture(SGtexture *tex);

void sgFreeTextures(SGtexture *texv, int texc);
