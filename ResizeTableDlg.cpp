#include "ResizeTableDlg.qoh"


ResizeTableDlg::ResizeTableDlg(int rows, int cols, QWidget* parent)
:   QDialog(parent),
    m_rows(rows),
    m_cols(cols)
{
    setupUi(this);

    m_rowSpin->setValue(m_rows);
    m_colSpin->setValue(m_cols);
}

ResizeTableDlg::~ResizeTableDlg()
{
}

void ResizeTableDlg::accept()
{
    if ( (m_rows != m_rowSpin->value()) ||
         (m_cols != m_colSpin->value()) )
    {
        m_rows = m_rowSpin->value();
        m_cols = m_colSpin->value();

        emit SizeChanged(m_rows, m_cols);
    }

    QDialog::accept();
}

void ResizeTableDlg::reject()
{
    m_rowSpin->setValue(m_rows);
    m_colSpin->setValue(m_cols);

    QDialog::reject();
}
