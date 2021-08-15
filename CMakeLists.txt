cmake_minimum_required(VERSION 3.16.0)

project(RayTracer)

set(INC
    core/HitRecord.hpp
    core/Hittable.hpp
    core/Material.hpp
    core/Utilities.hpp
    material/Lambertian.hpp
    material/Metal.hpp
    material/Dielectric.hpp
    math/Ray.hpp
    math/Vec3.hpp
    shapes/Sphere.hpp
)

set(SRC
    main.cpp
    material/Lambertian.cpp
    material/Metal.cpp
    material/Dielectric.cpp
    math/Ray.cpp
    math/Vec3.cpp
    shapes/Sphere.cpp
)

set(INC_DIRS
    core
    material
    math
    shapes
)

include_directories(${INC_DIRS})

add_executable(RayTracer ${SRC} ${INC})