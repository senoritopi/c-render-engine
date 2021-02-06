#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include "tgaimage.h"

const int width  = 100;
const int height = 100;

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor color) {
    for(float t = 0.; t < 1.; t += 0.1) {
        int x = x0 * (1. - t) + x1 * t;
        int y = y0 * (1. - t) + y1 * t;
        img.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);

    line(10, 10, 10, 90, image, white);
    line(10, 10, 90, 10, image, white);
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, white);

    line(90, 90, 10, 10, image, red);

    image.flip_vertically();
    image.write_tga_file("output.tga");

} 