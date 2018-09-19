#ifndef MYWIDGT_H
#define MYWIDGT_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QUdpSocket>
#include <heder.h>
#include <QTimer>
#include <QCloseEvent>
#include <QMutex>
#include <QTime>
#include <QKeyEvent>

class mywidgt : public QWidget
{
    Q_OBJECT
public:
    explicit mywidgt( QPushButton * name,QPushButton * pic_name,DATA*, QUdpSocket *, QPushButton *pb ,QMutex * mutex,QMutex *  read_Mutex, QPushButton * ,QWidget *parent = nullptr);

signals:

public slots:

    void send_data();
    void timeout();
    void clear_data();
private:
    QPushButton *pb_send, *pb_close;
    QLabel *lb2;
    QPushButton *lb1;
    QTextEdit *te_recv, *te_send;

    QUdpSocket *udpSocket;
    QUdpSocket *myudpSocket;
    DATA * data;

    QPushButton *pb;
    QPushButton * myname;
    QPushButton * mypic_name;
    QTimer *tm;
    QPushButton * all_addr;
    QMutex * mutex;
    QMutex *  read_Mutex;
    int x;
    QPushButton *clear;

protected:
     void closeEvent(QCloseEvent *event);

};

#endif // MYWIDGT_H
