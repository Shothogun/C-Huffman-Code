#include "../include/huffman.h"
#include "../include/io.h"
#include "../include/bitstream.h"

#define DEBUG 0

Huffman::Coder *read_file_to_coder(char *file_path)
{
  // Coder object
  Huffman::Coder *coder = new Huffman::Coder();

  // String that populates the coder buffer
  std::string line_string;

  // File's content
  std::vector<uint8_t> buffer;

  // Get the bitstream and stores as 
  // a string sequence.
  coder->FillBuffer(file_path);

  // Returns the string sequence 
  // representing the bits from the file
  buffer = coder->GetBuffer();

  // A byte bitstream as a string
  std::string byte_bitstream = "";

  // Counts symbols
  for (uint base = 0; base < buffer.size(); base+=8)
  { 
    byte_bitstream.clear();

    // Reads a byte sequence, represents a character
    for (uint i = 0; i < 8; i++)
    { byte_bitstream = byte_bitstream + std::to_string(buffer[base+i]);}

    coder->CountSymbol(byte_bitstream);
  }

  coder->ComputeProbabilityTable();

  double sum = 0;

  if (DEBUG)
  {
    // As bytes
    for (auto const &x : coder->GetSymbolTable())
    {
      std::cout << x.first
                << ':'
                << x.second
                << std::endl;

      sum += x.second;
    }

    for(auto i :coder->GetBuffer()){
      std::cout << std::to_string(i);
    }

    std::cout << std::endl;
  }

  return coder;
}