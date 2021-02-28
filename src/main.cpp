#include <iostream>
#include "../include/huffman.h"
#include "../include/io.h"

using namespace std;

int main(int argc, char *argv[]){
  Huffman::Coder* coder;
  char* file_name = argv[1];
  std::string out_file = "out.huff";

  coder = read_file_to_coder(file_name);
  coder->ComputeHuffmanCode();
  coder->Encode();
  coder->CompressToFile(out_file);
  return 0;
}