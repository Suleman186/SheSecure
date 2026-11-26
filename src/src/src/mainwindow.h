#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contactstore.h"
#include <QMainWindow>
class QListWidget;
class QLineEdit;
class QLabel;
class QTextEdit;
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
explicit MainWindow(QWidget *parent = nullptr);
private slots:
void addContact();
void removeSelectedContact();
void triggerSOS();
private:
void refreshContacts();
void appendLog(const QString& message);
ContactStore m_store;
QListWidget *m_contactList;
QLineEdit *m_nameInput;
QLineEdit *m_phoneInput;
QLabel *m_statusLabel;
QTextEdit *m_activityLog;
};
#endif
