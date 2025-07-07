#include <qapplication.h>

#include "about.hpp"

int
main(int argc, char** argv)
{
  QApplication app(argc, argv);

  AboutWidget about{};
  about.show();

  return QApplication::exec();
}