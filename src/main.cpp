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
    bool transpose = false; 
	// si la línea es demasiado inclinada la transponemos
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        transpose = true; 
    } 
	// si la línea es de derecha a izquierda intercambiamos
    if (x0 > x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 

    int dx = x1 - x0;
    int dy = y1 - y0;

    int error = 2 * dy - dx;
    int dn = error + dx;
    int dp = error - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++) { 
        if(error < 0){
            error += dn;
        } else {
            error += dp;
            y += (y1 > y0 ? 1 : -1);
        }

        if (transpose) { 
            img.set(y, x, color); 
        } else { 
            img.set(x, y, color); 
        } 
    } 
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);

    unsigned t0, t1;
    t0=clock();

    for (int i = 0; i < 30000000; i++) {
        line(13, 20, 80, 40, image, white);
    }

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    printf("Execution Time: %f \n", time);

    line(10, 10, 10, 90, image, white);
    line(10, 10, 90, 10, image, white);
    line(13, 20, 80, 40, image, white);
    line(20, 13, 40, 80, image, white);

    line(90, 90, 10, 10, image, red);

    image.flip_vertically();
    image.write_tga_file("output.tga");

} 