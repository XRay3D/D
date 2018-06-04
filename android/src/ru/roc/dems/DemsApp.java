package ru.roc.dems;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Vibrator;

public class DemsApp extends org.qtproject.qt5.android.bindings.QtActivity {
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static DemsApp m_instance;

    public DemsApp()
    {
        m_instance = this;
    }

    public static void notify(String s)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle("Сообщение от dEMS!");
            m_builder.setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE);
        }

        m_builder.setContentText(s);
        m_notificationManager.notify(1, m_builder./*getNotification*/ build());
    }

    public static void vibro(long mills)
    {
        if (mills == 0)
            mills = 1000L;
        Vibrator vibrator = (Vibrator)m_instance.getSystemService(Context.VIBRATOR_SERVICE);
        if (vibrator.hasVibrator()) {
            vibrator.vibrate(mills);
        }
    }

    //    @Override
    //    public void onResume()
    //    {
    //        if (isVoiceInteraction()) {
    //            String promt = "Are you sure?";
    //            getVoiceInterractor().submitRequessst(new Confirm(promt));
    //        }
    //    }
}
