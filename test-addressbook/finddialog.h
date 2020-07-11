#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QWidget>
#include <QLineEdit>

//使用向前 (forward) 声明来声明 QLineEdit 和 QPushButton，这样就能在对话框类中使用这些 widget
class QLineEdit;
class QPushButton;

class FindDialog:public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent=0);
    QString getFindText();
private:
    QPushButton *findButton;
    QLineEdit *lineEdit;
    QString findText;
public slots:
    void findClicked();
};

#endif // FINDDIALOG_H
