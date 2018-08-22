//
// Created by zhaojunhe on 2018/8/18.
//
#include "vermilion.hpp"

extern "C" void vglLoadDDS(const char* filename, vglImageData* image);

void vglLoadImage(const char *filename, vglImageData *image){
    vglLoadDDS(filename, image);
}

void vglUnloadImage(vglImageData* image){
    delete [] reinterpret_cast<uint8_t *>(image->mip[0].data);
}

GLuint vglLoadTexture(const char *filename, GLuint texture, vglImageData* image){

}