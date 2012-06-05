#include <QtGui>

#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    n=0;m=0;
}

bool RenderArea::setSize(int w, int h)
{
    n=h; m=w;
    this->setFixedSize(n*d,m*d);
    return true;
}

bool RenderArea::setGridT(int w, int h,int ** grid)
{
    n=h;
    m=w;
    gridt=grid;
    QString tmp;
    pixmaps = new QPixmap* [m];
    for (int i=0;i<m;i++)
    {
        pixmaps[i]=new QPixmap [n];
        for (int j=0;j<n;j++)
        {
            switch (gridt[i][j])
            {
                case 0: tmp=tr(":/pixmaps/empty.png"); break;
                case 1: tmp=tr(":/pixmaps/A.png"); break;
                case 2: tmp=tr(":/pixmaps/B.png"); break;
                case 3: tmp=tr(":/pixmaps/line_h.png"); break;
                case 4: tmp=tr(":/pixmaps/line_v.png"); break;
                case 5: tmp=tr(":/pixmaps/point_l.png"); break;
                case 6: tmp=tr(":/pixmaps/point_r.png"); break;
                case 7: tmp=tr(":/pixmaps/point_t.png"); break;
                case 8: tmp=tr(":/pixmaps/point_b.png"); break;
                case 9: tmp=tr(":/pixmaps/coner_1f.png"); break;
                case 10: tmp=tr(":/pixmaps/coner_2f.png"); break;
                case 11: tmp=tr(":/pixmaps/coner_3f.png"); break;
                case 12: tmp=tr(":/pixmaps/coner_4f.png"); break;
                default: tmp=tr(":/pixmaps/empty.png");
            }
            pixmaps[i][j].load(tmp);
        }
    }

    return true;
}

//QSize RenderArea::minimumSizeHint() const
//{
//    return QSize(100, 100);
//}

//QSize RenderArea::sizeHint() const
//{
//    return QSize(400, 200);
//}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            painter.save();
            painter.translate(j*d, i*d);

            painter.drawPixmap(0, 0, pixmaps[i][j]);
            painter.drawPixmap(0, 0, pathpixmaps[i][j]);
            QRect rect(5, 5, d-10, d-10);
            painter.drawText(rect, Qt::AlignRight, qsparams[i][j][0]);
            painter.drawText(rect, Qt::AlignLeft, qsparams[i][j][1]);
            painter.restore();
        }
    }

    //painter.setRenderHint(QPainter::Antialiasing, false);
    //painter.setPen(palette().dark().color());
    //painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

}


bool RenderArea::setEPath(int w, int h,int ** epath)
{
    n=h;
    m=w;

    QString tmp;
    pathpixmaps = new QPixmap* [m];
    for (int i=0;i<m;i++)
    {
        pathpixmaps[i]=new QPixmap [n];
        for (int j=0;j<n;j++)
        {
            switch (epath[i][j])
            {
                case 0: tmp=tr(":/pixmaps/no_path.png"); break;
                case 1: tmp=tr(":/pixmaps/path.png"); break;
                default: tmp=tr(":/pixmaps/no_path.png");
            }
            pathpixmaps[i][j].load(tmp);
        }
    }

    return true;
}

bool RenderArea::setParams(int w, int h, int*** params)
{
    n=h;
    m=w;
    qsparams = new QString** [m];
    for (int i=0;i<m;i++)
    {
        qsparams[i]=new QString* [n];
        for (int j=0;j<n;j++)
        {
            qsparams[i][j]=new QString[2];
            for (int k=0;k<2;k++)
                qsparams[i][j][k]=(params[i][j][k]<9999 && params[i][j][k]>0) ? QString::number(params[i][j][k],10) : "";
        }
    }
    return true;
}
