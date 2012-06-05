#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    bool setSize(int,int);
    bool setGridT(int,int,int**);
    bool setEPath(int,int,int**);
    bool setParams(int,int,int***);

//    QSize minimumSizeHint() const;
//    QSize sizeHint() const;

public slots:


protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap ** pixmaps;
    QPixmap ** pathpixmaps;
    QString *** qsparams;
    int n,m,**gridt;
    static const int d=50;
};

#endif
