#ifndef OPENOPTIONSDLG_H
#define OPENOPTIONSDLG_H

#include <QDialog>

#include "OpenOptionsDlgUi.h"

class QStringList;


class OpenOptionsDlg : public QDialog, private Ui::OpenOptionsDlgUi
{
    Q_OBJECT

public:
    OpenOptionsDlg(const QStringList& recent, QWidget* parent = NULL);
    virtual ~OpenOptionsDlg();

signals:
    void OpenRecentSelected(const QString& filename);
    void OpenOtherSelected();
    void StartNewSelected();

protected slots:
    void OpenRecent();
    void OpenOther();
    void StartNew();

    void UpdateOpenRecentButton();

};

#endif
