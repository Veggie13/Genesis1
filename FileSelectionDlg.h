#ifndef FILESELECTIONDLG_H
#define FILESELECTIONDLG_H

#include <QDialog>
#include <QStringList>

#include "QStringMapRefModel.hpp"

#include "FileSelectionDlgUi.h"


class FileSelectionDlg : public QDialog, private Ui::FileSelectionDlgUi
{
    Q_OBJECT

public:
    FileSelectionDlg(QWidget* parent=NULL);
    virtual ~FileSelectionDlg();

    void AddFile(const QString& title, const QString& filename);
    void DeleteFile(const QString& title);

    const QMap<QString, QString>& GetFileMap();

public slots:
    QString     ExecSingleSelection();
    QStringList ExecMultiSelection();
    int         ExecNoSelection();

    virtual void reject();

signals:
    void ImportRequested(const QString& title, const QString& filename);
    void DeleteRequested(const QString& title);
    void RenameRequested(const QString& title, const QString& newTitle);

private slots:
    void ImportFiles();
    void DeleteSelectedFiles();
    void RenameSelectedFiles();
    void ReimportSelectedFiles();

private:
    bool GetTitleForFile(const QString& filename, QString& title);


    QMap<QString, QString>      m_fileMap;
    QStringMapRefModel<QString> m_fileMapModel;

};

#endif
