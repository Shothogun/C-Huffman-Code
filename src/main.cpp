#include <iostream>
#include "../include/huffman.h"
#include "../include/IO.h"

using namespace std;

int main(int argc, char *argv[]){
  Huffman::Coder* coder;
  char* file_name = argv[1];

  coder = read_file_to_coder(file_name);
  return 0;
}