#include <iostream>
#include "../include/huffman.h"
#include "../include/io.h"

using namespace std;

int main(int argc, char *argv[]){
  Huffman::Encoder* encoder;
  Huffman::Decoder* decoder = new Huffman::Decoder();
  char* file_name = argv[1];
  std::string out_file = "out.huff";

  // Enconding
  encoder = read_file_to_coder(file_name);
  encoder->ComputeHuffmanCode();
  encoder->Encode();
  encoder->CompressToFile(out_file);

  // Decoding
  decoder->DecompressFromFile(out_file);
  decoder->Decode();

  return 0;
}