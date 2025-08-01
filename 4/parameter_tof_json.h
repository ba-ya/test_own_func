#ifndef PARAMETER_TOF_JSON_H
#define PARAMETER_TOF_JSON_H

#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QMap>
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
        save_to_file("./tof.json", doc);
        // store
        if (!doc.isObject()) {
            qWarning() << "Invalid JSON format";
            return false;
        }
        auto &&check_size = [](const QJsonObject &obj) {
            std::vector<int> cnts;
            for (auto &key : obj.keys()) {
                auto sub_obj = obj[key].toObject();
                cnts.push_back(sub_obj.count());
            }
            std::sort(cnts.begin(), cnts.end());
            return cnts.front() == cnts.back();
        };
        auto &&check_continuity = [this](QStringList keys) {
            std::vector<int> values;
            for (auto &key : keys) {
                auto id  = get_id(key);
                values.push_back(id);
            }
            // sort
            std::sort(values.begin(), values.end());
            bool flag = true;
            for (int i = 0; i < values.size() - 1; ++i) {
                if (values[i + 1] - values[i] != 1) {
                    flag = false;
                    break;
                }
            }
            return flag;
        };

        auto root = doc.object();
        for (auto &key : root.keys()) {
            QMap<int, tb::hal::LawInfo> laws;
            auto group_obj = root[key].toObject();
            if (!check_size(group_obj)) {
                qDebug() << "apeture not equel";
                return false;
            }
            for (auto &beam_key : group_obj.keys()) {
                auto beam_obj = group_obj[beam_key].toObject();
                if (!check_continuity(beam_obj.keys())) {
                    qDebug() << "id trans not continuous";
                    return false;
                }
                QMap<int, int> tofs;
                auto min_value = std::numeric_limits<int>::max();
                auto max_value = std::numeric_limits<int>::min();
                for (auto &trans_key : beam_obj.keys()) {
                    auto trans_id = get_id(trans_key);
                    auto tof = beam_obj[trans_key].toInt();
                    tofs[trans_id] = tof;
                    if (tof > max_value)
                        max_value = tof;
                    if (tof < min_value)
                        min_value = tof;
                }
                tb::hal::LawInfo law;
                for (auto &v : tofs.values()) {
                    law.elem_time.push_back(v);
                }
                law.elem_min_time = min_value;
                law.elem_max_time = max_value;
                auto beam_id = get_id(beam_key);
                laws[beam_id] = law;
            }
            auto id = get_id(key);
            law_infos[id] = laws;
        }
        for (auto &id : law_infos.keys()) {
            qDebug() << "------group_id" << id;
            auto rst = get_law_infos(id);
            int i = 0;
            for (auto &tofs : rst) {
                qDebug() << "------beam_id" << i++;
                qDebug() << "max:" << tofs.elem_max_time << "min" << tofs.elem_min_time;
                qDebug() << tofs.elem_time;
            }
        }

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
