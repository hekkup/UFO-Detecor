/*
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

#ifndef DIALOG_H
#define DIALOG_H

#include "config.h"
#include <QDialog>
#include <opencv2/opencv.hpp>
#include "graphicsscene.h"

class Camera;

namespace Ui {
class DetectionAreaEditDialog;
}

/**
 * @brief Dialog for the detection area selection
 *
 * @todo save detection area as polygon: only save the corner points. Then can edit, re-edit, scale etc. more freely.
 */
class DetectionAreaEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetectionAreaEditDialog(QWidget *parent = 0, Camera *camPtr = 0, Config *configPtr = 0);
    ~DetectionAreaEditDialog();

private slots:
    void on_buttonTakePicture_clicked();
    void on_buttonSave_clicked();
    void on_buttonConnect_clicked();
    void on_buttonClear_clicked();

private:
    Ui::DetectionAreaEditDialog *ui;
    Camera *cameraPtr;
    Config *m_config;
    GraphicsScene *scene;

    /**
     * Get all points inside the selected area and pass vector with points to savePointsAsXML()
     */
    void getPointsInContour(std::vector<cv::Point2f> & contour);

    /**
     * Save the points to area xml
     */
    void savePointsAsXML(std::vector<cv::Point2f> & contour);
    int WIDTH;
    int HEIGHT;
    std::string areaFilePath;
    bool isPictureTaken;
    bool wasSaved;
    void closeEvent(QCloseEvent *);


signals:
    //void savedFile();

};

#endif // DIALOG_H
