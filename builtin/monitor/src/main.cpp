#include <qapplication.h>
#include <tde/app/builder.hpp>
#include <tde/assets/styles.hpp>

#include "monitor.hpp"

int
main(int argc, char** argv)
{
  using tde::app::Builder;
  using tde::assets::styles::Scope;

  auto app = QApplication{ argc, argv };

  auto ui = Builder<Monitor>()
              .with_name("TDE Monitor")
              .with_scope(Scope::APPLICATION | Scope::COMPONENTS)
              .build();
  ui.show();

  return QApplication::exec();
}
