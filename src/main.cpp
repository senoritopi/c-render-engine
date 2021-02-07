#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;

const int width  = 800;
const int height = 800;

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

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

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

Vec3f normalize(Vec3f values) {
    int oldMax = 1;
    int oldMin = -1;

    int newMin = 0;
    int newXMax = width;
    int newYMax = height;

    int oldRange = (oldMax - oldMin);

    int newXRange = (newXMax - newMin);
    int newYRange = (newYMax - newMin);

    int newXValue = (((values.x - oldMin) * newXRange) / oldRange) + newMin;
    int newYValue = (((values.y - oldMin) * newYRange) / oldRange) + newMin;

    Vec3f normalized;
    normalized.z = values.z;
    normalized.x = newXValue;
    normalized.y = newYValue;
    return normalized;
}


int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    
    model = new Model("../src/test.obj");

    for(int i = 0; i < model->nfaces(); i++){
        std::vector<int> face = model->face(i);
        for(int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);

            Vec3f v0Normalized = normalize(v0);
            Vec3f v1Normalized = normalize(v1);

            int x0 = v0Normalized.x;
            int y0 = v0Normalized.y;

            int x1 = v1Normalized.x;
            int y1 = v1Normalized.y;

            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    return 0;
}

