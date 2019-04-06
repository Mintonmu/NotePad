#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("NotePad");
    this->resize(800,600);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Init()
{
    codename = "UTF-8";
    connect(ui->actionnew_file,&QAction::triggered,this,&MainWindow::doProcessNewTriggered);
    connect(ui->actionopen_file,&QAction::triggered,this,&MainWindow::doProcessOpenTriggered);
    connect(ui->actionUTF_8,&QAction::triggered,this,&MainWindow::doProcessUTF8Triggered);
    connect(ui->actionUnicode,&QAction::triggered,this,&MainWindow::doProcessUTF8Triggered);
    connect(ui->actionsave,&QAction::triggered,this,&MainWindow::doProcessSaveTriggered);
    connect(ui->actionsaveother,&QAction::triggered,this,&MainWindow::doPorcessSaveASTriggered);
    connect(ui->actionexit,&QAction::triggered,this,&MainWindow::doPorcessExitTriggered);
    connect(ui->actionclose,&QAction::triggered,this,&MainWindow::doPorcessCloseTriggered);
    connect(ui->actioncloseall,&QAction::triggered,this,&MainWindow::doPorcessCloseTriggeredAll);
    connect(ui->actionTile,&QAction::triggered,this,&MainWindow::doPorcessTileTriggered);
    connect(ui->actionCascading,&QAction::triggered,this,&MainWindow::doPorcessCasCadeTriggered);
    connect(ui->actionrestore,&QAction::triggered,this,&MainWindow::doPorcessRedoTriggered);
    connect(ui->actioncopy,&QAction::triggered,this,&MainWindow::doPorcessCopyTriggered);
    connect(ui->actionScrapbooking,&QAction::triggered,this,&MainWindow::doPorcessCutTriggered);
    connect(ui->actionpaster,&QAction::triggered,this,&MainWindow::doPorcessPasteTriggered);
    connect(ui->actionback,&QAction::triggered,this,&MainWindow::doPorcessCancelTriggered);

    connect(ui->actionnext,&QAction::triggered,this,[=](){
        ui->mdiArea->activateNextSubWindow();
    });
    connect(ui->actionprev,&QAction::triggered,this,[=](){
        ui->mdiArea->activatePreviousSubWindow();
    });
    connect(ui->actionabout,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"About Author","This notepad designed by MinTon");
    });
    connect(ui->actionabout_qt,&QAction::triggered,this,[=](){
        QMessageBox::aboutQt(this);
    });

}
SubText *MainWindow::getActiveChildForm()
{
    SubText * sub = nullptr;
    QMdiSubWindow *subwin = ui->mdiArea->activeSubWindow();
    if(subwin == nullptr) return sub;
    QWidget *wid = subwin->widget();
    if(wid == nullptr) return sub;
    sub = static_cast<SubText*>(wid);
    return sub;
}
void MainWindow::doProcessNewTriggered(bool flag)
{
    SubText * subtext = new SubText();
    ui->mdiArea->addSubWindow(subtext);
    subtext->SetCodeName(codename);
    subtext->NewFile();
    subtext->show();
}
void MainWindow::doProcessOpenTriggered(bool flag)
{
    SubText * subtext = new SubText();
    ui->mdiArea->addSubWindow(subtext);
    subtext->SetCodeName(codename);
    subtext->OpenFile();
    subtext->show();
}
void MainWindow::doProcessUTF8Triggered(bool flag)
{
    this->codename = "UTF-8";
}
void MainWindow::doProcessGB2312Triggered(bool flag)
{
    this->codename ="GB18030";
}
void MainWindow::doProcessSaveTriggered(bool flag)
{
    QMdiSubWindow * subwin =   ui->mdiArea->activeSubWindow();
    if(subwin == nullptr)
    {
        return;
    }
    QWidget *wid = subwin->widget();
    if(wid == nullptr) return;
    SubText *sub = static_cast<SubText *>(wid);
    if(sub == nullptr) return;
    sub->SaveFile();
}
void MainWindow::doPorcessSaveASTriggered(bool flag)
{
    QMdiSubWindow * subwin =   ui->mdiArea->activeSubWindow();
    if(subwin == nullptr)
    {
        return;
    }
    QWidget *wid = subwin->widget();
    if(wid == nullptr) return;
    SubText *sub = static_cast<SubText *>(wid);
    if(sub == nullptr) return;
    sub->SaveAsFile();
    sub->close();

}
void MainWindow::closeEvent(QCloseEvent* e)
{
    doPorcessExitTriggered(false);

}
void MainWindow::doPorcessExitTriggered(bool flag)
{
    ui->mdiArea->closeAllSubWindows();
    this->close();
}
void MainWindow::doPorcessCloseTriggered(bool flag)
{
    ui->mdiArea->closeActiveSubWindow();
}
void MainWindow::doPorcessCloseTriggeredAll(bool flag)
{
    ui->mdiArea->closeAllSubWindows();
}
void MainWindow::doPorcessTileTriggered(bool flag)
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::doPorcessCasCadeTriggered(bool flag)
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::doPorcessRedoTriggered(bool flag)
{
    SubText * sub = getActiveChildForm();
    if(sub == nullptr)sub->redo();
}

void MainWindow::doPorcessCopyTriggered(bool flag)
{
    SubText * sub = getActiveChildForm();
    if(sub == nullptr)sub->copy();
}
void MainWindow::doPorcessCutTriggered(bool flag)
{
    SubText * sub = getActiveChildForm();
    if(sub == nullptr)sub->cut();
}
void MainWindow::doPorcessPasteTriggered(bool flag)
{
    SubText * sub = getActiveChildForm();
    if(sub == nullptr)sub->paste();
}
void MainWindow::doPorcessCancelTriggered(bool flag)
{
    SubText * sub = getActiveChildForm();
    if(sub == nullptr)sub->undo();
}
