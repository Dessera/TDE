#include <qapplication.h>
#include <tde/app/builder.hpp>
#include <tde/assets/styles.hpp>

#include "about.hpp"

int
main(int argc, char** argv)
{
  using tde::app::Builder;
  using tde::assets::styles::Scope;

  auto app = QApplication{ argc, argv };

  auto ui = Builder<About>()
              .with_name("TDE About")
              .with_scope(Scope::APPLICATION | Scope::COMPONENTS)
              .build();
  ui.show();

  return QApplication::exec();
}
