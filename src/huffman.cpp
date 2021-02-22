#include "../include/huffman.h"
#define DEBUG 1

int Huffman::Coder::HowManyCharacters()
{
  return this->character_counter_;
}

int Huffman::Coder::CharactersQuantity()
{
  return this->character_counter_;
}

void Huffman::Coder::CountCharacters(int n_characters)
{
  this->character_counter_ += n_characters;
}

void Huffman::Coder::FillBuffer(std::string s)
{
  this->file_content_ += s;
}

std::string Huffman::Coder::GetBuffer()
{
  return this->file_content_;
}

void Huffman::Coder::CountSymbol(std::string character)
{
  this->symbol_table_[character]++;
}

std::map<std::string, double> Huffman::Coder::GetSymbolTable()
{
  return this->symbol_table_;
}

void Huffman::Coder::ComputeProbabilityTable()
{
  for (auto &x : this->GetSymbolTable())
  {
    this->symbol_table_[x.first] /= this->HowManyCharacters();
  }
}

void Huffman::Coder::ComputeHuffmanCode()
{
  // Vector of pair probability and symbol
  std::vector<std::pair<double, std::string>> symbol_vector;

  // Vector that stores the symbols pairs chosen
  // during the combination, following its choice order
  std::vector<std::pair<std::string, std::string>> combined_pairs;

  // Stores the father node of the tree generated,
  // determines the childer code appending 0 or 1
  std::vector<std::string> father;

  // Maps the symbol to its code
  std::map<std::string, std::string> code_map;

  // Counts the ith alpha generated symbol from combination
  // of primitive symbol
  int alpha_count = 0;

  // Fill symbol vector
  for (auto const &x : this->GetSymbolTable())
  {
    symbol_vector.push_back(std::make_pair(x.second, x.first));
  }

  // Combines symbols
  while (symbol_vector.size() > 2)
  {
    // Sort in ascending order
    std::sort(symbol_vector.begin(), symbol_vector.end());

    // Get the 2 least probability symbols
    double first_symbol_probability = symbol_vector.front().first;
    std::string first_symbol = symbol_vector.front().second;
    symbol_vector.erase(symbol_vector.begin());

    double second_symbol_probability = symbol_vector.front().first;
    std::string second_symbol = symbol_vector.front().second;
    symbol_vector.erase(symbol_vector.begin());

    combined_pairs.push_back(std::make_pair(first_symbol, second_symbol));

    double new_probability = first_symbol_probability;
    new_probability += second_symbol_probability;

    symbol_vector.push_back(
        std::make_pair(new_probability,
                       "alpha_" + std::to_string(alpha_count)));

    father.push_back("alpha_" + std::to_string(alpha_count));

    alpha_count++;
  }

  // The remaining symbols will initiate
  // the code pattern
  auto it = symbol_vector.begin();
  auto next = symbol_vector.begin() + 1;
  code_map[it->second]="1";
  code_map[next->second]="0";

  std::reverse(father.begin(), father.end());
  std::reverse(combined_pairs.begin(), combined_pairs.end());
  auto current_father = father.begin();

  // Produces code to each symbol
  for (auto p : combined_pairs)
  {
    std::string code = code_map[*current_father];
    code_map[p.first] = code+"1";
    code_map[p.second] = code+"0";
    current_father++;
  }

  if (DEBUG)
  {
    std::cout << "Combined Pair\n";

    for (auto it : combined_pairs)
    {
      std::cout << it.first
                << " : "
                << it.second
                << std::endl;
    }

    std::cout << "Father\n";

    for (auto it : father)
    {
      std::cout << it
                << std::endl;
    }

    std::cout << "Code Map\n";

    for (auto const &x : code_map)
    {
      std::cout << x.first
                << ':'
                << x.second
                << std::endl;
    }
  }
}
