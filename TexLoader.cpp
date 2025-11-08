#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include <cstdint>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <unordered_map>

#include <FreeImage.h>
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>


typedef GLuint MTLTexture;

class TextureLoader {
public:
    static void init();
    static MTLTexture createUncompressedTexture(const std::string& filePath, uint64_t fmt = 0);
    static void destroy();
};


//std::string GetBundleFilePath(const std::string& filename) ;

std::unordered_map<std::string, FIBITMAP*> fiTextureMap;
std::unordered_map<std::string, MTLTexture> mtlTextureMap;

void TextureLoader::init() {
    FreeImage_Initialise();
}
MTLTexture TextureLoader::createUncompressedTexture(const std::string &filePath, uint64_t fmt) {
    
    if(mtlTextureMap.find(filePath) != mtlTextureMap.end()) {
        return mtlTextureMap[filePath];
    }
    
    MTLTexture texture = 0;
    
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP* image = 0;

    unsigned int width(0), height(0), bpp(0);

    auto rpath = filePath; //GetBundleFilePath(filePath);

        fif = FreeImage_GetFileType(filePath.c_str(), 0);
        if (fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(filePath.c_str());
    
        if (fif == FIF_UNKNOWN) {
            fif = FIF_TARGA;
            return {};
        }

        if (FreeImage_FIFSupportsReading(fif))
            image = FreeImage_Load(fif, rpath.c_str());
    
        if (!image) {
            return {};
        }
    
            FreeImage_FlipVertical(image);


        bpp = FreeImage_GetBPP(image);
        width = FreeImage_GetWidth(image);
        height = FreeImage_GetHeight(image);
    
        if ((bpp == 0) || (width == 0) || (height == 0)) {
            FreeImage_Unload(image);
            return {};
        }

    
    uint64_t format = 0;


        switch (bpp)
        {
        case 4:
        case 8:
        case 16:
        case 24:
        {
            bpp = 32;
            FIBITMAP* newImage = FreeImage_ConvertTo32Bits(image);
            FreeImage_Unload(image);
            image = newImage;
        }
        case 32:
        //    format = MTL::PixelFormatBGRA8Unorm;
         //   if (fif == FIF_DDS)
         //       format = MTL::PixelFormatBGRA8Unorm;
            break;
        case 128:
            {
       //         format = MTL::PixelFormatRGBA32Float;
            }
            break;
        default:
        {
       //     format = MTL::PixelFormatRGBA8Unorm;
        }
        break;
        }

    fiTextureMap[filePath] = image;
    
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    mtlTextureMap[filePath] = texture;

    return texture;
}

void TextureLoader::destroy() {
    FreeImage_DeInitialise();
}


void TexWrap_init() {
    puts("make sure u init the free image");
    TextureLoader::init();
}

unsigned TexWrap_createUncompressedTexture(const std::string &filePath) {
    return TextureLoader::createUncompressedTexture(filePath, 0);
} 