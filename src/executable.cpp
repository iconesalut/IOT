#include "executable.hpp"

Executable::Executable(std::string file_name): m_binary(std::unique_ptr<const LIEF::ELF::Binary>{LIEF::ELF::Parser::parse(file_name)})
{
    auto&& static_symbols = m_binary->static_symbols();
    if (static_symbols.size() > 0) {
      std::cout << "== Static symbols ==" << std::endl;
      for (const LIEF::ELF::Symbol& symbol : static_symbols) {
        std::cout << symbol << std::endl;
      }
    }
  
    std::cout << "== Dynamics symbols ==" << std::endl;
    for (const LIEF::ELF::Symbol& symbol : m_binary->dynamic_symbols()) {
      std::cout << symbol << std::endl;
    }
}
Executable::~Executable()
{}

void Executable::extractFunction()
{}
void Executable::saveAt(std::string)
{}

void Executable::AddFunctionData()
{}

void Executable::findSection(std::string name)
{}
void Executable::findSection(int address)
{}
void Executable::findFunction(std::string name)
{}
void Executable::findFunction(int address)
{}