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
    uint8_t channel = 0;
    uint8_t address = 0;
} RfSettings_t;

typedef struct Battery_t {
    uint8_t left = 0;
    uint8_t right = 0;
} Battery_t;

typedef struct StimulationSettings_t {
    uint8_t voltage = 0;
    uint16_t duration = 0;
    uint16_t delay = 0;
    //int16_t leadTime;
} StimulationSettings_t;

typedef struct AccGyr_t {
    struct {
        int8_t x = 0;
        int8_t y = 0;
        int8_t z = 0;
    } acc;
    struct {
        int8_t x = 0;
        int8_t y = 0;
        int8_t z = 0;
    } gyr;
} AccGyr_t;

typedef struct Statistics_t {
    uint32_t timePause = 0;
    uint32_t timeStimulatiion = 0;
    float averageAmplitude = 0;
    uint16_t steps = 0;
} Statistics_t;

typedef struct SysInfo_t { //STATUS// считать состояния чипов, напряжения, версию прошивки
    uint8_t acc = 0;
    uint8_t gyr = 0;
    uint8_t rf = 0;
    uint8_t battery_voltage = 0;
    uint8_t impulse_voltage = 0;
    uint8_t nLeft_right = 0;
    uint8_t version = 0;
} SysInfo_t;

typedef struct DateTime_t {
    uint16_t year = 0;
    uint8_t month = 0;
    uint8_t day = 0;
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;
    uint8_t dom = 0;
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
        d->len = static_cast<quint8>(data.size());
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
