#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "mlogic.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE
class RenderArea;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void browse();

private:
    RenderArea *renderArea;
    QLabel *qLabel1;
    QLineEdit *qEdit1;
    QPushButton *qButton1;
    MLogic *mLogic;
    int n,m,**gridt;
};

#endif // MAINWINDOW_H
