#include <qapplication.h>
#include <tde/app/builder.hpp>
#include <tde/widgets/desktop.hpp>

int
main(int argc, char** argv)
{
  using tde::app::Builder;
  using tde::widgets::Desktop;

  auto app = QApplication{ argc, argv };

  auto ui = Builder<Desktop>().with_name("TDE").with_decoration(false).build();
  ui.show();

  return QApplication::exec();
}
