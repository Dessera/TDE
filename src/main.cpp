#include <tde/application.hpp>

int
main(int argc, char** argv)
{
  using tde::Application;

  Application app{ argc, argv };
  return Application::exec();
}
