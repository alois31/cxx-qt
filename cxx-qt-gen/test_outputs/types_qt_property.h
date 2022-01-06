#pragma once

#include <mutex>

#include "rust/cxx_qt.h"

#include <QtCore/QPointF>
#include <QtCore/QVariant>

namespace cxx_qt::my_object {

class RustObj;

class MyObject : public CxxQObject
{
  Q_OBJECT
  Q_PROPERTY(QPointF pointf READ getPointf WRITE setPointf NOTIFY pointfChanged)
  Q_PROPERTY(QString string READ getString WRITE setString NOTIFY stringChanged)
  Q_PROPERTY(
    QVariant variant READ getVariant WRITE setVariant NOTIFY variantChanged)

public:
  explicit MyObject(QObject* parent = nullptr);
  ~MyObject();

  const QPointF& getPointf() const;
  const QString& getString() const;
  const QVariant& getVariant() const;

public Q_SLOTS:
  void setPointf(const QPointF& value);
  void setString(const QString& value);
  void setVariant(const QVariant& value);

Q_SIGNALS:
  void pointfChanged();
  void stringChanged();
  void variantChanged();

private:
  rust::Box<RustObj> m_rustObj;
  std::mutex m_rustObjMutex;
  bool m_initialised = false;

  QPointF m_pointf;
  QString m_string;
  QVariant m_variant;
};

typedef MyObject CppObj;

std::unique_ptr<CppObj>
newCppObject();

} // namespace cxx_qt::my_object

Q_DECLARE_METATYPE(cxx_qt::my_object::CppObj*)