#include "mainwindow.h"
#include <QDateTime>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
m_contactList(new QListWidget(this)),
m_nameInput(new QLineEdit(this)),
m_phoneInput(new QLineEdit(this)),
m_statusLabel(new QLabel(this)),
m_activityLog(new QTextEdit(this))
{
setWindowTitle("SheSecure | Women's Safety");
resize(820, 650);
QWidget *central = new QWidget(this);
QVBoxLayout *mainLayout =
new QVBoxLayout(central);
mainLayout->setSpacing(14);
mainLayout->setContentsMargins(22, 22, 22, 22);
QLabel *title = new QLabel("SheSecure");
title->setObjectName("title");
QLabel *subtitle = new QLabel(
"Emergency Contacts and One-Click SOS Alert"
);
subtitle->setObjectName("subtitle");
mainLayout->addWidget(title);
mainLayout->addWidget(subtitle);
QHBoxLayout *contentLayout =
new QHBoxLayout();
// CONTACT MANAGEMENT SECTION
QGroupBox *contactsBox =
new QGroupBox("Emergency Contacts");
QVBoxLayout *contactsLayout =
new QVBoxLayout(contactsBox);
QFormLayout *form = new QFormLayout();
m_nameInput->setPlaceholderText("Enter contact name");
m_phoneInput->setPlaceholderText("Enter phone number");
form->addRow("Name:", m_nameInput);
form->addRow("Phone:", m_phoneInput);
contactsLayout->addLayout(form);
QPushButton *addButton =
new QPushButton("Add Contact");
addButton->setObjectName("primaryButton");
contactsLayout->addWidget(addButton);
contactsLayout->addWidget(m_contactList);
QPushButton *removeButton =
SheSecure - README and Source Code Page 10
new QPushButton("Remove Selected Contact");
contactsLayout->addWidget(removeButton);
// SOS SECTION
QGroupBox *sosBox =
new QGroupBox("Emergency SOS");
QVBoxLayout *sosLayout =
new QVBoxLayout(sosBox);
QLabel *description = new QLabel(
"In an emergency, press the SOS button "
"to generate an emergency message for "
"all your saved contacts."
);
description->setWordWrap(true);
sosLayout->addWidget(description);
QPushButton *sosButton =
new QPushButton("SOS - I'M IN DANGER");
sosButton->setObjectName("sosButton");
sosButton->setMinimumHeight(90);
sosLayout->addWidget(sosButton);
m_statusLabel->setObjectName("statusLabel");
m_statusLabel->setWordWrap(true);
sosLayout->addWidget(m_statusLabel);
QLabel *logTitle =
new QLabel("Emergency Activity Log");
sosLayout->addWidget(logTitle);
m_activityLog->setReadOnly(true);
m_activityLog->setPlaceholderText(
"SOS activity will appear here."
);
sosLayout->addWidget(m_activityLog, 1);
contentLayout->addWidget(contactsBox, 1);
contentLayout->addWidget(sosBox, 1);
mainLayout->addLayout(contentLayout, 1);
QLabel *footer = new QLabel(
"Offline Application | Local Contact Storage | "
"No GPS Tracking"
);
footer->setObjectName("footer");
mainLayout->addWidget(footer);
setCentralWidget(central);
// APPLICATION DESIGN
setStyleSheet(R"(
QMainWindow, QWidget {
background: #fff8fb;
color: #29232a;
font-family: Arial;
font-size: 14px;
}
#title {
color: #9d245d;
font-size: 30px;
font-weight: bold;
}
SheSecure - README and Source Code Page 11
#subtitle {
color: #705b68;
font-size: 14px;
}
QGroupBox {
border: 1px solid #e7c9d8;
border-radius: 10px;
margin-top: 12px;
padding: 12px;
font-weight: bold;
}
QGroupBox::title {
subcontrol-origin: margin;
left: 12px;
padding: 0 5px;
color: #8d2455;
}
QLineEdit, QListWidget, QTextEdit {
background: white;
border: 1px solid #decbd5;
border-radius: 6px;
padding: 8px;
}
QPushButton {
background: #ead8e1;
border: 0;
border-radius: 7px;
padding: 10px;
font-weight: bold;
}
QPushButton:hover {
background: #dfc2d1;
}
#primaryButton {
background: #9d245d;
color: white;
}
#primaryButton:hover {
background: #811b4b;
}
#sosButton {
background: #c62828;
color: white;
font-size: 20px;
font-weight: bold;
border-radius: 12px;
}
#sosButton:hover {
background: #a51f1f;
}
#statusLabel {
color: #8d2455;
font-weight: bold;
padding: 5px;
}
#footer {
color: #786b72;
font-size: 11px;
}
)");
// CONNECT BUTTONS TO BACKEND FUNCTIONS
connect(
addButton,
&QPushButton::clicked,
this,
&MainWindow::addContact
SheSecure - README and Source Code Page 12
);
connect(
removeButton,
&QPushButton::clicked,
this,
&MainWindow::removeSelectedContact
);
connect(
sosButton,
&QPushButton::clicked,
this,
&MainWindow::triggerSOS
);
refreshContacts();
m_statusLabel->setText(
"Ready. Add your emergency contacts."
);
}
// DISPLAY SAVED CONTACTS
void MainWindow::refreshContacts()
{
m_contactList->clear();
const auto& contacts = m_store.contacts();
for (const auto& contact : contacts)
{
m_contactList->addItem(
contact.name + " - " + contact.phone
);
}
if (contacts.isEmpty())
{
m_contactList->addItem(
"No emergency contacts saved."
);
}
}
// ADD CONTACT
void MainWindow::addContact()
{
QString error;
bool success = m_store.addContact(
m_nameInput->text(),
m_phoneInput->text(),
error
);
if (!success)
{
QMessageBox::warning(
this,
"Error",
error
);
return;
}
m_nameInput->clear();
m_phoneInput->clear();
refreshContacts();
m_statusLabel->setText(
"Emergency contact saved successfully!"
);
}
// REMOVE CONTACT
SheSecure - README and Source Code Page 13
void MainWindow::removeSelectedContact()
{
int row = m_contactList->currentRow();
if (row < 0 || row >= m_store.contacts().size())
{
QMessageBox::information(
this,
"Select Contact",
"Please select a contact first."
);
return;
}
if (!m_store.removeContact(row))
{
QMessageBox::warning(
this,
"Error",
"Could not remove contact."
);
return;
}
refreshContacts();
m_statusLabel->setText(
"Contact removed successfully."
);
}
// ACTIVITY LOG
void MainWindow::appendLog(const QString& message)
{
QString timestamp =
QDateTime::currentDateTime().toString(
"yyyy-MM-dd hh:mm:ss"
);
m_activityLog->append(
"[" + timestamp + "] " + message
);
}
// SOS EMERGENCY FUNCTION
void MainWindow::triggerSOS()
{
const auto& contacts = m_store.contacts();
if (contacts.isEmpty())
{
QMessageBox::warning(
this,
"No Contacts",
"Please add emergency contacts first."
);
return;
}
QMessageBox::StandardButton answer =
QMessageBox::question(
this,
"Confirm SOS",
"Are you sure you want to trigger SOS?",
QMessageBox::Yes | QMessageBox::No,
QMessageBox::No
);
if (answer != QMessageBox::Yes)
return;
QString sosMessage =
"SOS! I am in danger and need help. "
"Please contact me immediately.";
SheSecure - README and Source Code Page 14
appendLog(
"SOS activated. Preparing messages for all contacts."
);
{
for (const auto& contact : contacts)
appendLog(
"SIMULATED SOS MESSAGE TO: "
+ contact.name
+ " ("
+ contact.phone
+ ")"
);
appendLog(
);
"MESSAGE: " + sosMessage
}
m_statusLabel->setText(
"SOS activated! Messages generated for all "
"emergency contacts."
);
QMessageBox::information(
this,
"SOS Activated",
"Emergency messages have been generated "
"for all saved contacts.\n\n"
"This is a simulation. No actual SMS was sent."
);
}
