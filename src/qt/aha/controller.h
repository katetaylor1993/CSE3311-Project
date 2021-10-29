#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller: public QObject
{
    // This macro allows you to access the values from this class in qml. Make sure you set up READ WRITE
    // and NOTIFY methods later in the class definition (in .h and .cpp)
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setwindowHeight NOTIFY windowHeightChanged)
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setwindowWidth NOTIFY windowWidthChanged)

    // Singleton pattern stuff. No touchy.
private:
    Controller();
    static Controller * obj;

public:
    static Controller * getInstance()
    {
        if(obj == nullptr)
        {
            obj = new Controller();
        }
        return obj;
    }

    // Class stuff. Have fun
private:
    int m_windowHeight;
    int m_windowWidth;

public:
    int windowHeight(void);
    void setWindowHeight(int value);

    int windowWidth(void);
    void setWindowWidth(int value);

signals:
    void windowHeightChanged(void);
    void windowWidthChanged(void);
};

#endif // CONTROLLER_H
