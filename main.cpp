#include <iostream>
#include "main.h"
#include <string>
#include <conio.h>

#define string std::string
#define start "-start"
#define end "-end"
#define steps "-steps"
#define listName "-name"
#define endl std::endl

int main(int argc, char* argv[]) {
    if (argc < 9){
        ColorGen::showUsage();
        return 1;
    }

    int stepsc = 100;
    RGBSet_s* startc = new RGBSet_s{0, 0, 0};
    RGBSet_s* endc = new RGBSet_s{0, 0, 0};
    const char* listNamec = "colorIdForTick";
    string delimiter = ",";

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == start) {
            if (i + 1 < argc) {
                string s = argv[++i];
                if (s.find(delimiter) != string::npos) {
                    size_t pos = 0;
                    string token;
                    bool red = false, blue = false, green = false;
                    while ((pos = s.find(delimiter)) != string::npos) {
                        token = s.substr(0, pos);
                        bool canRun = 1;
                        if (!red && canRun) {startc->red = atoi(token.c_str());red = 1;canRun = 0;}
                        if (!green && canRun) {startc->green = atoi(token.c_str());green = 1;canRun = 0;}
                        if (!blue && canRun) {startc->blue = atoi(token.c_str());blue = 1;}
                        s.erase(0, pos + delimiter.length());
                    }
                    if (!blue) {startc->blue = atoi(s.c_str());blue = 1;}
                } else if (s.find("0x") != string::npos) {
                    sscanf_s(s.c_str(), "0x%02x%02x%02x", &startc->red, &startc->green, &startc->blue);
                } else {
                    sscanf_s(s.c_str(), "%02x%02x%02x", &startc->red, &startc->green, &startc->blue);
                }
            } else {
                ColorGen::showUsage();
                return 1;
            }
        } else if (arg == end) {
            if (i + 1 < argc) {
                string s = argv[++i];
                if (s.find(delimiter) != string::npos) {
                    size_t pos = 0;
                    string token;
                    bool red = false, blue = false, green = false;
                    while ((pos = s.find(delimiter)) != string::npos) {
                        token = s.substr(0, pos);
                        bool canRun = 1;
                        if (!red && canRun) {endc->red = atoi(token.c_str());red = 1;canRun = 0;}
                        if (!green && canRun) {endc->green = atoi(token.c_str());green = 1;canRun = 0;}
                        if (!blue && canRun) {endc->blue = atoi(token.c_str());blue = 1;}
                        s.erase(0, pos + delimiter.length());
                    }
                    if (!blue) {endc->blue = atoi(s.c_str());blue = 1;}
                } else if (s.find("0x") != string::npos) {
                    sscanf_s(s.c_str(), "0x%02x%02x%02x", &endc->red, &endc->green, &endc->blue);
                } else {
                    sscanf_s(s.c_str(), "%02x%02x%02x", &endc->red, &endc->green, &endc->blue);
                }
            } else {
                ColorGen::showUsage();
                return 1;
            }
        } else if (arg == steps) {
            if (i + 1 < argc) {
                string s = argv[++i];
                stepsc = atoi(s.c_str());
            } else {
                ColorGen::showUsage();
                return 1;
            }
        } else if (arg == listName) {
            listNamec = argv[++i];
        }
    }

    std::cout << "\tprivate static ArrayList<Integer> " << listNamec << " = new ArrayList<Integer>();\n\n\tstatic {\n";
    for (int i = 0; i <= stepsc; ++i) {
        float percent = (float)i / stepsc;
        char hex[16];
        RGBSet_s* interpolated = ColorGen::interpolate(startc, endc, percent);
        sprintf(hex, "0x%02X%02X%02X", interpolated->red, interpolated->green, interpolated->blue);
        std::cout << "\t\t" << listNamec << ".add(" << hex << ");\n";
    }
    std::cout << "\t}";
    std::cout << "Press any key to continue..." << endl;
    _getch();
    return 0;
}

void ColorGen::showUsage() {
    std::cerr << "Options:\n\t-start Color code for start color, (0xFF00AA, FF11AA, 255,14,60)\n\t-end Color code for end color, (0xFF00AA, FF11AA, 255,14,60)\n\t-steps amount of steps to take to transition from start to end\n\t-name name of the arraylist" << endl;
    std::cout << "Press any key to continue..." << endl;
    _getch();
    return;
}

unsigned long ColorGen::createRGB(int r, int g, int b) {
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
}

RGBSet_s* ColorGen::interpolate(RGBSet_s* startingColor, RGBSet_s* endColor, float percent) {

    int   r1 = startingColor->red;
    int   r2 = endColor->red;
    int   g1 = startingColor->green;
    int   g2 = endColor->green;
    int   b1 = startingColor->blue;
    int   b2 = endColor->blue;

    int   r3 = (int) ((r2 - r1) * percent + r1);
    int   g3 = (int) ((g2 - g1) * percent + g1);
    int   b3 = (int) ((b2 - b1) * percent + b1);

    return new RGBSet_s{r3, g3, b3};
}
