#ifndef VIBRATIONCLIENT_H
#define VIBRATIONCLIENT_H

#include <QObject>

class VibrationClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit VibrationClient(QObject* parent = nullptr);
    ~VibrationClient();

    static VibrationClient* self();

    bool enabled() const;
    void setEnabled(bool enabled);

signals:
    bool enabledChanged() const;

public slots:
    void on(long duration);

private:
    static VibrationClient* m_self;
    bool m_enabled = false;
};

#endif // VIBRATIONCLIENT_H
