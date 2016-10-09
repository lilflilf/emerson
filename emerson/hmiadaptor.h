#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include <QObject>

class HmiAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit HmiAdaptor(QObject *parent = 0);
    Q_INVOKABLE void openFileDialog();
signals:

public slots:
};

#endif // HMIADAPTOR_H
