#include "../include/huffman.h"
#include "../include/IO.h"

Huffman::Coder* read_file_to_coder(char *file_path)
{
  // Coder object
  Huffman::Coder *coder = new Huffman::Coder();

  // line read from the file
  char *line = NULL;

  // String that populates the coder buffer
  std::string line_string;

  // How many characters were read 
  ssize_t read_n_characters;
  size_t len = 0;

  FILE *original_file = std::fopen(file_path, "r");
  if (original_file == NULL)
    perror("Error opening file");

  // Until reach no line is left, read lines
  while ((read_n_characters = getline(&line, &len, original_file)) != -1)
  {
    coder->count_characters(read_n_characters);

    // Converts char* -> std::string
    line_string = line;

    coder->fill_buffer(line_string);

    // Resets line read
    line_string.clear();
  }


  std::cout << coder->getBuffer();
}