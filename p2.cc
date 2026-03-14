// Program 2 - HW2
// Author: <YOUR NAME>

#include <iostream>
#include <string>

#include "image.h"
#include "DisjSets.h"
using namespace ComputerVisionProjects;

Image sequencial_labler(Image binary) {
  const int W = binary.num_columns();
  const int H = binary.num_rows();
  int counter = 1;
  DisjSets ds(W*H+1);

  for (int row = 1; row < H; ++row) {
    for (int col = 1; col < W; ++col) {
      int curr = binary.GetPixel(row, col);
      // part of background, skip and find proper element
      if (curr == 0) {
        continue;
      }
      
      int top  = binary.GetPixel(row-1, col); //getting top neighbour
      int left = binary.GetPixel(row, col-1); //getting left neighbour
      
      // current is not a back ground
      if (top == 0 && left == 0) {
        // new object
        ++counter;
        binary.SetPixel(row, col, counter);
      } else if (left != 0 && top == 0) {
        //only left is object
        binary.SetPixel(row, col, ds.find(left));
      } else if (left == 0 && top != 0) {
        // Only top neighbor is object
        binary.SetPixel(row, col, ds.find(top));

      } else {
        // Both neighbors are objects record equivalence and merge
          int root_left = ds.find(left);
          int root_top  = ds.find(top);
          if (root_left == root_top) {
            // Case (e): already the same set – just propagate
            binary.SetPixel(row, col, root_left);
          } else {
            // Case (f): different sets – record equivalence and merge
            ds.unionSets(root_left, root_top);
            binary.SetPixel(row, col, ds.find(root_left));
        }
      }
    }
  }

  //----------------- IMAGE FORMATION -----------------
  int gradient = 255/counter;
  for (int r = 0; r < H; r++) {
    for (int c = 0; c < W; c++) {
      int curr_obj = binary.GetPixel(r,c);
      if (curr_obj != 0) {
        binary.SetPixel(r,c, curr_obj*gradient);
      }
    }
  }
  return binary;
}


int main(int argc, char **argv){
  
  if (argc!=3) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const std::string output_file(argv[2]);

  std::cout << "Running p2 " << input_file << " " << output_file << std::endl;
  Image* binary_image = new Image();
  ReadImage(input_file, binary_image);
  Image result = sequencial_labler(*binary_image);
  WriteImage(output_file, result);
  
  return 0;
}