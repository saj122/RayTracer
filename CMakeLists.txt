cmake_minimum_required(VERSION 3.16.0)

project(RayTracer)

set(INC
    core
    material
    math
)

set(SRC
    main.cpp
    material/Lambertian.cpp
    math/Ray.cpp
    math/Vec3.cpp
)

include_directories(${INC})

add_executable(RayTracer ${SRC})