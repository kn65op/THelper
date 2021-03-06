#include "OS/WindowsPaths.hpp"

using namespace THelper::OS;

WindowsPaths::WindowsPaths()
{
}

WindowsPaths::~WindowsPaths()
{
}

std::string WindowsPaths::getHomeDir() const
{
  return std::string(std::getenv("HOMEDRIVE")) + std::getenv("HOMEPATH");
}

std::string WindowsPaths::getTmpDir() const
{
  return std::string(std::getenv("TEMP"));
}