#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


QDir dir;
dir.cd("/");  //进入某文件夹
if(!dir.exists("Mr.kun"))//判断需要创建的文件夹是否存在
{
    dir.mkdir("Mr.kun"); //创建文件夹
}
dir.cd("/Mr.kun");  //进入某文件夹
if(!dir.exists("data"))//判断需要创建的文件夹是否存在
{
    dir.mkdir("data"); //创建文件夹
}

QFile file("/Mr.kun/data/mrkun.config");
if(!file.exists())
{
 if (! file.open(QIODevice::WriteOnly| QIODevice::Text));
 QTextStream out(&file);
 QString str("鬼豸");
 out <<"name "<<str<<"\n";
 out <<"ip 127.0.0.1\n";
 out <<"pic 0.png\n";
 out << "music 0\n";
 file.close();
}


QFile file3("/Mr.kun/readme.md");
if(!file3.exists())
{
 if (! file3.open(QIODevice::WriteOnly| QIODevice::Text));
 QTextStream out(&file3);
 QString str("本目录下的文件为聊天配置文件与历史记录文件勿删!!");
 out<<str<<"\n";
 file3.close();
}

 for(int i=0; i<MAX; i++)
    {
        Bt[i] =0;

    }

    this->setStyleSheet("border:none");
    this->setStyleSheet("background-color: rgb(218, 224, 250);");

    //music_bool =0;                                                //music
    setWindowTitle("小坤聊天       -by小坤");
    all_addr = new QPushButton;
    //all_addr->setText("192.168.5.1");                             //ip
    all_addr->hide();

    for(int i=0; i<MAX;i++)
        data[i].line =0;
    Q =0;
    udpSocket = new QUdpSocket;
    udpSocket2 = new QUdpSocket;
    //udpSocket->bind(QHostAddress("0.0.0.0"), quint16(12345));
    //udpSocket2->bind(QHostAddress("0.0.0.0"), quint16(23456));
        mybind();
    read_Mutex = new QMutex;

    for(int i=0; i<256;i++)
    mutex[i] = new QMutex;
    mutex_seting  = new QMutex;
    pic_name = new QPushButton;
   // pic_name->setText("0.jpg");                       //头像
    pic_name->hide();
    list = new QPushButton;
    list->setFixedSize(380,100);
    list->setIcon(QIcon("list.jpg"));
    list->setIconSize(QSize(400,100));
    tm = new QTimer;
    tm2 = new QTimer;
    tm->start(1000);
    tm2->start(3000);
    seter = new QPushButton;
    name = new QPushButton;
    //name->setText("<---点头像进入设置");           //name
    name->setFont(QFont("行楷",14));
    name->setFixedSize(280,60);
    //name->setEnabled(0);
    name->setStyleSheet("border:none");
  //  seter->setIcon(QIcon(pic_name->text()));
    seter->setFixedSize(60,60);
    seter->setIconSize(QSize(60,60));
    seter->setStyleSheet("border:none");
    setFixedSize(400,800);
    QHBoxLayout *hboxl = new QHBoxLayout;
    hboxl->addWidget(seter);
    hboxl->addWidget(name);



    QFile file2("/Mr.kun/data/mrkun.config");
     if (! file2.open(QIODevice::ReadOnly| QIODevice::Text));
        //return;
     QTextStream in (&file2);
          while (!in.atEnd()) {
            QString line1 = in.readLine();
            QString line2 = in.readLine();
            QString line3 = in.readLine();
            QString line4 = in.readLine();
            name->setText(line1.mid(5));
            all_addr->setText(line2.mid(3));
            pic_name->setText(line3.mid(4));
            music_bool = line4.mid(6).toShort();
            seter->setIcon(QIcon(pic_name->text()));
          }
     file2.close();

    pArea= new QScrollArea(this);
    qw = new QWidget(pArea);//需要滚动的是一个Qwidget，而如果是在设计器里面拖入控件，会自动添加一个
    qw->setStyleSheet("border:none");
    //qw->setStyleSheet("background-color: rgb(179, 229, 273);");
    QHBoxLayout *hbox[MAX];
    srand( time(NULL));
    for(int i =0; i<MAX; i++)
     {

        pb[i] = new QPushButton(qw);
        pb[i]->setFixedSize(280,60);
        pb[i]->setText(QString::number(i+1));
        lb[i] = new QPushButton(qw);
        lb[i]->setFixedSize(60,60);
        lb[i]->setIcon(QIcon(QString::number(rand()%9+1)+".jpg"));
        lb[i]->setIconSize(QSize(60,60));
        lb[i]->setText(QString::number(i)+' ');
        lb[i]->setFont(QFont("宋体",1));
        fg[i] = new QPushButton(qw);
        fg[i]->setFixedSize(500,10);
        fg[i]->setIcon(QIcon("fg.jpg"));
        fg[i]->setIconSize(QSize(500,10));
        fg[i]->hide();
        hbox[i] = new QHBoxLayout;
        hbox[i]->addWidget(lb[i]);
        hbox[i]->addWidget(pb[i]);

        pb[i]->hide();
        lb[i]->hide();
        pb[i]->setFont(QFont ("宋体",15));
        lb[i]->setFocusPolicy(Qt::NoFocus);
       lb[i]->setStyleSheet("border:none");
       pb[i]->setStyleSheet("border:none");

    }

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hboxl);
    vbox->addWidget(list);
    for(int i =0; i <MAX; i++)
    {
        vbox->addLayout(hbox[i]);
        vbox->addWidget(fg[i]);
    }
       qw->setLayout(vbox);


    pArea->setWidget(qw);//这里设置滚动窗口qw，
    pArea->setGeometry(0,0,400,800);//要显示的区域大小
    qw->setGeometry(0,0,380,200);//这里变大后，看出他实际滚动的是里面的QWidget窗口
    connect(seter,SIGNAL(clicked(bool)),this,SLOT(my_seting())); //设置
    for(int i =0; i< MAX; i++)
        {
        connect(pb[i],SIGNAL(clicked(bool)),this,SLOT(myfun())); //昵称对话
        connect(lb[i],SIGNAL(clicked(bool)),this,SLOT(myfun())); //头像对话
    }

    connect(tm,SIGNAL(timeout()),this,SLOT(timeout())); //发送 检查
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(recv_data()));
    connect(udpSocket2, SIGNAL(readyRead()), this, SLOT(recv_data2()));
    connect(tm2,SIGNAL(timeout()),this,SLOT(ZX()));

}

