#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    mServer = new QTcpServer(this);
    mSocket = nullptr;

    connect(mServer, SIGNAL(newConnection()),this, SLOT(newConnection()));

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::on_pushButton_clicked()
{
    if(!mServer->listen(QHostAddress::Any, ui->portNo->value())){
        QMessageBox::critical(this,"Error", mServer->errorString());
    }
    else{
        QMessageBox::information(this, "server", "initiating...");
    }
}

void TcpServer::on_pushButton_2_clicked()
{
    if(mSocket){
        QTextStream textValue(mSocket);
        textValue<<ui->message_1->text();
        mSocket->flush();
    }
}

void TcpServer::on_pushButton_3_clicked()
{
    close();
}

void TcpServer::newConnection(){
    mSocket = mServer->nextPendingConnection();
    connect(mSocket, SIGNAL(readyRead()),this, SLOT(receiveData()));
    qDebug()<<"new connection.";

}

void TcpServer::sendValue(const QString &ms){
    if(mSocket){
        QTextStream textValue(mSocket);
        textValue<<ms;
        mSocket->flush();
    }
}

void TcpServer::receiveData(){
    QString datas=mSocket->readAll();
    QByteArray debugdata = datas.toLatin1();
    char *out=debugdata.data();
    ui->listInfoArea->addItem(QString(debugdata));
    mSocket->flush();
}
