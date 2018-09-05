#include "tcTextToSpeech.h"

#if defined(Q_OS_WIN)
#include <QAxObject>
#include <qt_windows.h>
#endif

void TcTextToSpeech::play(const QString& text)
{
  #if defined(Q_OS_WIN)
    CoInitialize(NULL);
    QAxObject speak("SAPI.SpVoice");
    speak.dynamicCall("Speak(QString)", text);
    CoUninitialize();
  #endif
}

void TcTextToSpeech::playing(const QString& text)
{
    m_mutex.lock();
    m_sounds.append(text);
    m_mutex.unlock();

    if ( ! isRunning() )
    {
        start(QThread::LowestPriority);
    }
}

void TcTextToSpeech::run()
{
    for(;;)
    {
        QString sound;
        m_mutex.lock();
        if ( ! m_sounds.isEmpty() )
        {
            sound = m_sounds.takeFirst();
        }
        m_mutex.unlock();

        if ( ! sound.isEmpty() )
        {
            play(sound);
        }
    }
}
