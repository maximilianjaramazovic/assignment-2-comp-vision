// Program 1 - HW2
// Author: Maximilian Jaramazovic

#include <iostream>
#include <string>

#include "image.h"
using namespace ComputerVisionProjects;

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
  turnToBinaryImg(input_file, threshold);
  std::cout << "Finished p1.";
}

void turnToBinaryImg(std::string input_file, int threshold) {
  Image* input_image;
  ReadImage(input_file, input_image);
  for ()
}
