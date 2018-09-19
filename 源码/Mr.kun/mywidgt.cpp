#include "mywidgt.h"

mywidgt::mywidgt(QPushButton * name,QPushButton * pic_name,DATA* data, QUdpSocket *sock,QPushButton *pb, QMutex * mutex ,QMutex *  read_Mutex ,QPushButton * addr,QWidget *parent) : QWidget(parent)
{

    //this->setStyleSheet("border:none");



    all_addr =addr;
    x =0;
    clear = new QPushButton("清空",this);
    clear->setFont(QFont("宋体",18));

    myudpSocket = new QUdpSocket;
    this->mutex = mutex;
    this->read_Mutex = read_Mutex;
    this->pb =pb;
    tm =new QTimer;
    tm->start(500);
    myname = name;
    mypic_name = pic_name;
    this->data =data;
    this->udpSocket = sock;
    setFixedSize(1000,700);
    pb_send = new QPushButton("发送");
    pb_close= new QPushButton("关闭");
    pb_send->setFont(QFont("宋体",18));
    pb_close->setFont(QFont("宋体",18));
    pb_send->setStyleSheet("background-color: rgb(98, 7, 245);");
    pb_send->setStyleSheet("color:red");
    lb1 = new QPushButton;
    lb2 = new QLabel;
    lb2->setFixedSize(800,60);
    te_recv = new QTextEdit;

    te_send = new QTextEdit;
    te_recv->setFont(QFont("宋体",10));
    te_send->setFont(QFont("宋体",17));
    te_send->setFixedSize(1000,100);
    lb1->setFixedSize(60,60);
    lb1->setIcon(QIcon("0.jpg"));
    lb1->setIconSize(QSize(60,60));
    //lb1->setEnabled(0);
    lb1->setStyleSheet("border:none");
   QHBoxLayout * hbox1 = new QHBoxLayout;
   hbox1->addWidget(lb1);
   hbox1->addWidget(lb2);
   hbox1->addWidget(clear);

   QHBoxLayout * hbox2 = new QHBoxLayout;
   hbox2->addWidget(pb_send);
   hbox2->addWidget(pb_close);

   QVBoxLayout *vbox = new QVBoxLayout;
   vbox->addLayout(hbox1);
   vbox->addWidget(te_recv);
   vbox->addWidget(te_send);
   vbox->addLayout(hbox2);
   setLayout(vbox);
   connect(pb_send,SIGNAL(clicked(bool)),this,SLOT(send_data()));
   connect(pb_close,SIGNAL(clicked(bool)),this,SLOT(close()));
   connect(tm,SIGNAL(timeout()),this,SLOT(timeout()));
   connect(clear,SIGNAL(clicked(bool)),this,SLOT(clear_data()));
}

void mywidgt::send_data()
{

    if( te_send->toPlainText().isEmpty())
       return;

    QString buf =pb->text();
    int len=buf.indexOf(' ');
    QString num =buf.mid(0, len);

    DATA mydata;
    mydata.GN =0;
    mydata.name =myname->text();
    mydata.pic =mypic_name->text();
    mydata.data= "hello";

    QString str =QString::number(mydata.GN)+"###";
    str += mydata.name+"###";
    str += mydata.pic+"###";
    str += te_send->toPlainText();
     QString temp =  all_addr->text();
    int len2 =temp.lastIndexOf(".");
     QString addr=temp.mid(0,len2+1);

    addr+=buf.mid(0,len);
    //qDebug()<<addr;


     myudpSocket->writeDatagram(str.toStdString().c_str(),strlen(str.toStdString().c_str()),QHostAddress(addr),quint16(23456));
    //qDebug()<<str;

     QFile file("/Mr.kun/data/"+QString::number(num.toShort())+".md");
      if (! file.open(QIODevice::WriteOnly| QIODevice::Append| QIODevice::Text));
         // return;

      QTime tm;
      tm.currentTime().toString("HH-mm-ss");
      QTextStream out(&file);
      out <<"myself"<<" :"<<tm.currentTime().toString("HH:mm:ss")<< "\n";
      out <<te_send->toPlainText()<< "\n\n";
      file.close();
    te_send->clear();

}


void mywidgt::timeout()
{
    QString str =pb->text();
    int len=str.indexOf(' ');
    QString num =str.mid(0, len);
    qDebug()<<str.mid(0, len);
    lb1->setIcon(QIcon(data[num.toShort()].pic));

    QFile file("/Mr.kun/data/"+QString::number( num.toShort())+".md");
     if (! file.open(QIODevice::ReadOnly| QIODevice::Text));
        //return;
     int size = file.size();
     QTextStream in (&file);
     file.seek(x);
          while (!in.atEnd()) {
              QString line = in.readLine();
              te_recv->append(line);
          }
     x =size;
     file.close();

    lb2->setText(data[num.toShort()].name);
    lb2->setFont(QFont("黑体",20));
    setWindowTitle("     与   "+data[num.toShort()].name+"  聊天中");

}

void mywidgt::clear_data()
{
    te_recv->clear();
}

void mywidgt::closeEvent(QCloseEvent *event)
{

    mutex->unlock();
    tm->stop();
    this->close();
}
