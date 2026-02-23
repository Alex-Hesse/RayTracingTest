#include <iostream>
#include "vec3.h"
#include "color.h"



void firstPPM(int image_width, int image_height, int i, int j) {
    auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0.5);
    write_color(std::cout, pixel_color);
}

int main() {
    // Image 

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255" << std::endl;

    for (int j = image_height - 1; j >= 0; --j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            firstPPM(image_width, image_height, i, j);
        }
    }
    std::clog << "\rDone.                 " << std::endl;
}