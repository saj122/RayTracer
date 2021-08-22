cmake_minimum_required(VERSION 3.16.0)

project(RayTracer)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(INC
    core/HitRecord.hpp
    core/Hittable.hpp
    core/HittableList.hpp
    core/Material.hpp
    core/Utilities.hpp
    core/Camera.hpp
    core/ThreadPool.hpp
    core/ThreadsafeQueue.hpp
    core/Texture.hpp
    core/AABB.hpp
    core/BVH.hpp
    core/Translate.hpp
    core/Rotate.hpp
    core/ConstantMedium.hpp
    shapes/Box.hpp
    shapes/AARect.hpp
    textures/SolidColor.hpp
    textures/ImageTexture.hpp
    material/Lambertian.hpp
    material/Metal.hpp
    material/Dielectric.hpp
    material/DiffuseLight.hpp
    material/Isotropic.hpp
    math/Ray.hpp
    math/Vec3.hpp
    shapes/Sphere.hpp
    shapes/MovingSphere.hpp
    external/stb/stb_image.h
    external/stb/stb_image_write.h
)

set(SRC
    main.cpp
    material/Lambertian.cpp
    material/Metal.cpp
    material/Dielectric.cpp
    material/DiffuseLight.cpp
    material/Isotropic.cpp
    math/Ray.cpp
    math/Vec3.cpp
    shapes/Sphere.cpp
    shapes/MovingSphere.cpp
    shapes/Box.cpp
    shapes/AARect.cpp
    core/Camera.cpp
    core/HittableList.cpp
    core/BVH.cpp
    core/Translate.cpp
    core/Rotate.cpp
    core/ConstantMedium.cpp
)

set(INC_DIRS
    core
    material
    math
    shapes
    external/stb
    textures
)

include_directories(${INC_DIRS})
add_executable(RayTracer ${SRC} ${INC})
target_link_libraries(RayTracer Threads::Threads)

