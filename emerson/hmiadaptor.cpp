#include "hmiadaptor.h"
#include <qdebug.h>
HmiAdaptor::HmiAdaptor(QObject *parent) : QObject(parent)
{

}

void HmiAdaptor::openFileDialog()
{
    qDebug() << tr("openFileDialog");
    //QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open File"),"C:",tr("Images (*.png *.xpm *.jpg)"));
}
