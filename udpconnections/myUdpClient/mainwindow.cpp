#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket = new QUdpSocket(this);
    connect(mSocket, &QUdpSocket::readyRead, [&]() {
        if(mSocket->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(mSocket->pendingDatagramSize());
            mSocket->readDatagram(datagram.data(),datagram.size());
            ui->listWidget->addItem(QString(datagram));
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{   //the default is udpsocket->bind(SOME_PORT_VALUE, QUdpSocket::ShareAddress);
    mSocket->bind(ui->portNo->value(), QUdpSocket::ShareAddress);
}
