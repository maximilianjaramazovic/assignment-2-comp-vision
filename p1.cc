// Program 1 - HW2
// Author: Maximilian Jaramazovic

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

const ComputerVisionProjects::Image& turnToBinaryImg(Image& input_image, int threshold) {
  for (int row = 0; row < input_image.num_rows(); ++row) {
    for (int col = 0; col < input_image.num_columns(); ++col) {
      if (input_image.GetPixel(row, col) >= threshold)
        input_image.SetPixel(row, col, 255);
      else
        input_image.SetPixel(row, col, 0);
    }
  }

  return input_image;
}

int main(int argc, char **argv){
  
  if (argc != 4) {
    std::cout << "Usage: " <<
      argv[0] << " {input_image_name} {threshold} {output_image_name}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const int threshold = std::stoi(argv[2]);
  const std::string output_file(argv[3]);

  std::cout << "Running p1 " << input_file << " " 
            << threshold << " " << output_file << std::endl;
  Image* input_image = new Image();
  ReadImage(input_file, input_image);
  ComputerVisionProjects::Image binary_image = turnToBinaryImg(*input_image, threshold);
  std::cout << "Writing image." << std::endl;
  ComputerVisionProjects::WriteImage(output_file, binary_image);
  std::cout << "Finished p1.";
}
