#include "../include/huffman.h"
#include "../include/io.h"
#include "../include/bitstream.h"

#define DEBUG 0

Huffman::Encoder *read_file_to_coder(char *file_path)
{
  // encoder object
  Huffman::Encoder *encoder = new Huffman::Encoder();

  // String that populates the encoder buffer
  std::string line_string;

  // File's content
  std::vector<bool> buffer;

  // Get the bitstream and stores as
  // a string sequence.
  encoder->FillBuffer(file_path);

  // Returns the string sequence
  // representing the bits from the file
  buffer = encoder->GetBuffer();

  // A byte bitstream as a string
  std::string byte_bitstream = "";

  // Counts symbols
  for (uint base = 0; base < buffer.size(); base += 8)
  {
    byte_bitstream.clear();

    // Reads a byte sequence, represents a character
    for (uint i = 0; i < 8; i++)
    {
      byte_bitstream = byte_bitstream + std::to_string(buffer[base + i]);
    }

    encoder->CountSymbol(byte_bitstream);
  }

  encoder->ComputeProbabilityTable();

  double sum = 0;

  if (DEBUG)
  {
    std::cout << "-----------------------------\n"
              << "-- Symbol Probabilities -----\n"
              << "-----------------------------\n";

    // As bytes
    for (auto const &x : encoder->GetSymbolTable())
    {
      std::cout << x.first
                << ':'
                << x.second
                << std::endl;

      sum += x.second;
    }

    std::cout << "\n";

    if (encoder->GetBuffer().size() > 1000)
    {
      std::cout << "WARNING: A TOO LONG BITSTREAM TO PRINT";
    }

    else
    {
      std::cout << "-----------------------------\n"
                << "-- Input file bits ----------\n"
                << "-----------------------------\n";
      for (auto i : encoder->GetBuffer())
      {
        std::cout << std::to_string(i);
      }
      std::cout << "\n\n";
    }
  }

  return encoder;
}