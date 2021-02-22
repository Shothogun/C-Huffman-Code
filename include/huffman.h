#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>

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
    */
    std::string file_content_;

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
    void FillBuffer(std::string s);

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
    std::string GetBuffer();

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