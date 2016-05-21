// Copyright 2016 Dolotov Evgeniy

#include <gtest/gtest.h>
#include "../include/hello_world.h"
TEST(ML, Can_ML) {
    EXPECT_EQ(10, sum(5,5));
}
