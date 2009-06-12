#include <QStringList>

#include "OpenOptionsDlg.qoh"


OpenOptionsDlg::OpenOptionsDlg(const QStringList& recent, QWidget* parent)
:   QDialog(parent, Qt::WindowTitleHint)
{
    setupUi(this);

    m_openRecentBtn->setEnabled(false);

    if (recent.size() > 0)
        m_recentList->addItems(recent);
    else
        m_recentList->setEnabled(false);
    m_recentList->clearSelection();

    connect(m_openRecentBtn, SIGNAL( clicked() ), this, SLOT( OpenRecent() ));
    connect(m_openOtherBtn,  SIGNAL( clicked() ), this, SLOT( OpenOther()  ));
    connect(m_newProjectBtn, SIGNAL( clicked() ), this, SLOT( StartNew()   ));

    connect(m_recentList,   SIGNAL( itemSelectionChanged()   ),
            this,           SLOT  ( UpdateOpenRecentButton() ));
    connect(m_recentList,   SIGNAL( itemDoubleClicked(QListWidgetItem*) ),
            this,           SLOT  ( OpenRecent()                        ));
}

OpenOptionsDlg::~OpenOptionsDlg()
{
}

void OpenOptionsDlg::OpenRecent()
{
    QList<QListWidgetItem*> selection = m_recentList->selectedItems();
    if (selection.size() < 1)
        return;

    QString filename = selection[0]->data(Qt::DisplayRole).toString();

    accept();
    emit OpenRecentSelected(filename);
}

void OpenOptionsDlg::OpenOther()
{
    accept();
    emit OpenOtherSelected();
}

void OpenOptionsDlg::StartNew()
{
    accept();
    emit StartNewSelected();
}

void OpenOptionsDlg::UpdateOpenRecentButton()
{
    m_openRecentBtn->setEnabled(m_recentList->selectedItems().size() > 0);
}
