#include "Camera.hpp"
#include "Vec3.hpp"
#include "HittableList.hpp"
#include "HitRecord.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "Utilities.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dielectric.hpp"
#include "ThreadPool.hpp"
#include "BVH.hpp"

#include <iostream>
#include <memory>
#include <thread>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

uint8_t* pixels = new uint8_t[1280 * 720 * 3];

Vec3 ray_color(const Ray& r, const Vec3& background, const Hittable& world, int depth)
{
    HitRecord rec;
    if (depth <= 0)
        return Vec3(0,0,0);

    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    Ray scattered;
    Vec3 attenuation;
    Vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

void render(int n, Camera cam, Vec3 background, HittableList world, int max_depth, int image_width, int image_height, int samples_per_pixel)
{
    int i = n % image_width;
    int j = n / image_width;
    Vec3 pixel_color(0,0,0);
    for (int s = 0; s < samples_per_pixel; ++s) 
    {
        auto u = (i + random_double()) / (image_width-1);
        auto v = (j + random_double()) / (image_height-1);
        Ray r = cam.getRay(u, 1.0 - v);
        pixel_color += ray_color(r, background, world, max_depth);
    }
    
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    pixels[n*3] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    pixels[n*3+1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    pixels[n*3+2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
}

HittableList random_scene()
{
    HittableList world;
    
    auto ground_material = std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0,-1000,0), 1000, ground_material));

    for (int a = -2; a < 2; a++) 
    {
        for (int b = -2; b < 2; b++) 
        {
            auto choose_mat = random_double();
            Vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) 
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) 
                {
                    auto albedo = Vec3::random() * Vec3::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } 
                else if (choose_mat < 0.95) 
                {
                    auto albedo = Vec3::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } 
                else 
                {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

    return HittableList(std::make_shared<BVHNode>(world, 0.0, 1.0));
}

int main(int argc, char** args)
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    const int max_depth = 50;

    auto world = random_scene();

    Vec3 lookfrom(13,2,3);
    Vec3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Vec3 background = Vec3(0.70, 0.80, 1.00);

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    ThreadPool tp;

    for (int i = 0; i < image_height*image_width; ++i) 
    {
        tp.submit(std::bind(&render,i, cam, background, world, max_depth, image_width, image_height, samples_per_pixel));
    }
    tp.waitFinished();

    stbi_write_jpg("stbjpg3.jpg", image_width, image_height, 3, pixels, 100);
    delete[] pixels;
    std::cerr << "\nDone.\n";
    return 0;
}