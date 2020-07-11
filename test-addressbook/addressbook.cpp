#include "addressbook.h"
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
AddressBook::AddressBook(QWidget *parent):QWidget(parent)
{
    //声明并通过实例来表示两个局部QLabel 对象
    QLabel *nameLabel = new QLabel("Name:");  // 头文件不必包含要使用的 QLabel 对象的声明，这是因为在创建这些对象后我们不 必对其进行引用
    QLabel *addressLabel = new QLabel("Address:");

    nameLine = new QLineEdit;
    addressText = new QTextEdit;
    addButton = new QPushButton("add");
    submitButton = new QPushButton("submit");
    cancelButton = new QPushButton("cancel");
    nextButton = new QPushButton("next");
    previoutButton = new QPushButton("previous");
    editButton = new QPushButton(tr("&Edit"));
    removeButton = new QPushButton(tr("&Remove"));
    findButton = new QPushButton("find");
    dialog = new FindDialog;

    nameLine->setReadOnly(true);
    addressText->setReadOnly(true);
    addButton->show();
    submitButton->hide();
    cancelButton->hide();
    nextButton->setEnabled(false);
    previoutButton->setEnabled(false);
    editButton->setEnabled(false);
    removeButton->setEnabled(false);
    findButton->setEnabled(false);

    // 布局管理
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;

    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addStretch();  // 用来确保按钮并不是采用均匀间隔排列的，而是更靠近 widget 的顶部
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);

    buttonLayout2->addWidget(nextButton);
    buttonLayout2->addWidget(previoutButton);

    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);
    mainLayout->addWidget(addressLabel,1,0);
    mainLayout->addWidget(addressText,1,1);
    mainLayout->addLayout(buttonLayout1,1,2);
    mainLayout->addLayout(buttonLayout2,3,1);
    // 要在 widget 上安装布局对象，必须调用 widget 的 setLayout() 函数
    setLayout(mainLayout);

    connect(addButton,SIGNAL(clicked()),this,SLOT(addContact()));
    connect(submitButton,SIGNAL(clicked(bool)),this,SLOT(submitContact()));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancel()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previoutButton, SIGNAL(clicked()), this, SLOT(previous()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(findButton,SIGNAL(clicked(bool)),this,findContact());
}

void AddressBook::addContact(){
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    addressText->setReadOnly(false);

    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();

    nextButton->setEnabled(false);
    previoutButton->setEnabled(false);
}
// 将模式切换到 EditingMode
void AddressBook::editContact(){
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    updateInterface(EditingMode);
}

void AddressBook::submitContact(){
    int number = contacts.size();
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if(currentMode == AddingMode){
        if(!contacts.contains(name)){
            contacts.insert(name,address);
            QMessageBox::information(this,"Add Successful",tr("%1 has been added to your address book").arg(name));
        }else{
            QMessageBox::information(this, tr("Add Unsuccessful"),tr("Sorry, \"%1\" is already in your address book.").arg(name));
            return;
        }
    }else if(currentMode == EditingMode){
        if(oldName != name){
            if(!contacts.contains(name)){
                QMessageBox::information(this, tr("Edit Successful"),tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name,address);
            }else{
                 QMessageBox::information(this, tr("Edit Unsuccessful"),tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
            return;
        }
    }else if(oldAddress != address){
    ///////////////
    }
    updateInterface(NavigationMode);


//    // 将按钮恢复为正常状态
//    if(contacts.isEmpty()){
//        nameLine->clear();
//        addressText->clear();
//    }
//    nameLine->setReadOnly(true);
//    addressText->setReadOnly(true);
//    addButton->setEnabled(true);
//    submitButton->hide();
//    cancelButton->hide();
//    nextButton->setEnabled(number > 1);
//    previoutButton->setEnabled(number > 1);
}

void AddressBook::cancel(){
    nameLine->setText(oldName);
    nameLine->setReadOnly(true);

    addressText->setText(oldAddress);
    addressText->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();

}

// 使用 QMap 对象 contacts 模拟了一个循环链接的列表
void AddressBook::next(){
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);

    if(i != contacts.end()){
        i ++;
    }else{
        i = contacts.begin();
    }

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::previous()  {
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i == contacts.end()){
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();
        i--;
        nameLine->setText(i.key());
        addressText->setText(i.value());
}

void AddressBook::findContact(){
    dialog->show();  // 查找界面
    if(dialog->exec() == QDialog::Accepted){
        QString contactName = dialog->getFindText();

        if(contacts.contains(contactName)){
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName));
        }else{
            QMessageBox::information(this, tr("Contact Not Found"),tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }
    updateInterface(NavigationMode);
}


