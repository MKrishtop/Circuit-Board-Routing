#include <QtGui>

#include "mainwindow.h"
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    renderArea = new RenderArea;

    qEdit1 = new QLineEdit(tr("Path..."));
    //qEdit1->text(tr("Path..."));

    qLabel1 = new QLabel(tr("&Input file:"));
    qLabel1->setBuddy(qEdit1);

    qButton1 = new QPushButton(tr("&Browse"));
    connect(qButton1, SIGNAL(clicked()), this, SLOT(browse()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->setRowMinimumHeight(1, 6);
    mainLayout->addWidget(qLabel1, 2, 1, Qt::AlignRight);
    mainLayout->addWidget(qEdit1, 2, 2, Qt::AlignRight);
    mainLayout->addWidget(qButton1, 2, 3, Qt::AlignRight);
    mainLayout->addWidget(renderArea, 3, 0, 1, 4);

    setLayout(mainLayout);

    setWindowTitle(tr("L6V14_oapsois"));

    this->setMinimumHeight(100);
    this->setMinimumWidth(300);

    mLogic = new MLogic();
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete qEdit1;
    delete qLabel1;
    delete qButton1;
}

void MainWindow::browse()
{
    QString filepath = QFileDialog::getOpenFileName(this,tr("Select input datafile"),QDir::currentPath());

    if (!filepath.isEmpty()) {
        qEdit1->setText(filepath);
        std::string str = std::string(filepath.toAscii().data());
        const char * stuff = str.c_str();
        mLogic->SetFN(stuff);
        mLogic->eval();
        n=mLogic->GetN();
        m=mLogic->GetM();
        gridt=mLogic->GetGridT();
        //this->resize(n*50,m*50+75);
        this->setFixedSize(m*50+25,n*50+75);
        renderArea->setSize(n,m);
        renderArea->setGridT(n,m,gridt);
        renderArea->setEPath(n,m,mLogic->GetEPath());
        renderArea->setParams(n,m,mLogic->GetParams());
        renderArea->repaint();

        //B->eval(A->GetXArray(),A->GetYArray(),A->GetN(),A->GetTriangles(),stuff,
        //        A->GetTArray(),A->GetX(),A->GetY(),A->GetResultTemp());
    }
}
