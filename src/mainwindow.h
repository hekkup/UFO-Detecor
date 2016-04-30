#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * UFO Detector | www.UFOID.net
 *
 * Copyright (C) 2016 UFOID
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QMainWindow>
#include "actualdetector.h"
#include "config.h"
#include <QModelIndex>
#include <QDomDocument>
#include <QFile>
#include <messageupdate.h>


namespace Ui {
class MainWindow;
}

class QNetworkReply;
class Camera;
class SettingsDialog;
class QNetworkAccessManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Camera *cameraPtr = 0, Config *configPtr = 0);
    ~MainWindow();
    void addOutputText(QString msg);
    bool getCheckboxState();
    void setSignalsAndSlots(ActualDetector *ptrDetector);

private:
    Ui::MainWindow *ui;
    SettingsDialog *settingsDialog;
    ActualDetector* theDetector;
    MessageUpdate* updateWindow;
    std::atomic<bool> isUpdating;
    std::atomic<bool> isRecording;
    std::atomic<bool> lastWasPositive, lastWasInfo;    
    bool isDetecting;
    int counterPositive_, counterNegative_, recordingCounter_;
    cv::Mat webcamFrame;
    Camera* CamPtr;
    std::unique_ptr<std::thread> threadWebcam;
    cv::Size displayResolution;
    QList<int> m_allowedWebcamAspectRatios; ///< currently allowed webcam aspect ratios

    Config* m_config;

    QDomDocument documentXML;
    QFile logFile;  ///< log file (XML)
    QString programVersion;
    QNetworkAccessManager *manager;

    void updateWebcamFrame();
    bool checkAndSetResolution(const int WIDTH, const int HEIGHT);
    void initializeStylesheet();

    /**
     * @brief readLogFileAndGetRootElement Read logfile containing existing video info
     */
    void readLogFileAndGetRootElement();

    /**
     * @brief checkDetectionAreaFile Check detection area file and create if doesn't exist
     */
    void checkDetectionAreaFile();
    bool checkCameraAndCodec(const int WIDTH, const int HEIGHT, const int CODEC);

    /**
     * Check that the folder for the images and videos exist
     */
    void checkFolders();
    void on_stopButton_clicked();

signals:
    void elementWasRemoved();
    void updatePixmap(QImage img);


public slots:
    void recordingWasStarted();
    void recordingWasStoped();
    void on_progressBar_valueChanged(int value);
	void update_output_text(QString msg);
    void displayPixmap(QImage img);

private slots:
    void on_startButton_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_buttonClear_clicked();
    void on_sliderNoise_sliderMoved(int position);
    void on_settingsButton_clicked();
    void on_recordingTestButton_clicked();
    void playClip();
    void deletingFileAndRemovingItem();
    void createUploadWindow();
    void setPositiveMessage();
    void setNegativeMessage();
    void setErrorReadingDetectionAreaFile();
    void updateWidgets(QString filename, QString datetime, QString videoLength);
    void on_aboutButton_clicked();
    void checkForUpdate(QNetworkReply* reply);

    void on_buttonImageExpl_clicked();
    void on_sliderThresh_sliderMoved(int position);
    void on_toolButtonNoise_clicked();
    void on_toolButtonThresh_clicked();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
