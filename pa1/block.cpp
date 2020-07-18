#include "block.h"

//

// completes a block's pixel data from the square area of dimension by dimension pixels 
// in im whose upper-left corner is at position (left, ,upper)
void Block::Build(PNG & im, int upper, int left, int dimension){
data.resize(dimension);
for (int i = 0; i <dimension; i++) {
    data[i].resize(dimension);
}


    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            data[i][j] = *im.getPixel(j + left, i + upper);
        }
    }
}


// const; draws the block at position (x,y) in im
void Block::Render(PNG & im, int upper, int left) const {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            *im.getPixel(j + left, i + upper) = data[i][j];
        }
    }
}

// reverses the hue and luminance of every pixel in the block, creating a simulated photo-negative effect
void Block::Negative() {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.size(); j++) {
            if (data[i][j].h >= 180) {
                data[i][j].h = data[i][j].h - 180;
            } else if (data[i][j].h < 180) {
                data[i][j].h = data[i][j].h + 180;
            } 
            data[i][j].l = 1 - data[i][j].l;
        }
    }
}

// const; returns the dimensions of the block
// horizontal and vertical dimensions are the same
int Block::Dimension() const {
    return data.size();
}