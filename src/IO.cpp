#include "../include/huffman.h"
#include "../include/IO.h"

#define DEBUG 0

Huffman::Coder *read_file_to_coder(char *file_path)
{
  // Coder object
  Huffman::Coder *coder = new Huffman::Coder();

  // line read from the file
  char *line = NULL;

  // String that populates the coder buffer
  std::string line_string;

  // File's content
  std::string buffer;

  // How many characters were read
  ssize_t read_n_characters;
  size_t len = 0;

  FILE *original_file = std::fopen(file_path, "r");
  if (original_file == NULL)
    perror("Error opening file");

  // Until reach no line is left, read lines
  while ((read_n_characters = getline(&line, &len, original_file)) != -1)
  {
    coder->CountCharacters(read_n_characters);

    // Converts char* -> std::string
    line_string = line;

    coder->FillBuffer(line_string);

    // Resets line read
    line_string.clear();
  }

  buffer = coder->GetBuffer();
  std::string character;

  // Counts symbols
  for (uint i = 0; i < buffer.length(); i++)
  {
    character = buffer[i];
    coder->CountSymbol(character);
  }

  coder->ComputeProbabilityTable();

  double sum=0;

  if (DEBUG)
  {
    for (auto const &x : coder->GetSymbolTable())
    {
      std::cout << x.first 
                << ':'
                << x.second
                << std::endl;

      sum += x.second;
    }
  }

  return coder;
}