#pragma once

#include <cstddef>
#include <qlist.h>
#include <qstring.h>

namespace tde::sys::fs {

struct Usage
{
  QString name;
  std::size_t capacity;
  std::size_t available;
  std::size_t free;
};

QList<Usage>
usage();

}
