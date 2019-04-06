#ifndef SUBTEXT_H
#define SUBTEXT_H

#include <QWidget>
#include <QTextEdit>
#include <QTextDocument>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
class SubText : public QTextEdit
{
    Q_OBJECT
public:
    explicit SubText(QWidget *parent = nullptr);
    void NewFile();
    void OpenFile();
    void SetCodeName(const QString);
    int SaveFile();
    void SaveAsFile();
protected:
    void closeEvent(QCloseEvent *);
signals:
private slots:
    void doPorcesscontentsChanged();
public slots:
private:
    QString filename;
    QFile *file;
    QString codename;
    bool isEdit;
};

#endif // SUBTEXT_H
