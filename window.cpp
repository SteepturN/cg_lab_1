#include "window.h"
#include "qcustomplot.h"
#include "qevent.h"
#include "qmargins.h"
#include <QWidget>
#include <cmath>
#include <iostream>
Window::Window( QWidget* parent )
    : QMainWindow( parent ), a_param_d( 1 ) {
    QVector< double > x, y;
 //   this->setWindowState( Qt::WindowMaximized );
    mPlot = new QCustomPlot( this );


    mPlot->addGraph();

//    mPlot->graph( 0 )->setData(QVector<double>{-1000, 1000}, QVector<double>{0, 0} );

    graph = new QCPCurve( mPlot->xAxis, mPlot->yAxis );

    calc( x, y );
    graph->setData( x, y );
    mPlot->setInteractions( QCP::iRangeZoom | QCP::iRangeDrag );

    this->setCentralWidget( mPlot );

    QToolBar* toolbar = new QToolBar;
    this->addToolBar( Qt::TopToolBarArea, toolbar );
    a_param = new QLineEdit;
    a_param->setValidator( new QRegularExpressionValidator( QRegularExpression( "[+]{0,1}[0-9]+\\.{0,1}[0-9]*" ) ) );
    toolbar->addWidget( a_param );

    QPushButton* button = new QPushButton;
    button->setText( "Close" );
    button->setFont( QFont( "GoMono" ) );
    toolbar->addWidget( button );
    QObject::connect( button, SIGNAL( clicked() ), this, SLOT( close() ) );


    a_param->setMaximumSize( 100, 100 );
    // mPlot->xAxis->setBasePen( QPen( Qt::black, 3 ) );
    // mPlot->yAxis->setBasePen( QPen( Qt::black, 3 ) );
    mPlot->xAxis->setRange( -5, 5 );

    mPlot->yAxis->setRange( -5, 5 );

    mPlot->axisRect()->setAutoMargins(QCP::msNone);
/*
    this->setWindowState( Qt::WindowMaximized );
    mPlot->replot( QCustomPlot::RefreshPriority::rpImmediateRefresh );
    mPlot->xAxis->setOffset(-500);
    mPlot->yAxis->setOffset(500);
*/
    QObject::connect( a_param, SIGNAL( editingFinished() ), this, SLOT( change_a() ) );
    QObject::connect( mPlot, SIGNAL( beforeReplot() ), this, SLOT( xy() ) );
    QObject::connect( mPlot, SIGNAL( resizeEvent() ), this, SLOT( xy() ) );
    //QObject::connect( this, SIGNAL( rp() ), this, SLOT( xy() ) );

    //emit rp();
}

void Window::resizeEvent(QResizeEvent* event) {
    xy_change();
}
void Window::calc( QVector< double >& x, QVector< double >& y ){
/*
    for( long double r = 0; r <= 2 * a_param_d; r += 0.001 ){
        // r = ( 1 - cos f ) * a
        // x = r cos f
        // y = r sin f

        x.push_back( r * ( 1 - r / a_param_d ) );
        std::cout << "r / a_param_d = " << r / a_param_d
                  << "\nstd::pow( 1 - r / a_param_d, 2 )" << std::pow( 1 - r / a_param_d, 2 )
                  << "\nstd::sqrt( 1 - std::pow( 1 - r / a_param_d, 2 ) )"
                  << std::sqrt( 1 - std::pow( 1 - r / a_param_d, 2 ) ) << '\n';
        y.push_back( r * std::sqrt( 1 - std::pow( 1 - r / a_param_d, 2 ) ) );

    }
    x.push_back( -2 * a_param_d );
    y.push_back( 0 );
*/
    for( double fi = 0; fi <= 2 * M_PI; fi += 0.001 ) {
        double cur_cos = std::cos( fi );
        double cur_sin = std::sin( fi );

        x.push_back( a_param_d * cur_cos * ( 1 - cur_cos ) );
        y.push_back( a_param_d * cur_sin * ( 1 - cur_cos ) );
    }
}

void Window::change_a() {
    a_param_d = a_param->text().toDouble();
//    std::cout << a_param_d << '\n';
    QVector< double > x, y;
    calc( x, y );
    graph->setData( x, y );
    mPlot->replot( QCustomPlot::RefreshPriority::rpImmediateRefresh );
}
void Window::xy_change() {
    int pxx = mPlot->yAxis->coordToPixel( 0 );
    int pxy = mPlot->xAxis->coordToPixel( 0 );
    mPlot->xAxis->setOffset(- mPlot->axisRect()->height() - mPlot->axisRect()->top() + pxx);
    mPlot->yAxis->setOffset(mPlot->axisRect()->left() - pxy);
    mPlot->replot( QCustomPlot::RefreshPriority::rpImmediateRefresh );
}
void Window::xy() {
    int pxx = mPlot->yAxis->coordToPixel( 0 );
    int pxy = mPlot->xAxis->coordToPixel( 0 );
    mPlot->xAxis->setOffset(- mPlot->axisRect()->height() - mPlot->axisRect()->top() + pxx);
    mPlot->yAxis->setOffset(mPlot->axisRect()->left() - pxy);
}
