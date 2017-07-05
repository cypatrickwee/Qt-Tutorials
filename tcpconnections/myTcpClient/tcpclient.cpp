#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientRecieve()));
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_connectBut_clicked()
{
    clientSocket->connectToHost(ui->ipadd->text(), ui->portNo->value());
}

void TcpClient::on_quitBut_clicked()
{
    close();
}

void TcpClient::clientRecieve(){
    QString datas=clientSocket->readAll();
    QByteArray debugdata = datas.toLatin1();
    char *out=debugdata.data();
    ui->listInfoArea->addItem(QString(debugdata));
    clientSocket->flush();
}
