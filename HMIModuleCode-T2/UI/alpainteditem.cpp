#include "alpainteditem.h"
#include "Modules/typedef.h"
ALPaintedItem::ALPaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent),
    m_brushColor(QColor(0, 0, 0 ,255)),
    m_eraserColor(QColor(255,255,255,255)),
    m_pDrawPath(NULL),
    m_penWidth(0),
    m_bFlag(true),
    m_bErasered(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    //myStart();
}

ALPaintedItem::~ALPaintedItem()
{
}

void ALPaintedItem::paint(QPainter *painter)
{
    if(m_bFlag)
        painter->drawImage(QRectF(0,0,m_bgImage.width(),m_bgImage.height()),m_bgImage);
    else
    {
        painter->drawImage(QRectF(0,0,m_tempImage.width(),m_tempImage.height()),m_tempImage);
        painter->drawImage(QRectF(0,0,m_bgImage.width(),m_bgImage.height()),m_bgImage);
    }
}

void ALPaintedItem::init()
{
    m_bgImage = QImage(this->width(),this->height(),QImage::Format_ARGB32);
    m_tempImage = QImage(this->width(),this->height(),QImage::Format_ARGB32);
    m_bgImage.fill(QColor(255,255,255,0));
    m_tempImage.fill(QColor(255,255,255,0));
}

void ALPaintedItem::clear()
{
    m_bgImage.fill(QColor(255,255,255,0));
    m_tempImage.fill(QColor(255,255,255,0));
    update();
}

void ALPaintedItem::draw()
{
    mousePressEvent(NULL);
}

void ALPaintedItem::myStart()
{
    if(m_pDrawPath == NULL)
    {
        m_pDrawPath = new QPainterPath();
    }
    m_pDrawPath->moveTo(QPointF(0,0));
    m_nowPoint = QPointF(0,0);

    myPoint(QPointF(1,2));
    myPoint(QPointF(2,3));
    myPoint(QPointF(300,100));
    myPoint(QPointF(4,5));
    myPoint(QPointF(566,666));
    myEnd();
}

void ALPaintedItem::myEnd()
{
    if(m_pDrawPath != NULL)
    {
        m_bFlag = true;
        drawBgLine(*m_pDrawPath);
        delete m_pDrawPath;
        m_pDrawPath = NULL;
    }
}
void ALPaintedItem::myPoint(QPointF point)
{
    m_lastPoint = m_nowPoint;
    m_nowPoint = point;
    QPointF tmpPoint = m_nowPoint - m_lastPoint;
    if(m_pDrawPath == NULL)
    {
        return;
    }
    if(qAbs(tmpPoint.x()) > 0 || qAbs(tmpPoint.y()) >0)
    {
        m_pDrawPath->quadTo(m_lastPoint.x() , m_lastPoint.y() ,(m_nowPoint.x() + m_lastPoint.x())/2,(m_nowPoint.y() + m_lastPoint.y())/2);
        m_bFlag = false;
        if(m_bErasered)
            drawBgLine(*m_pDrawPath);
        else
            drawTmpLine(); // 临时画
    }
}

void ALPaintedItem::mousePressEvent(QMouseEvent *event)
{
    UNUSED(event);
//    if(!(event->button() & acceptedMouseButtons()))
//    {
//        QQuickPaintedItem::mousePressEvent(event);
//    }
//    else{
//        if(m_pDrawPath == NULL)
//        {
//            m_pDrawPath = new QPainterPath();
//        }
//        m_pDrawPath->moveTo(event->localPos());
//        m_nowPoint = event->localPos();
//    }
    myStart();

}

//void ALPaintedItem::mouseMoveEvent(QMouseEvent *event)
//{
//    m_lastPoint = m_nowPoint;
//    m_nowPoint = event->localPos();
//    QPointF tmpPoint = m_nowPoint - m_lastPoint;
//    if(m_pDrawPath == NULL)
//    {
//        return;
//    }
//    if(qAbs(tmpPoint.x()) > 0 || qAbs(tmpPoint.y()) >0)
//    {
//        m_pDrawPath->quadTo(m_lastPoint.x() , m_lastPoint.y() ,(m_nowPoint.x() + m_lastPoint.x())/2,(m_nowPoint.y() + m_lastPoint.y())/2);
//        m_bFlag = false;
//        if(m_bErasered)
//            drawBgLine(*m_pDrawPath);
//        else
//            drawTmpLine(); // 临时画
//    }
//    QQuickPaintedItem::mouseMoveEvent(event);
//}

//void ALPaintedItem::mouseReleaseEvent(QMouseEvent *event)
//{
//    if(!(event->button() & acceptedMouseButtons()))
//    {
//        QQuickPaintedItem::mousePressEvent(event);
//    }
//    else{
//        if(m_pDrawPath != NULL)
//        {
//            m_bFlag = true;
//            drawBgLine(*m_pDrawPath);
//            delete m_pDrawPath;
//            m_pDrawPath = NULL;
//        }
//    }
//}

void ALPaintedItem::drawTmpLine()
{
    QPainter painter(&m_tempImage);
    drawPenStyle(&painter);
    painter.drawLine(m_lastPoint,m_nowPoint);
    qreal rad = this->width()/375.0*170;//点周围范围值
    qDebug() << "rad:" << rad;
    QRect rect = QRect(m_nowPoint.x() - 5, m_nowPoint.y() - 5,10,10);
    update(rect.adjusted(-rad,-rad,+rad,+rad));
}

void ALPaintedItem::drawBgLine(const QPainterPath &path)
{
    QPainter painter(&m_bgImage);
    drawPenStyle(&painter);
    painter.drawPath(path);
    m_tempImage.fill(QColor(255,255,255,0));
    update();
}

void ALPaintedItem::drawPenStyle(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QBrush brush(m_brushColor, Qt::SolidPattern);
    if(m_bErasered)
    {
        painter->setCompositionMode(QPainter::CompositionMode_Clear);
        painter->setPen(QPen(brush, 5*m_penWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    }
    else
    {
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter->setPen(QPen(brush, m_penWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    }
    painter->setBrush(Qt::NoBrush);
}
