#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "Texture.hpp"
#include "stb_image.h"
#include "Vec3.hpp"

#include <iostream>

class ImageTexture : public Texture
{
    public:
        ImageTexture()
            : _data(nullptr), _width(0), _height(0), _bytes_per_scanline(0) {}

        ImageTexture(const char* filename) 
        {
            auto components_per_pixel = BYTES_PER_PIXEL;

            _data = stbi_load(filename, &_width, &_height, &components_per_pixel, components_per_pixel);

            if (!_data) 
            {
                std::cerr << "ERROR: Could not load texture image file -'" << filename << "'.\n";
                _width = _height = 0;
            }

            _bytes_per_scanline = BYTES_PER_PIXEL * _width;
        }

        ~ImageTexture() 
        {
            stbi_image_free(_data);
        }

        virtual Vec3 value(double u, double v, const Vec3& p) const override 
        {
            if (_data == nullptr)
                return Vec3(0, 1, 1);

            u = clamp(u, 0.0, 1.0);
            v = 1.0 - clamp(v, 0.0, 1.0);  

            auto i = static_cast<int>(u * _width);
            auto j = static_cast<int>(v * _height);

            if (i >= _width)  i = _width - 1;
            if (j >= _height) j = _height - 1;

            const auto color_scale = 1.0 / 255.0;
            auto pixel = _data + j * _bytes_per_scanline + i * BYTES_PER_PIXEL;

            return Vec3(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
        }

    private:
        static constexpr int BYTES_PER_PIXEL = 3;
        unsigned char* _data;
        int _width, _height;
        int _bytes_per_scanline;
};

#endif