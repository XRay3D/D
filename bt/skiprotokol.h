#ifndef MYPROTOKOL_H
#define MYPROTOKOL_H

#include <QByteArray>
#include <stdint.h>

namespace Ski {

enum COMMAND {
    //Service functions
    PING, // return SOFTWARE_VERSION
    //User functions
    SET_GET_RF_SETTINGS,
    SET_GET_STIMULATION_SETTINGS,
    SET_GET_STATISTICS, //Statistics
    SET_GET_DATE_TIME,
    GET_BATTERY, //left + right
    GET_ACC_GYR, //AccGyr
    GET_STATUS,
    IMPULSE,
    ON_OFF,
    //Service functions
    BUFFER_OVERFLOW,
    WRONG_COMMAND,
    TEXTUAL_PARCEL, //for debug (may be)
    CRC_ERROR,
};

enum AccGyr {
    OFF,
    ON,
    SINGLE,
};

enum Statistics {
    RESET,
    GET_TRAINING,
    GET_PAUSE,
};

#pragma pack(push, 1)

typedef struct RfSettings_t {
    uint8_t channel;
    uint8_t address;
} RfSettings_t;

typedef struct Battery_t {
    uint8_t left;
    uint8_t right;
} Battery_t;

typedef struct StimulationSettings_t {
    uint8_t voltage;
    uint16_t duration;
    uint16_t delay;
    //int16_t leadTime;
} StimulationSettings_t;

typedef struct AccGyr_t {
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

typedef struct Statistics_t {
    uint32_t timePause;
    uint32_t timeStimulatiion;
    float averageAmplitude;
    uint16_t steps;
} Statistics_t;

typedef struct SysInfo_t { //STATUS// считать состояния чипов, напряжения, версию прошивки
    uint8_t acc;
    uint8_t gyr;
    uint8_t rf;
    uint8_t battery_voltage;
    uint8_t impulse_voltage;
    uint8_t nLeft_right;
    uint8_t version;
} SysInfo_t;

typedef struct DateTime_t {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t dom;
} DateTime_t;

typedef struct Parcel_t {
    quint16 start;
    quint8 len;
    quint8 cmd;
    quint8 data[1];
} Parcel_t;

#pragma pack(pop)

enum {
    TX = 0xAA55,
    RX = 0x55AA,
    MIN_LEN = 5
};

class Protokol {
public:
    explicit Protokol();
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

    template <typename T>
    T value(const QByteArray& data) const { return *reinterpret_cast<const T*>(data.constData() + 4); }

    template <typename T>
    T pValue(const QByteArray& data) const { return reinterpret_cast<const T*>(data.constData() + 4); }

    QByteArray parcel(quint8 cmd);

    bool checkParcel(const QByteArray& data);

    quint8 calcCrc(const QByteArray& data);

private:
    enum { POLYNOMIAL = 0x1D }; // x^8 + x^4 + x^3 + x^2 + 1
    static const uint8_t array[0x100];
};
}

#endif // MYPROTOKOL_H
