#include <iostream>
#include "main.h"
#include <string>
#include <conio.h>
#include <algorithm>
#include <cctype>

#define string std::string
#define start "-start"
#define endM "-end"
#define steps "-steps"
#define listName "-name"
#define language "-lang"

int main(int argc, char* argv[]) {
    if (argc < 11){
        ColorGen::showUsage();
        return 1;
    }

    int stepsc = 100;
    RGBSet_s* startc = new RGBSet_s{0, 0, 0};
    RGBSet_s* endc = new RGBSet_s{0, 0, 0};
    const char* listNamec = "colorIdForTick";
    string langc = "java";
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
                } else if (s.find("#") != string::npos) {
                    sscanf_s(s.c_str(), "#%02x%02x%02x", &startc->red, &startc->green, &startc->blue);
                } else {
                    sscanf_s(s.c_str(), "%02x%02x%02x", &startc->red, &startc->green, &startc->blue);
                }
            } else {
                ColorGen::showUsage();
                return 1;
            }
        } else if (arg == endM) {
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
                } else if (s.find("#") != string::npos) {
                    sscanf_s(s.c_str(), "#%02x%02x%02x", &endc->red, &endc->green, &endc->blue);
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
        } else if (arg == language) {
            string s = argv[++i];
            if (s.c_str()) {
                std::transform(s.begin(), s.end(), s.begin(), [](char c){return static_cast<char>(std::tolower(c));});

                if ((s.find("java") != string::npos) || (s.find("c#") != string::npos) ||
                    (s.find("cs") != string::npos) || (s.find("cpp") != string::npos) ||
                    (s.find("c++") != string::npos) || (s.find("py") != string::npos) ||
                    (s.find("python") != string::npos)) {
                    langc = s;
                } else {
                    std::cerr << "Can't detect language! - " << s << std::endl;
                    ColorGen::showUsage();
                    return 1;
                }
            }
        }
    }


    ColorGen::outputGeneration(langc, startc, endc, stepsc, listNamec);

    std::cout << "Press any key to continue..." << std::endl;
    _getch();
    return 0;
}

void ColorGen::showUsage() {
    std::cerr << "Options:\n\t-start Color code for start color, (#00FF00, 0xFF00AA, FF11AA, 255,14,60)\n\t-end Color code for end color, (#00FF00, 0xFF00AA, FF11AA, 255,14,60)\n\t-steps amount of steps to take to transition from start to end\n\t-name name of the arraylist\n\t-lang Language to output as (Java, C#, C++, Python)" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch();
    return;
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

void CStyleOutputGeneration(string braceBegin, string braceEnd, string wrapperBegin, string wrapperEnd, bool hasSemiColon, RGBSet_s* startColor, RGBSet_s* endColor, int stepsc, string lName, int tabAmount) {
    std::cout << wrapperBegin << lName << wrapperEnd << braceBegin << std::endl;
    string tabs = "";
    for (int i = 0; i < tabAmount; ++i)
        tabs += "\t";
    string tabse = "";
    for (int i = 0; i < tabAmount - 1; ++i)
        tabse += "\t";
    char hex[16];
    sprintf_s(hex, "0x%02X%02X%02X", startColor->red, startColor->green, startColor->blue);
    std::cout << tabs << " " << hex;
    int lastI = 0;
    for (int i = 0; i <= stepsc; ++i) {
        float percent = (float)i / stepsc;
        char hexI[16];
        RGBSet_s* interpolated = ColorGen::interpolate(startColor, endColor, percent);
        sprintf_s(hexI, "0x%02X%02X%02X", interpolated->red, interpolated->green, interpolated->blue);
        std::cout << (i % 2 == 0 ? ", " : tabs + " ") << hexI << (i == stepsc ? "\n" : (i % 2 == 0 ? ",\n" : ""));
        lastI = i;
    }
    std::cout << (lastI % 2 == 1 ? "\n" : "") << tabse << braceEnd << (hasSemiColon ? ";" : "") << std::endl;
    return;
}

void ColorGen::outputGeneration(string langc, RGBSet_s* startColor, RGBSet_s* endColor, int stepsc, string lName) {
    if (langc.find("java") != string::npos) {
        std::cout << "\tprivate static ArrayList<Integer> " << lName << " = new ArrayList<Integer>();\n\n\tstatic {\n";
        for (int i = 0; i <= stepsc; ++i) {
            float percent = (float)i / stepsc;
            char hex[16];
            RGBSet_s* interpolated = ColorGen::interpolate(startColor, endColor, percent);
            sprintf_s(hex, "0x%02X%02X%02X", interpolated->red, interpolated->green, interpolated->blue);
            std::cout << "\t\t" << lName << ".add(" << hex << ");\n";
        }
        std::cout << "\t}\n";
        return;
    }

    if ((langc.find("cs") != string::npos) || (langc.find("c#") != string::npos)) {
        CStyleOutputGeneration("{", "}", "\t\tpublic static List<int> ", " = new List<int> ", 1, startColor, endColor, stepsc, lName, 3);
    }
    else
    if ((langc.find("cpp") != string::npos) || (langc.find("c++") != string::npos)) {
        CStyleOutputGeneration("{", "}", "\t\tstd::vector<int> ", " = std::vector<int>", 1, startColor, endColor, stepsc, lName, 3);
    }
    else
    if ((langc.find("py") != string::npos) || (langc.find("python") != string::npos)) {
        CStyleOutputGeneration("[", "]", "\t", " = ", 0, startColor, endColor, stepsc, lName, 2);
    }
}
