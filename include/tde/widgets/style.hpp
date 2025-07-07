/**
 * @file style.hpp
 * @author Dessera (dessera@qq.com)
 * @brief Style factory.
 * @version 0.1.0
 * @date 2025-07-07
 *
 * @copyright Copyright (c) 2025 Dessera
 *
 */

#pragma once

#include <qstring.h>
#include <qstringlist.h>

#include "tde/common.hpp"
#include "tde/settings.hpp"

namespace tde::widgets {

/**
 * @brief Style factory.
 *
 */
class TDE_PUBLIC StyleFactory
{
public:
  inline static const QString DEFAULT_STYLE =
    ":/tde/styles/default.qss"; /**< Default style. */

  /**
   * @brief Generate QSS from files.
   *
   * @param files User defined qss files.
   * @return QString Final QSS.
   */
  static QString generate_qss(const QStringList& files = {});

  /**
   * @brief Generate QSS from desktop settings.
   *
   * @param settings Desktop settings.
   * @return QString Final QSS.
   */
  static QString generate_qss(const DesktopSettings& settings);

private:
  /**
   * @brief Read qss from file.
   *
   * @param file QSS file path.
   * @param buffer QSS buffer.
   */
  static void _read_qss(const QString& file, QString& buffer);
};

}
