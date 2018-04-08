#ifndef MYPROTOKOL_H
#define MYPROTOKOL_H

#include <QByteArray>
#include <stdint.h>

namespace Ski {
enum COMMAND {
    //Service functions
    PING, // return SOFTWARE_VERSION
    //User functions
    IMPULSE,
    //
    GET_SETTINGS,
    SET_SETTINGS,
    //
    GET_STATISTICAL,
    //
    SET_SNIFFER_MODE,
    SET_SLEEP_MODE,
    //
    GET_SYSTEM_INFO,
    GET_ACC_AND_GYR_DATA,
    //
    GET_LEVEL_AND_DURATION_OF_STIMULATION,
    SET_LEVEL_AND_DURATION_OF_STIMULATION,
    //
    GET_RF_SETTINGS,
    SET_RF_SETTINGS,
    //
    GET_DATE,
    SET_DATE,
    //
    GET_PWM_AND_DURATION,
    SET_PWM_AND_DURATION,
    //Service functions
    BUFFER_OVERFLOW,
    WRONG_COMMAND,
    TEXTUAL_PARCEL, //for debug (may be)
    CRC_ERROR,
};

enum {
    POWER_OFF,
    POWER_ON,
};

enum SETTINGS {
    POWER,
    IMPULSE_AMPLITUDE, //1.2. Параметры импульса1.2.1. Установить амплитуду импульса (десятичное, Вольты)
    DURATION, //1.3. Продолжительность стимуляции 1.3.1. Целое число в мс от 100 до 300 мс
    LEAD_TIME, //1.4. Опережение включения/выключения момента стимуляции,//1.4.1. Знаковое целое, кол-во миллисекунд от -50 до 50 мс.
};

enum STATISTICAL {
    LEFT_BATTERY_CHARGE, //	2.1. Напряжение батареи 2 шт (левая и правая нога) (% заряда 0...100)
    RIGHT_BATTERY_CHARGE, //	2.1. Напряжение батареи 2 шт (левая и правая нога) (% заряда 0...100)
    SOFTWARE_VERSION, //	2.2. Версия ПО 1 шт. (строка)
    TIME_OF_PURE_STIMULATION, //	2.3. Время чистой стимуляции (секунды)
    AVERAGE_AMPLITUDE_OF_STIMULATION, //	2.4. Средняя амплитуда стимуляции (Вольты) - потом
    PURE_TRAINING_TIME_WITHOUT_PAUSES, //	2.5. Чистое время тренировки без пауз (секунды)
    TOTAL_TRAINING_TIME, //	2.6. Общее время тренировки (секунды)
    TOTAL_PAUSE_TIME, //	2.7. Общее время пауз (секунды)
    AVERAGE_FREQUENCY_OF_STEPS, //	2.9. Средняя частота шагов при стимуляции ??? (если нетрудоёмко)
};
#pragma pack(push, 1)

typedef struct Settings_t { // считать состояния чипов, напряжения, версию прошивки
    uint8_t power;
    uint16_t impulseAmplitude;
    uint16_t duration;
    int16_t leadTime;
} Settings_t;

typedef struct SettingsData_t {
    uint8_t type; //SKI_SETTINGS or SKI_STATISTICAL
    int16_t value;
} SettingsData_t;

typedef struct SysInfo_t { // считать состояния чипов, напряжения, версию прошивки
    uint8_t accelerometer;
    uint8_t gyroscope;
    uint8_t rf;
    uint8_t battery_voltage;
    uint8_t impulse_voltage;
    uint8_t master;
    uint8_t version;
} SysInfo_t;

typedef struct AccGyr_t { // считать состояния чипов, напряжения, версию прошивки
    struct {
        int8_t x;
        int8_t y;
        int8_t z;
    } acc;
    struct {
        int8_t x;
        int8_t y;
        int8_t z;
    } gyr;
} AccGyr_t;

typedef struct RfSettings_t { // считать состояния чипов, напряжения, версию прошивки
    uint8_t freq0;
    uint8_t freq1;
    uint8_t freq2;
    uint8_t testb;
    uint8_t channel;
    uint8_t address;
} RfSettings_t;

typedef struct Date_t { // считать состояния чипов, напряжения, версию прошивки
    uint16_t year;
    uint8_t month;
    uint8_t dom;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Date_t;

typedef struct PwmDuration_t { // считать состояния чипов, напряжения, версию прошивки
    uint8_t pwm;
    uint8_t duration;
} PwmDuration_t;

typedef struct Statistical_t { // считать состояния чипов, напряжения, версию прошивки
    uint8_t leftBatteryCharge; //	2.1. Напряжение батареи 2 шт (левая и правая нога) (% заряда 0...100)
    uint8_t rightBatteryCharge; //	2.1. Напряжение батареи 2 шт (левая и правая нога) (% заряда 0...100)
    uint8_t softwareVersion; //	2.2. Версия ПО 1 шт. (строка)
    uint16_t timeOfPureStimulation; //	2.3. Время чистой стимуляции (секунды)
    uint8_t averageAmplitudeOfStimulation; //	2.4. Средняя амплитуда стимуляции (Вольты) - потом
    uint16_t pureTrainingTimeWithoutPauses; //	2.5. Чистое время тренировки без пауз (секунды)
    uint16_t totalTrainingTime; //	2.6. Общее время тренировки (секунды)
    uint16_t totalPauseTime; //	2.7. Общее время пауз (секунды)
    uint8_t averageFrequencyOfSteps; //	2.9. Средняя частота шагов при стимуляции ??? (если нетрудоёмко)
} Statistical_t;

typedef struct Parcel_t {
public:
    quint16 start;
    quint8 len;
    quint8 cmd;
    quint8 data[32];
} Parcel_t;

#pragma pack(pop)

enum {
    TX = 0xAA55,
    RX = 0x55AA,
    MIN_LEN = 5
};

class Protokol {
public:
    template <typename T>
    QByteArray parcel(quint8 cmd, const T& value)
    {
        QByteArray data(MIN_LEN + sizeof(T), 0);
        Parcel_t* d = reinterpret_cast<Parcel_t*>(data.data());
        memcpy(d->data, &value, sizeof(T));
        d->start = TX;
        d->len = data.size();
        d->cmd = cmd;
        d->data[sizeof(T)] = calcCrc(data); //crc
        return data;
    }

    QByteArray parcel(quint8 cmd)
    {
        QByteArray data(MIN_LEN, 0);
        Parcel_t* d = reinterpret_cast<Parcel_t*>(data.data());
        d->start = TX;
        d->len = MIN_LEN;
        d->cmd = cmd;
        d->data[0] = calcCrc(data); //crc
        return data;
    }

    bool checkParcel(const QByteArray& data)
    {
        const Parcel_t* d = reinterpret_cast<const Parcel_t*>(data.constData());
        if (data.size() >= MIN_LEN) {
            if (d->start == RX) {
                if (d->len == data.size()) {
                    if (d->data[d->len - MIN_LEN] == calcCrc(data)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    quint8 calcCrc(const QByteArray& data)
    {
        quint8 crc8 = 0;
        for (uint16_t i = 0, len = data.size() - 1; i < len; ++i) {
            crc8 ^= data[i];
            for (quint8 j = 0; j < 8; ++j) {
                crc8 = (crc8 & 0x80) ? (crc8 << 1) ^ POLYNOMIAL : crc8 << 1;
            }
        }
        return crc8;
    }

private:
    enum { POLYNOMIAL = 0x1D }; // x^8 + x^4 + x^3 + x^2 + 1
};
}

#endif // MYPROTOKOL_H
