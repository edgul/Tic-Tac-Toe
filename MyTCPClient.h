#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

enum TcpState
{
    DISCONNECTED,
    CONNECTING,
    CONNECTED
};

class MyTCPClient : public QObject
{
    Q_OBJECT
public:
    MyTCPClient();

    QTcpSocket socket;

    void connect_to_server();
    void send(QString str);
    void close();

signals:
    void report(QString);

private slots:
    void connected();
    void received_data();
    void closing();

    void flush_output();
private:

    TcpState state;

    QTimer flush_timer;
};

#endif // MYTCPCLIENT_H
