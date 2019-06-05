//
//  main.cpp
//  OpenCV Test
//
//  Created by Max Reynolds on 4/15/19.
//  Copyright © 2019 Max Reynolds. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <typeinfo>
#include "qtree.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Enter maximum variance \n0 = very little compression \n20 = a lot of compression" << endl;
    int max_comp;
    cin >> max_comp;
    Mat original = imread("/Users/maxreynolds/Desktop/lake.jpg", IMREAD_GRAYSCALE);
    Mat modified = imread("/Users/maxreynolds/Desktop/lake.jpg", IMREAD_GRAYSCALE);
    
    if (original.empty()){
        cout << "Could not open or find image"<< endl;
        return -1;
    }
    

    
    int rows=modified.rows;
    int cols=modified.cols;
    
    cout << "Rows: " <<  rows << endl;
    cout << "Cols: " <<  cols << endl;
    cout << "Total pixels: " << rows * cols << endl;

    int* pixels = new int[rows*cols];
    

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            pixels[r*cols+c]=modified.at<uint8_t>(r,c);
        }
    }

    qt_node* q = init_node();
    add_values(q, pixels, rows, cols);
    build_tree(q,max_comp);
    

    cout << "Nodes: " << count_tree_nodes(q) << endl;
    cout << "Pixel check: " << check_num_pixels(q) << endl;
    
    unpack_tree(q, modified, rows, cols);

    delete[] pixels;



    imshow("Original", original);
    imshow("Modified", modified);
    waitKey(0);
    return 0;
    
}
