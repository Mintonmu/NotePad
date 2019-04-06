#include "subtext.h"

SubText::SubText(QWidget *parent) : QTextEdit(parent)
{
    this->filename.clear();
    file = new QFile(this);
    isEdit = false;

}
void SubText::NewFile()
{
    static int index = 1;
    QString title = QString("未命名文档[%1][*]").arg(index);
    this->setWindowTitle(title);
    index++;
    connect(this->document(),&QTextDocument::contentsChange,this,&SubText::doPorcesscontentsChanged);
}
//////////////slot//////////////
void SubText::doPorcesscontentsChanged()
{
    isEdit = true;
    this->setWindowModified(true);
}

void SubText::OpenFile()
{
    QString filename =  QFileDialog::getOpenFileName(this,"获取文本文件",".","Text(*.cpp *.c *.h *.txt *.java)");
    if(filename.isEmpty())
    {
        return;
    }
    this->filename = filename;

    //    QStringList list = filename.split("/");
    //    //文件名
    //    QString tile = list[list.length()-1];
    //     this->setWindowTitle(tile);
    QFileInfo titleinfo(filename);
    QString title = QString("%1[*]").arg(titleinfo.fileName());
    this->setWindowTitle(title);
    file->setFileName(filename);
    bool ret = file->open(QIODevice::ReadOnly | QIODevice::ReadOnly);
    if(!ret)
    {
        QMessageBox::warning(this,"文件失败","打开文件失败");
        return;
    }
    QTextStream stream(file);
    stream.setCodec(this->codename.toLocal8Bit().data());
    QString str = stream.readAll();
    this->append(str);
    file->close();
    connect(this->document(),&QTextDocument::contentsChanged,this,&SubText::doPorcesscontentsChanged);

}
void SubText::SetCodeName(const QString codename)
{
    this->codename = codename;
}
int SubText::SaveFile()
{
    int ret = -1;
    if(!isEdit)
    {
        return ret;
    }

    if(this->filename.isEmpty())
    {
        QString filename = QFileDialog::getSaveFileName(this,"保存提示",".","Text(*.cpp *.c *.h *.txt *.java)");
        if(!filename.isEmpty())
        {
            this->filename = filename;
        }
        else
        {
            return ret;
        }
    }
    file->setFileName(this->filename);
    bool rest = file->open(QIODevice::WriteOnly | QIODevice::Text);
    if(!rest)
    {
        QMessageBox::warning(this,"失败提示","打开文件失败");
        return ret;
    }
    QTextStream stream(file);
    stream.setCodec(this->codename.toLocal8Bit().data());
    stream<<this->toPlainText();
    stream.flush();
    file->close();
    this->setWindowModified(false);
    QMessageBox::information(this,"成功提示","保存文件成功!");
    ret = 0;
    return ret;
}
void SubText::SaveAsFile()
{
//    isEdit = true;
    bool isedit = this->isEdit;
    this->isEdit = true;
    QString filenames = this->filename;
    this->filename.clear();
    int ret =  SaveFile();
    if(ret<0)
    {
        this->isEdit = isedit;
        this->filename = filename;
    }

}
void SubText::closeEvent(QCloseEvent *e)
{
    if(!isEdit)
    {
        return;
    }
    QMessageBox::StandardButton btn =  QMessageBox::information(this,"保存提示","你确定是否已经保存",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (btn == QMessageBox::Yes )
    {
        SaveFile();
        e->accept();

    }
    else if (btn == QMessageBox::No)
    {
        e->accept();
    }
    else if (btn == QMessageBox::Cancel)
    {
        e->ignore();
    }
}
