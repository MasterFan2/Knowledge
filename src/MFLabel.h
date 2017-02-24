#ifndef MFLABEL_H
#define MFLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

/**
 * @brief 有点击事件的Label
 */
class MFLabel : public QLabel
{
    Q_OBJECT
public:
    MFLabel(QWidget * parent = 0);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool leftPressed;
};

#endif // MFLABEL_H
