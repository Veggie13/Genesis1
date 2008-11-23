#ifndef RESIZETABLEDLG_H
#define RESIZETABLEDLG_H

#include <QDialog>

#include "ResizeTableDlgUi.h"


class ResizeTableDlg : public QDialog, private Ui::ResizeTableDlgUi
{
    Q_OBJECT

public:
    ResizeTableDlg(int rows, int cols, QWidget* parent=NULL);
    virtual ~ResizeTableDlg();

public slots:
    virtual void accept();
    virtual void reject();

signals:
    void SizeChanged(int rows, int cols);

private:
    int m_rows;
    int m_cols;

};

#endif