Widget::~Widget()
{

}

void Widget::mybind()
{
    if(!udpSocket->bind(QHostAddress("0.0.0.0"), quint16(12345)))
    {
        Q=1;
        this->close();
        qw->close();
        return;
    }
    if(!udpSocket2->bind(QHostAddress("0.0.0.0"), quint16(23456)))
    {
            Q=1;
            this->close();
            qw->close();
            return;

    }

}



void Widget::myfun()
{

    QPushButton *pb = static_cast<QPushButton*>(sender());
    QString str =pb->text();
    int len=str.indexOf(' ');
    QString num =str.mid(0, len);
    int bt = num.toShort();

    if(!mutex[bt]->tryLock())

    return;

   my[bt] = new mywidgt(name,pic_name,data,udpSocket2,pb, mutex[bt],read_Mutex,all_addr);
    my[bt]->show();
    //qDebug()<<pb->text();
}


void Widget::my_seting()
{

    if(!mutex_seting->tryLock())
    return;
    seting *set = new seting(seter,name,pic_name,mutex_seting,all_addr,&music_bool);
    set->show();



}

void Widget::timeout()
{
    DATA mydata;
    mydata.GN =1;
    mydata.name =name->text();
    mydata.pic =pic_name->text();
    mydata.data= "hello";

    QString str =QString::number(mydata.GN)+"###";
    str += mydata.name+"###";
    str += mydata.pic+"###";
    str += mydata.data;
    QString temp =  all_addr->text();
    int len =temp.lastIndexOf(".");
    qDebug() <<len;
    QString addr=temp.mid(0,len+1);
    qDebug()<<addr;
    for(int i =0; i<MAX; i++)
     udpSocket->writeDatagram(str.toStdString().c_str(),strlen(str.toStdString().c_str()),QHostAddress(addr+QString::number(i)),quint16(12345));

}

void Widget::recv_data()
{
    QHostAddress temp;

      char buf[1000] = {0};
      int ret;
      QString str;
      ret = udpSocket->readDatagram(buf, sizeof(buf), &temp, NULL);
     // qDebug()<<buf;
         QString addr = temp.toString();
         if(addr.isEmpty())
             return;
        // qDebug()<<addr;
        int len =addr.lastIndexOf(".");
        QString  num =addr.mid(len+1);
        str+=buf;
       // qDebug()<<num;
        int i =4;
       for(i;;i++)
        {
           if(i >str.length()-1)
               break;
           if(str.at(i) =='#')
               break;
         }
      // qDebug()<<i;
        data[num.toShort()].GN =str.mid(0,1).toShort();
        data[num.toShort()].name =str.mid(4,i-4);
        data[num.toShort()].pic =str.mid(i+3,5);
        //if(data[num.toShort()].GN  ==0)
       // data[num.toShort()].data =str.mid(i+11);
        data[num.toShort()].line++;
       // qDebug()<< str.mid(4,i-4);

     //   qDebug()<<str;
        //qDebug()<<data[145].name;
       // qDebug()<<data[145].pic;
       // qDebug()<<data[145].data;
        //qDebug()<<num.toShort();




}

