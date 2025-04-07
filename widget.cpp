#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //socket_.connected();
    QObject::connect(&socket_,&QAbstractSocket::connected, this, &Widget::doConnected);
    //socket_.disconnected();
    QObject::connect(&socket_,&QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    //socket_.readyread();
    QObject::connect(&socket_,&QIODevice::readyRead, this, &Widget::doReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){
    QString msg = "connected\r\n";
    ui->pteMessage->insertPlainText(msg);
}

void Widget::doDisconnected(){
    QString msg = "disconnected\r\n";
    ui->pteMessage->insertPlainText(msg);
}

void Widget::doReadyRead(){
    QString msg = socket_.readAll();
    ui->pteMessage->insertPlainText(msg);
}


void Widget::on_pbConnect_clicked(){
    if(ui->sslCb->isChecked()){
         socket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort());
    }
    else if (ui->tcpCb->isChecked()){
        socket_.connectToHost(ui->leHost->text(),ui->lePort->text().toUShort());
    }
}


void Widget::on_pbDisconnect_clicked()
{
    socket_.disconnectFromHost();
}



void Widget::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());
}

void Widget::on_sslCb_checkStateChanged(const Qt::CheckState &state)
{
    if (state == Qt::Checked)
        ui->tcpCb->setCheckState(Qt::Unchecked);
        ui->leHost->setText("www.naver.com");
        ui->lePort->setText("443");
}

void Widget::on_tcpCb_checkStateChanged(const Qt::CheckState &state)
{
    if (state == Qt::Checked)
        ui->sslCb->setCheckState(Qt::Unchecked);
        ui->leHost->setText("naver.com");
        ui->lePort->setText("80");
}



