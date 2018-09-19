#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <mywidgt.h>
#include <seting.h>
#include <QTime>
#include <stdlib.h>
#include <QTimer>
#include <QUdpSocket>
#include <heder.h>
#include <QMutex>
#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QSound>
#include <QDir>
#include <QMessageBox>
#include <QDialogButtonBox>
#define  MAX 256


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton *lb[MAX];
    QPushButton *pb[MAX];
    QPushButton *fg[MAX];
    QScrollArea *pArea;
    QWidget * qw ;
    int on_line[255];
    QPushButton *seter;
    QPushButton *pic_name;
    QPushButton * name;
    DATA data[256];
    QTimer *tm, *tm2;
    QUdpSocket *udpSocket;
    QUdpSocket *udpSocket2;
    QMutex * mutex[256];
    QMutex * mutex_seting;
    QMutex *read_Mutex;
    QPushButton * all_addr;
    QPushButton *list;
    int music_bool;
    int Bt[MAX];
    mywidgt *my[MAX];
    void mybind();
    int Q;


private slots:
    void myfun();
    void my_seting( );
    void timeout();
    void recv_data();
    void recv_data2();
    void ZX();

protected:
    void closeEvent(QCloseEvent *event);


};

#endif // WIDGET_H
