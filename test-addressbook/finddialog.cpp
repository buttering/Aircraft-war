#include "finddialog.h"
#include <QLabel>
#include <QHBoxLayout>

FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Enter the name of a contact:"));

    lineEdit = new QLineEdit;
    findButton = new QPushButton("find");
    findText = "";

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findButton);

    setLayout(layout);
    setWindowTitle(tr("Find a Contact"));

    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(findButton,SIGNAL(clicked()),this,SLOT(accept())); // 。QDialog 提供的 accept() 槽会隐藏对话框并将结果代码设置为 Accepted
}

void FindDialog::findClicked(){
    QString text = lineEdit->text();

    if(text.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"),tr("Please enter a name."));
        return;
    }else{
        findText = text;
        lineEdit->clear();
        hide();
    }
}

// findText 的 getter
void FindDialog::getFindText(){
    return findText;
}
