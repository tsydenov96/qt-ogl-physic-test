#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class SceneView;

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    MainWindow();
private:
    SceneView * m_sceneView;
};

#endif // MAINWINDOW_H
