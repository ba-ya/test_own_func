#ifndef PARAMETER_TOF_JSON_H
#define PARAMETER_TOF_JSON_H

#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QMap>
#include <qjsonarray.h>
#include <qjsonobject.h>
// #include "tb_hal_pa_config.h"

namespace tb::hal {
struct LawInfo
{
    int elem_max_time{};
    int elem_min_time{};

    std::vector<int32_t> elem_time{};
    std::vector<int32_t> tx_delays{};
    std::vector<int32_t> rx_delays{};
};
}
struct TofJsonManger {
    bool completed() {
        // join part
        QByteArray json_data;
        for (auto &data : data_parts) {
            json_data.append(data);
        }
        // save as file
        auto doc = QJsonDocument::fromJson(json_data);
        save_to_file("./tof_recv.json", doc);
        // store
        if (!doc.isObject()) {
            qWarning() << "Invalid JSON format";
            return false;
        }
        auto root = doc.object();
        for (auto group_it = root.begin(); group_it != root.end(); ++group_it) {
            auto group_id = get_id(group_it.key());
            auto group_obj = group_it.value().toObject();
            QMap<int, tb::hal::LawInfo> laws;
            for (auto beam_it = group_obj.begin(); beam_it != group_obj.end(); ++beam_it) {
                auto beam_id = get_id(beam_it.key());
                auto beam_array = beam_it.value().toArray();
                QMap<int, int> tofs;
                auto min_value = std::numeric_limits<int>::max();
                auto max_value = std::numeric_limits<int>::min();
                for (auto id_trans_it = beam_array.begin(); id_trans_it != beam_array.end(); ++id_trans_it) {
                    auto id_trans_obj = id_trans_it->toObject();
                    for (auto id_trans = id_trans_obj.begin(); id_trans != id_trans_obj.end(); ++id_trans) {
                        auto trans_id = get_id(id_trans.key());
                        auto tof = id_trans.value().toInt();
                        tofs[trans_id] = tof;
                        if (tof > max_value)
                            max_value = tof;
                        if (tof < min_value)
                            min_value = tof;
                    }

                }
                tb::hal::LawInfo law;
                for (auto tof_it = tofs.cbegin(); tof_it != tofs.cend(); ++tof_it) {
                    law.elem_time.push_back(tof_it.value());
                }
                law.elem_min_time = min_value;
                law.elem_max_time = max_value;
                laws[beam_id] = law;
            }
            law_infos[group_id] = laws;
        }
#if 1
        for (auto it = law_infos.cbegin(); it != law_infos.cend(); ++it) {
            auto group_id = it.key();
            qDebug() << "------------group_id" << group_id;
            auto rst = get_law_infos(group_id);
            int i = 0;
            for (auto &tofs : rst) {
                qDebug() << "------------beam_id" << i++;
                qDebug() << "max:" << tofs.elem_max_time << "min" << tofs.elem_min_time;
                qDebug() << tofs.elem_time;
            }
        }
#endif

        return true;
    }

    void push_data(int id, QByteArray& data) {
        data_parts[id] = data;
    }

    std::vector<tb::hal::LawInfo> get_law_infos(int group_id) {
        if (!law_infos.contains(group_id)) {
            return {};
        }
        auto laws = law_infos[group_id];
        std::vector<tb::hal::LawInfo> rst_laws;
        for (auto &law : laws) {
            rst_laws.push_back(law);
        }
        return rst_laws;
    }

private:
    bool save_to_file(const QString &file_path, QJsonDocument &doc) {
        QFile file(file_path);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson(QJsonDocument::Indented));
        } else {
            qWarning() << "Failed to open file for writing!";
            return false;
        }
        return true;
    }

    int get_id(const QString &key) {
        return key.split(" ").last().toInt();
    }

private:
    QMap<int, QByteArray> data_parts;
    QMap<int, QMap<int, tb::hal::LawInfo>> law_infos;

};


#endif // PARAMETER_TOF_JSON_H
