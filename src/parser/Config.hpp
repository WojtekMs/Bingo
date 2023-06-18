#pragma once 
#include <filesystem>
#include <string>

struct Point {
    int x;
    int y;

    std::string toString() const {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }
};

struct Config {
    Point boardUpperLeftCorner;
    Point boardUpperRightCorner;
    int linePixelWidth;
    int generatedNumbersFontSize;
    int generateBingosCount;
    std::filesystem::path generateBingosDirectory;    
    std::filesystem::path originalBingoBoardFile;    
    std::filesystem::path fontFile;    

    std::string toString() const {
        return "boardUpperLeft: " + boardUpperLeftCorner.toString() + "\n" \
               "boardUpperRight: " + boardUpperRightCorner.toString() + "\n" \
               "linePixelWidth: " + std::to_string(linePixelWidth) + "\n" \
               "generatedNumbersFontSize: " + std::to_string(generatedNumbersFontSize) + "\n" \
               "generateBingosCount: " + std::to_string(generateBingosCount) + "\n" \
               "generateBingosDirectory: " + generateBingosDirectory.string() + "\n" \
               "originalBingoBoardFile: " + originalBingoBoardFile.string() + "\n" \
               "fontFile: " + fontFile.string();
    }
};
