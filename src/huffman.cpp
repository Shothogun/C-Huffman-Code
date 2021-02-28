#include "../include/huffman.h"
#include "../include/bitstream.h"
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

void Huffman::Coder::FillBuffer(std::string file_path)
{

  // Read file as binary data
  std::ifstream f(file_path, std::ios::binary | std::ios::in);
  if (!f)
  {
    std::cout << "File not found\n";
    exit(0);
  };
  char c;

  // Gets each byte until no more
  // is left
  while (f.get(c))
  {
    // Gets each bit from the byte
    for (int i = 7; i >= 0; i--)
    {
      this->file_content_.push_back(((c >> i) & 1));
    }

    // Each byte is a character
    this->CountCharacters(1);
  }
}

std::vector<bool> Huffman::Coder::GetBuffer()
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
  code_map[it->second] = "1";
  code_map[next->second] = "0";

  std::reverse(father.begin(), father.end());
  std::reverse(combined_pairs.begin(), combined_pairs.end());
  auto current_father = father.begin();

  // Produces code to each symbol
  for (auto p : combined_pairs)
  {
    std::string code = code_map[*current_father];
    code_map[p.first] = code + "1";
    code_map[p.second] = code + "0";
    current_father++;
  }

  for (auto p : code_map)
  {
    if (p.first[0] == '0' || p.first[0] == '1')
    {
      this->symbol_encode_[p.first] = p.second;
    }
  }

  if (DEBUG)
  {
    std::cout << "Combined Pair\n\n";

    for (auto it : combined_pairs)
    {
      std::cout << it.first
                << " : "
                << it.second
                << "\n";
    }

    std::cout << "Father\n\n";

    for (auto it : father)
    {
      std::cout << it
                << "\n";
    }

    std::cout << "Code Map\n\n";

    for (auto const &x : code_map)
    {
      std::cout << x.first
                << ':'
                << x.second
                << "\n";
    }
  }
}

void Huffman::Coder::Encode()
{
  std::string byte_bitstream = "";
  std::string encoded_symbol = "";
  std::string bit = "";

  for (uint base = 0; base < this->file_content_.size(); base += 8)
  {
    byte_bitstream.clear();
    encoded_symbol.clear();

    // Constructs the byte symbol
    for (uint i = 0; i < 8; i++)
    {
      byte_bitstream += std::to_string(this->file_content_[base + i]);
    }

    encoded_symbol = this->symbol_encode_[byte_bitstream];

    // Gets the encoded symbol, bit by bit,
    // and concatenates to the encoded bitstream
    for (uint i = 0; i < encoded_symbol.size(); i++)
    {
      bit = encoded_symbol[i];
      this->encoded_data_.push_back(stoi(bit));
    }
  }

  if (DEBUG)
  {

    if (this->encoded_data_.size() > 1000)
    {
      std::cout << "WARNING: A TOO LONG BITSTREAM TO PRINT";
    }

    else
    {
      std::cout << "Original bitstream"
                << "\n";

      for (auto x : this->file_content_)
      {
        std::cout << to_string(x);
      }
      std::cout << "\n";

      std::cout << "Encoded bitstream"
                << "\n";

      for (auto x : this->encoded_data_)
      {
        std::cout << to_string(x);
      }
      std::cout << "\n\n";
    }

    for (auto const &x : this->symbol_encode_)
    {
      std::cout << x.first
                << ':'
                << x.second
                << std::endl;
    }

    std::cout << "Symbols number:\t\t"
              << this->symbol_encode_.size()
              << '\n';
  }

  std::cout << "Compression rate:\t";

  double compression_rate = 1;
  compression_rate -= (double)this->encoded_data_.size() /
                      (double)this->file_content_.size();

  compression_rate *= 100;

  std::cout << compression_rate
            << "%"
            << "\n";
}

void Huffman::Coder::CompressToFile(std::string file_name)
{
  // 2 Bytes: symbols number
  // tuples: array of tuples [a size code]
  // a    -> 1 Byte:  symbol
  // size -> 1 Byte:  encode size
  // code -> n Bytes: symbol encode

  // Empty Bitstream object
  Bitstream bstream;

  // Inserts symbols number as bits
  for (int i = 0; i < 16; i++)
  {
    bstream.writeBit((this->symbol_encode_.size() >> (15 - i)) & 1);
  }

  std::string bit;

  // Inserts array of tuples as bits
  for (auto p : this->symbol_encode_)
  {
    // Inserts Symbol
    for (int i = 0; i < 8; i++)
    {
      bit = p.first[i];
      bstream.writeBit(stoi(bit));
    }

    // Inserts encode size
    for (int i = 0; i < 8; i++)
    {
      bstream.writeBit((p.second.size() >> (7 - i)) & 1);
    }

    // Inserts symbol encode
    for (int i = 0; i < p.second.size(); i++)
    {
      bit = p.second[i];
      bstream.writeBit(stoi(bit));
    }
  }

  for (int i = 0; i < this->encoded_data_.size(); i++)
  {
    bstream.writeBit(this->encoded_data_[i]);
  }

  bstream.flushesToFile(file_name);
}