#ifndef SETING_H
#define SETING_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QMutex>
#include <QCloseEvent>
#include <heder.h>
#include <QCheckBox>
#include <QRegExpValidator>



class seting : public QWidget
{
    Q_OBJECT
public:
    explicit seting(QPushButton *seter , QPushButton * name,QPushButton * pic_name,QMutex * mutex_seting,QPushButton * ,int *music_bool,QWidget *parent = nullptr);

signals:

public slots:

    void save();
    void mypic_set();
    void music_set();

private:
    QPushButton *pic[9];
    QLabel *lb_name, *lb_addr;
    QPushButton *pb_ok, *pb_close;
    QLineEdit *te_name;
    QPushButton *pic1;
    QPushButton * set_name;
    QPushButton * pic_name;
    QLineEdit *set_addr;
    QPushButton *all_addr;
    QMutex * mutex_seting;
    QCheckBox * music;
    int  *music_bool;


protected:
    void closeEvent(QCloseEvent *event);

};

#endif // SETING_H
