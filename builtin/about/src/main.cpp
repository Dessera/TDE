#include <tde/app/builder.hpp>

#include "about.hpp"

int
main(int argc, char** argv)
{
  return tde::app::run<AboutWidget>("About", argc, argv);
}
