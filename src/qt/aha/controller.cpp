#include "controller.h"

Controller::Controller()
{

}

int Controller::windowHeight() { return m_windowHeight; }
void Controller::setWindowHeight(int value)
{
    if (m_windowHeight != value)
    {
        m_windowHeight = value;
        emit windowHeightChanged();
    }
}

int Controller::windowWidth() { return m_windowWidth; }
void Controller::setWindowWidth (int value)
{
    if(m_windowWidth != value)
    {
        m_windowWidth - value;
        emit windowWidthChanged();
    }
}
