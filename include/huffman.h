#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <iterator>

namespace Huffman
{
  //! Coder class
  /*
    * Coder
    * 
    * Class dedicated to convert text file to create
    * the Huffman Coding compression
    */
  class Coder
  {
  private:
    //! Symbol Table
    /*
     * Symbol table
     * 
     * Maps a symbol to its probability
    */
    std::map<std::string, double> symbol_table_;
    //! characters counter
    /*
     * Counts how many characters exists on the source
    */
    int character_counter_;

    //! File string stream
    /*
     * Its the content read from the file
     * as a bector of bits
    */
    std::vector<bool> file_content_;

    //! Encoded data
    /*
     * Contains the encoded data bitstream
    */
    std::vector<bool> encoded_data_;

    //! Symbol Encode map
    /*
     * Maps the symbol to its code
    */
    std::map<std::string, std::string> symbol_encode_;

  public:
    //! characters counter
    /*
     * Increases n_characters on the character_counter variable.
    */
    void CountCharacters(int n_characters);

    //! Fill stream
    /*
     * Fill the Coder buffer with the file's content
    */
    void FillBuffer(std::string file_path);

    //! How many Characters
    /*
     * Returns the number of characters from read
     * from the file
    */
    int HowManyCharacters();

    //! Characters quantity
    /*
     * Returns the number of characters from read
     * from the file
    */
    int CharactersQuantity();

    //! Get buffer
    /*
     * Returns buffer content
    */
    std::vector<bool> GetBuffer();

    //! Count Symbol
    /*
     * Count the read symbol in the symbol_table
    */
    void CountSymbol(std::string character);

    //! Get Symbol Table
    /*
     * Returns Symbol Table
    */
    std::map<std::string, double> GetSymbolTable();

    //! Computes probability table
    /*
     * This function computes the probability table 
     * from of the symbol table after populate it with its
     * counting in the source input file.
    */
    void ComputeProbabilityTable();

    //! Compute Huffman Code
    /*
     * This function computes the Huffman code for a given
     * symbol alphabet and its frequency in a source.
    */
    void ComputeHuffmanCode();

    //! Write Compress File
    /*
     * Get the encoded file and writes
     * it in the compressed file.
    */
    void WriteCompressFile();

    //! Encode function
    /*
     * Gets the input file buffer file_content_ and encodes it
     * to the created Huffman Code buffer encoded_data_
    */
    void Encode();

    //! Compress to File functino
    /*
     * Writes the encoded_data_ to a 
     * compressed file, .huff
    */
    void CompressToFile(std::string file_name);

  };

  //! Decoder class
  /*
    * Decoder
    * 
    * Class dedicated to decompress .huff compressed file to 
    * the original file and format
    */
  class Decoder
  {
  private:
  };
} // namespace Huffman

#endif