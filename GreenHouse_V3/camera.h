#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QDate>

namespace Ui {
class Camera;
}

class Camera :public QThread
{
    Q_OBJECT
public:
    // Attributes
    QString pictureRepositoryPath ;
    QString currentDateTime ;

    // Methods
    Camera();
    void takePicture();
    void makeGIF();
    // QThread methods
    void run();
    int exec();

signals :
    void updateGIF(void);
};

#endif // CAMERA_H
