#include "camera.h"

Camera::Camera()
{
    this->pictureRepositoryPath = "/home/pi/Pictures/GreenHouse_Pictures/%d" ;
}

void Camera::takePicture()
{
    // Command terminal : raspistill -o ~/Camera/image.jpg -q 100
    QProcess::execute("raspistill -o " + this->pictureRepositoryPath + " -q 100 -dt -w 200 -h 200");
    qDebug("Taking picture");
}

void Camera::makeGIF()
{
    QProcess::execute("python /home/pi/Pictures/createGIF.py");
    qDebug("Creating GIF");
}

void Camera::run()
{
    exec();
}

int Camera::exec()
{
    QDate firstDate = QDate::currentDate();
    QDate currentDate ;
    QTime currentTime ;
    while(1)
    {
        // Taking pictures each day at 12
        currentDate = QDate::currentDate();
        currentTime = QTime::currentTime();
        qDebug("First date = %d | Current date = %d | Current hour = %d",firstDate.dayOfWeek(),currentDate.dayOfWeek(),currentTime.hour());
        if((firstDate.dayOfWeek() != currentDate.dayOfWeek()) && currentTime.hour() == 12)
        {
            firstDate = currentDate ;
            this->takePicture();
            this->makeGIF();
            emit updateGIF();
        }
        // Waiting one hour
        sleep(3600);
    }
    return 0 ;
}
