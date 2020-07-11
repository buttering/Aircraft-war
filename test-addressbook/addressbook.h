#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "finddialog.h"

class AddressBook:public QWidget
{
    Q_OBJECT  // 使用 Q_OBJECT 宏表明该类使用国际化功能与 Qt 信号和槽功能
public:
    AddressBook(QWidget *parent=0);

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previoutButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    FindDialog *dialog;  // 声明私有变量 dialog，用于引用 FindDialog 的实例
    QMap<QString,QString>contacts;// 需要一个容器来储存地址簿联系人，这样才能搜索和显示联系人
    QString oldName;
    QString oldAddress;
    Mode currentMode;  // 声明 currentMode 来跟踪 enum 的当前模式

    void updateInterface(Mode mode);

    enum Mode { NavigationMode, AddingMode, EditingMode };


public slots:
    void addContact();
    void submitContact();
    void cancel();
    void next();
    void previous();
    void editContact();
    void removeContact();
    void findContact();

};

#endif // ADDRESSBOOK_H
