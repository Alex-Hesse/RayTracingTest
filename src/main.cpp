#include <iostream>

int main() {
    // Image 

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255" << std::endl;

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            int r = static_cast<int>(255.999 * i / (image_width - 1));
            int g = static_cast<int>(255.999 * j / (image_height - 1));
            int b = 128;
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }

}