void Widget::recv_data2()
{

    QHostAddress temp;

      char buf[1000*4] = {0};
      int ret;
      QString str;
      ret = udpSocket2->readDatagram(buf, sizeof(buf), &temp, NULL);
     // qDebug()<<buf;
         QString addr = temp.toString();
         if(addr.isEmpty())
             return;
        // qDebug()<<addr;
        int len =addr.lastIndexOf(".");
        QString  num =addr.mid(len+1);
        str+=buf;
       // qDebug()<<num;
        int i =4;
       for(i;;i++)
        {
           if(i >str.length()-1)
               break;
           if(str.at(i) =='#')
               break;
         }
       //qDebug()<<i;
        //data[num.toShort()].GN =str.mid(0,1).toShort();
       // data[num.toShort()].name =str.mid(4,i-4);
       // data[num.toShort()].pic =str.mid(i+3,5);
        //if(data[num.toShort()].GN  ==0)
      //  if( !read_Mutex->tryLock())
         //   return;
         //  data[num.toShort()].data =str.mid(i+11);
        //   read_Mutex->unlock();
       // data[num.toShort()].line++;
       // qDebug()<< str.mid(4,i-4);

     //   qDebug()<<str;
        //qDebug()<<data[145].name;
       // qDebug()<<data[145].pic;
       // qDebug()<<data[145].data;
        //qDebug()<<num.toShort();

       // qDebug()<<"---------------"<<str.mid(i+11);
       // qDebug()<<"------"<<data[num.toShort()].data;
        QFile file("/Mr.kun/data/"+QString::number( num.toShort())+".md");
         if (! file.open(QIODevice::WriteOnly| QIODevice::Append| QIODevice::Text))
             return;
         //file.seek(file.size());

         QTime tm;
         tm.currentTime().toString("HH-mm-ss");
         QTextStream out(&file);
         out <<str.mid(4,i-4)<<" :"<<tm.currentTime().toString("HH:mm:ss")<< "\n";
         out <<str.mid(i+11) << "\n\n";
         file.close();

         // 消息弹窗
         QString str2 =pb[num.toShort()]->text();
         int len2=str2.indexOf(' ');
         QString num2 =str2.mid(0, len2);
         int bt = num2.toShort();
        //qDebug()<<  mutex[bt]->tryLock();

        if(0 == music_bool)
         QSound::play("msg.wav");

         if(!mutex[bt]->tryLock())
         return;

         mywidgt *my = new mywidgt(name,pic_name,data,udpSocket2,pb[num.toShort()], mutex[bt],read_Mutex,all_addr);
         my->show();


}

void Widget::ZX()
{
    int sum =0;

    for(int i=0; i<MAX;i++)
    {
        if(data[i].line ==0)
         {
            pb[i]->hide();
            lb[i]->hide();
            fg[i]->hide();
            Bt[i] =0;        }
        else
        {

            pb[i]->show();
            lb[i]->show();
            fg[i]->show();
            sum++;
            data[i].line =0;
            lb[i]->setIcon(QIcon(data[i].pic));
            pb[i]->setText(QString::number(i)+" "+data[i].name);
            if(Bt[i] ==0)
                if(0 == music_bool)
                QSound::play("Global.wav");
            Bt[i]=1;

         }
    }

    if(sum <8)
     {
         qw->setGeometry(0,0,380,sum*100+200);//这里变大后，看出他实际滚动的是里面的QWidget窗口
       return;

      }
    //qDebug()<<"sum = "<<sum;
     qw->setGeometry(0,0,380,800+sum*80);//这里变大后，看出他实际滚动的是里面的QWidget窗口

}


void Widget::closeEvent(QCloseEvent *event)
{

    event->setAccepted(0);

    if(1 == Q)
     {
        for(int i =0; i<MAX; i++)
        my[i]->close();
        this->close();
        return;
    }


    QMessageBox box(QMessageBox::Warning,"退出","是否退出");
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText (QMessageBox::Ok,QString("退 出"));
    box.setButtonText (QMessageBox::Cancel,QString("取 消"));
    int ret =box.exec ();

    switch (ret) {
        case QMessageBox::Ok:
            // Save was clicked
            {
            for(int i =0; i<MAX; i++)
            my[i]->close();
            this->close();
            }
        case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            break;
      }

}

