//
// Created by 2matt on 11/18/2020.
//

#ifndef ColorGen_MAIN_H
#define ColorGen_MAIN_H

typedef struct RGBSet_s {
public:
    int red;
    int green;
    int blue;
} RGBSet_def;

class ColorGen {
    public:
        static unsigned long createRGB(int r, int g, int b);
        static RGBSet_s* interpolate(RGBSet_s* startingColor, RGBSet_s* endColor, float percent);
        static void showUsage();
};

#endif