#include <qdebug.h>

#include "tde/app/launcher.hpp"

namespace tde::app {

void
Launcher::launch(const Info& app)
{
  qInfo() << "Launching app:" << app.name << "with command:" << app.exec;

  auto* proc = new QProcess{ this };
  connect(proc, &QProcess::finished, this, &Launcher::_on_app_finish);

  emit before_app_start(app);

  proc->startCommand(app.exec);
  if (!proc->waitForStarted()) {
    // take it as a special error exit
    QMetaObject::invokeMethod(proc,
                              "finished",
                              Q_ARG(int, -1),
                              Q_ARG(QProcess::ExitStatus, QProcess::CrashExit));
  }
}

void
Launcher::on_request_launch_app(const Info& app)
{
  launch(app);
}

void
Launcher::_on_app_finish(int code, QProcess::ExitStatus status)
{
  qInfo() << "App exited with code:" << code << "and status:" << status;

  auto* proc = qobject_cast<QProcess*>(sender());
  proc->deleteLater();

  emit after_app_finish(code, status);
}

}
