#include <tde/app/builder.hpp>

#include "monitor.hpp"

int
main(int argc, char** argv)
{
  return tde::app::run<Monitor>("Monitor", argc, argv);
}
