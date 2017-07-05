#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class TcpClient;
}

class TcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();

private slots:
    void on_connectBut_clicked();

    void on_quitBut_clicked();

    void clientRecieve();

private:
    Ui::TcpClient *ui;
    QTcpSocket *clientSocket;
};

#endif // TCPCLIENT_H
