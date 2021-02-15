#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <map>

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
    std::map<std::string, int> symbol_table;

    //! characters counter
    /*
     * Counts how many characters exists on the source
    */
    int character_counter;

    //! File string stream
    /*
     * Its the content read from the file
    */
    std::string file_content;

  public:
    //! characters counter
    /*
     * Increases n_characters on the character_counter variable.
    */
    void count_characters(int n_characters);

    //! Fill stream
    /*
     * Fill the Coder buffer with the file's content
    */
    void fill_buffer(std::string s);

    //! How many Characters
    /*
     * Returns the number of characters from read
     * from the file
    */
    int how_many_characters();

    //! Get buffer
    /*
     * Returns buffer content
    */
    std::string getBuffer();
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