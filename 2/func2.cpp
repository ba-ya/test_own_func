#include "func2.h"
#include "ui_func2.h"

func2::func2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::func2)
{
    ui->setupUi(this);
    socket.bind(QHostAddress::Any, 30003);
    connect(&socket, &QUdpSocket::readyRead, this, &func2::read_msg);

}

func2::~func2()
{
    delete ui;
}
#if 0
void func2::on_input_valueChanged(int check_falg)
{
    QByteArray data;
    data.append(reinterpret_cast<const char*>(&check_falg), sizeof(int));

    int out = data_to_int(data);
    ui->output->append(QString::number(out));
}
#endif

struct MessageHeader {
    uint8_t type{0x42};
    uint8_t flag{};
    uint16_t command{4};
    uint16_t length{};
    uint16_t req_id{};
};

void func2::read_msg()
{
    while (socket.hasPendingDatagrams())
    {
        QByteArray buffer;
        QHostAddress ip;
        buffer.resize(socket.pendingDatagramSize());
        socket.readDatagram(buffer.data(), buffer.size(), &ip);
        int type = data_to_int(buffer.mid(0, sizeof(int)));
        if (type < 0 || type > 2) {
            ui->output_1->setText(QString("Wrong type: %1").arg(type));
            return;
        }

        int cnt = buffer.size() / sizeof(int) - 1;
        QStringList pre_flag = {"rate", "heartbeat", "open device"};
        QString str = QString("--------%1: %2, cnt: %3\n").arg(type).arg(pre_flag[type]).arg(cnt);
        int offset = sizeof(int);
        for (int i = 0; i < cnt; i++) {
            auto out = data_to_int(buffer.mid(offset, sizeof(int)));
            offset += sizeof(int);
            str += QString::number(out) + "\n";

            uint16_t out_short = out;
            if (type == 1) {
                MessageHeader header;
                QByteArray datagram;
                QDataStream out(&datagram, QIODevice::WriteOnly);
                // out.setVersion(QDataStream::Qt_5_15);
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

int func2::data_to_int(QByteArray data)
{
    int out;
    memcpy(&out, data.constData(), sizeof(int));
    return out;
}

