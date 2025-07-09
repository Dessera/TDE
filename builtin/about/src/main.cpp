#include <qapplication.h>

#include "about.hpp"
#include "tde/app/builder.hpp"

int
main(int argc, char** argv)
{
  return tde::app::run<AboutWidget>("About", argc, argv);
}
