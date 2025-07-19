#include <qapplication.h>
#include <tde/app/builder.hpp>

#include "monitor.hpp"

int
main(int argc, char** argv)
{
  using tde::app::Builder;
  using tde::assets::Styles;

  auto app = QApplication{ argc, argv };

  auto ui =
    Builder<Monitor>()
      .with_name("TDE Monitor")
      .with_scope(Styles::Scope::APPLICATION | Styles::Scope::COMPONENTS)
      .build();
  ui.show();

  return QApplication::exec();
}
