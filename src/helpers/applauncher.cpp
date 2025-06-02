#include "tde/helpers/applauncher.hpp"

namespace tde::helpers {

AppLauncher::AppLauncher(const DesktopSettings& /*settings*/, QObject* parent)
  : QObject{ parent }
{
}

void
AppLauncher::on_request_launch_app(const helpers::AppInfo& app)
{
  qInfo() << "Launching app:" << app.name << "with command:" << app.exec;

  auto* proc = new QProcess{ this };
  connect(proc, &QProcess::finished, this, &AppLauncher::on_finish_app);

  emit start_app(app);

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
AppLauncher::on_finish_app(int code, QProcess::ExitStatus status)
{
  qInfo() << "App exited with code:" << code << "and status:" << status;

  auto* proc = qobject_cast<QProcess*>(sender());
  proc->deleteLater();

  emit finish_app(code, status);
}

}
