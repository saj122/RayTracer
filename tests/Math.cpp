#include "gtest/gtest.h"
#include "Vec3.hpp"

TEST(Math, vec3Dot)
{
    Vec3 a(1.0,1.0,1.0);
    Vec3 b(1.0,1.0,1.0);
    EXPECT_EQ (dot(a,b),  3.0);
}