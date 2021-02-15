#include "../include/huffman.h"

int Huffman::Coder::how_many_characters(){
  return this->character_counter;
}

void Huffman::Coder::count_characters(int n_characters){
  this->character_counter += n_characters;
}

void Huffman::Coder::fill_buffer(std::string s){
  this->file_content += s;
}

std::string Huffman::Coder::getBuffer(){
  return this->file_content;
}