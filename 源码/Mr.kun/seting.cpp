#include "seting.h"
#include "heder.h"
seting::seting(QPushButton *seter , QPushButton * name,QPushButton* pic_name,QMutex * mutex_seting, QPushButton *addr,int* music_bool,QWidget *parent) : QWidget(parent)
{

    this->music_bool =music_bool;

  music =new QCheckBox("静音",this);
  music->setChecked(*music_bool);


    all_addr = addr;
    set_addr = new QLineEdit(this);
    set_addr->setText(all_addr->text());

    QRegExp rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");  //ip
    QRegExpValidator * m_IPValidator = new QRegExpValidator(rx, this);
    set_addr->setValidator(m_IPValidator);



    this->mutex_seting =mutex_seting;

    this->pic_name = pic_name;
    pic1 = seter;
    set_name = name;
    setWindowTitle("设置头像以及昵称");
    lb_name = new QLabel("昵称");
    lb_addr = new QLabel("IP 请正确填写本机IP否则将无法正常通信");
    pb_ok = new QPushButton("保存");
    pb_close = new QPushButton("退出");
    te_name = new QLineEdit;
    te_name->setText(set_name->text());

    QRegExp rx1("[^# ]{1,16}$"); //空格 与#
    QValidator *validator_16c = new QRegExpValidator(rx1,this);
    te_name->setValidator(validator_16c);


    for(int i =0; i<9; i++)
    {
        pic[i] =new QPushButton;
        pic[i]->setIcon(QIcon(QString::number(i+1)+".jpg"));
        pic[i]->setText(QString::number(i+1));
        pic[i]->setFont(QFont("黑体",i));
       // qDebug()<<QString::number(i)+"jpg";
        pic[i]->setFixedSize(100,100);
        pic[i]->setIconSize(QSize(100,100));
    }
    QHBoxLayout *hbox2 = new QHBoxLayout;

    QHBoxLayout *hbox[5];
    for(int i=0; i<5; i++)
        hbox[i] = new QHBoxLayout;

    hbox[0]->addWidget(pic[0]);
    hbox[0]->addWidget(pic[1]);
    hbox[0]->addWidget(pic[2]);

    hbox[1]->addWidget(pic[3]);
    hbox[1]->addWidget(pic[4]);
    hbox[1]->addWidget(pic[5]);

    hbox[2]->addWidget(pic[6]);
    hbox[2]->addWidget(pic[7]);
    hbox[2]->addWidget(pic[8]);

    hbox[3]->addWidget(lb_name);
    hbox[3]->addWidget(te_name);
    hbox2->addWidget(lb_addr);
    hbox2->addWidget(set_addr);

    hbox[4]->addWidget(pb_ok);
    hbox[4]->addWidget(pb_close);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox[0]);
    vbox->addLayout(hbox[1]);
    vbox->addLayout(hbox[2]);
    vbox->addLayout(hbox[3]);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox[4]);
    vbox->addWidget(music);

    setLayout(vbox);
    connect(pb_ok,SIGNAL(clicked(bool)),this,SLOT(save()));
    connect(pb_close,SIGNAL(clicked(bool)),this,SLOT(close()));
    for(int i=0; i<9;i++)
        connect(pic[i],SIGNAL(clicked(bool)),this,SLOT(mypic_set()));
    connect(music,SIGNAL(clicked(bool)),this,SLOT(music_set()));

}

void seting::save()
{

    if(te_name->text().isEmpty())
        return;

    set_name->setText(te_name->text());

    if(set_addr->text().isEmpty())
        return;
    all_addr->setText(set_addr->text());

    //disconnect(pb_ok,SIGNAL(clicked(bool)),this,SLOT(save()));

    QFile file("/Mr.kun/data/mrkun.config");

     if (! file.open(QIODevice::WriteOnly| QIODevice::Text));
     QTextStream out(&file);
     QString str(te_name->text());
     out <<"name "<<str<<"\n";
     out <<"ip "+set_addr->text()+"\n";
     out <<"pic " + pic_name->text()  + "\n";
     out << "music "+ QString::number(*music_bool) + "\n";
     file.close();
     this->close();

}

void seting::mypic_set()
{
    QPushButton *pb = static_cast<QPushButton*>(sender());
    pic1->setIcon(pb->icon());
   // qDebug()<< pb->text();
    pic_name->setText(pb->text()+".jpg");

}

void seting::music_set()
{
    if(music->isChecked())
       *music_bool =1;
    else
        *music_bool =0;
}

void seting::closeEvent(QCloseEvent *event)
{
    mutex_seting->unlock();
    event->Close;
}



