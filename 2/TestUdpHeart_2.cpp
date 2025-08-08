#include "TestUdpHeart_2.h"
#include "ui_TestUdpHeart_2.h"

#include <random>

TestUdpHeart_2::TestUdpHeart_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestUdpHeart_2)
{
    ui->setupUi(this);
    setWindowTitle("TestUdpHeart_2");
    socket.bind(QHostAddress::Any, 30003);
    connect(&socket, &QUdpSocket::readyRead, this, &TestUdpHeart_2::read_msg);
}

TestUdpHeart_2::~TestUdpHeart_2()
{
    delete ui;
}

struct MessageHeader {
    uint8_t type{0x42};
    uint8_t flag{};
    uint16_t command{4};
    uint16_t length{};
    uint16_t req_id{};
};

void TestUdpHeart_2::read_msg()
{
    // QDataStream in(&buffer, QIODevice::ReadOnly);
    // in.setVersion(QDataStream::Qt_5_15);
    // ...
    // while (!in.atEnd()) {
    //     in >> out;
    while (socket.hasPendingDatagrams())
    {
        QByteArray buffer;
        QHostAddress ip;
        buffer.resize(socket.pendingDatagramSize());
        socket.readDatagram(buffer.data(), buffer.size(), &ip);
        int type;
        memcpy(&type, buffer.mid(0, sizeof(int)).constData(), sizeof(int));
        if (type < 0 || type > 2) {
            ui->output_1->setText(QString("Wrong type: %1").arg(type));
            return;
        }

        int cnt = buffer.size() / sizeof(int) - 1;
        QStringList pre_flag = {"rate", "heartbeat", "open device"};
        QString str = QString("--------%1: %2, cnt: %3\n").arg(type).arg(pre_flag[type]).arg(cnt);
        int offset = sizeof(int);
        for (int i = 0; i < cnt; i++) {
            int out;
            memcpy(&out, buffer.mid(offset, sizeof(int)).constData(), sizeof(int));
            offset += sizeof(int);
            str += QString::number(out) + "\n";

            uint16_t out_short = out;
            if (type == 1) {
                MessageHeader header;
                QByteArray datagram;
                QDataStream out(&datagram, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_15);
                header.req_id = 3;
                header.length = out_short + ui->input->value();
                out << header.type << header.flag << header.command << header.length << header.req_id;
                socket.writeDatagram(datagram, ip, 10001);
            }
        }

        QTextBrowser *output[3] = {ui->output_1, ui->output_2, ui->output_3};
        output[type]->append(str);
        output[type]->moveCursor(QTextCursor::End);
    }
}


void TestUdpHeart_2::on_btn_send_released()
{
    QByteArray datagram;
    datagram.append(reinterpret_cast<const char*>(&cnt), sizeof(cnt));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    auto random_v = dist(gen);
    datagram.append(reinterpret_cast<const char*>(&random_v), sizeof(random_v));
    auto ip = QHostAddress("127.0.0.1");
    if (cnt > 2) {
        cnt = 0;
    }
    socket_send.writeDatagram(datagram, ip, 30003);
}

