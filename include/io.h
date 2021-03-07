#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <map>
#include <cmath>
#include "huffman.h"

// Receives file title and returns Coder object
Huffman::Encoder* read_file_to_coder(char* file_path);

// Receive a processed coder object and 
// writes the compressed data in a .huff file
void writeCompressedFile(Huffman::Encoder encoder);

#endif