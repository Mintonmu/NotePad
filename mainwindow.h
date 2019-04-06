#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subtext.h"
#include <QMdiSubWindow>
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
    void closeEvent(QCloseEvent *);
private slots:
    void doProcessNewTriggered(bool);
    void doProcessOpenTriggered(bool);
    void doProcessUTF8Triggered(bool);
    void doProcessGB2312Triggered(bool);
    void doProcessSaveTriggered(bool);
    void doPorcessSaveASTriggered(bool);
    void doPorcessExitTriggered(bool);
    void doPorcessCloseTriggered(bool);
    void doPorcessCloseTriggeredAll(bool);
    void doPorcessTileTriggered(bool);
    void doPorcessCasCadeTriggered(bool);
    void doPorcessRedoTriggered(bool);
    void doPorcessCopyTriggered(bool);
    void doPorcessCutTriggered(bool);
    void doPorcessPasteTriggered(bool);
    void doPorcessCancelTriggered(bool);

     SubText * getActiveChildForm();
private:
    Ui::MainWindow *ui;
    QString codename;
};

#endif // MAINWINDOW_H
