#pragma once
#include <QMainWindow>
#include <QFont>
#include <QSize>
#include <QIcon>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QSlider>
#include <QProgressBar>
#include "qcustomplot.h"
#include "qevent.h"
#include "qlineedit.h"
#include "qmainwindow.h"
#include <QToolBar>
class Window : public QMainWindow {
    Q_OBJECT
    public:
        explicit Window( QWidget *parent = nullptr );
        void calc( QVector< double >&, QVector< double >& );
        void xy_change();
    private:
        long double a_param_d;
        QLineEdit* a_param;
        QCPCurve* graph;
        QCustomPlot* mPlot;
    protected:
        void resizeEvent( QResizeEvent* ) override;
    private slots:
        void change_a();
        void xy();
    signals:
        //void rp();
};
