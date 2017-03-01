/***********************************************************
 * Label控件
 * 自定义有点击事件的label, 系统自带label无点击事件
 *
 *
 * create by MasterFan
 *      on 2017年2月10日
 *
 *
 *
 ***********************************************************/

#include "MFLabel.h"
#include <QDebug>

MFLabel::MFLabel(QWidget * parent) : QLabel(parent)
{
    leftPressed = true;
    setMouseTracking(true);
}


void MFLabel::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "Press::label:x=" << this->pos().x() << "," << this->pos().y() << "Event:x=" << event->pos().x() << "y=" << event->pos().y();
}

void MFLabel::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "Move::label:x=" << this->pos().x() << "," << this->pos().y() << "Event:x=" << event->pos().x() << "y=" << event->pos().y();
}

void MFLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint ePos = event->pos();

    //判断为左键点击
    if (ePos.x() >= 1 && ePos.x() <= this->width() && ePos.y() >= 1 && ePos.y() <= this->height() && event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
