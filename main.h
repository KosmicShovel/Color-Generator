#ifndef ColorGen_MAIN_H
#define ColorGen_MAIN_H

typedef struct RGBSet_s {
public:
    int red;
    int green;
    int blue;
};

class ColorGen {
    public:
        static RGBSet_s* interpolate(RGBSet_s* startingColor, RGBSet_s* endColor, float percent);
        static void showUsage();
};

#endif