#ifndef ColorGen_MAIN_H
#define ColorGen_MAIN_H

struct RGBSet_s {
public:
    int red;
    int green;
    int blue;
};

class ColorGen {
    public:
        static RGBSet_s* interpolate(RGBSet_s* startingColor, RGBSet_s* endColor, float percent);
        static void showUsage();
        static void outputGeneration(std::string langc, RGBSet_s* starColor, RGBSet_s* endColor, int stepsc, std::string lName);
};

#endif