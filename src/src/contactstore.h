#include "contactstore.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
ContactStore::ContactStore()
{
load();
}
const QVector<EmergencyContact>& ContactStore::contacts() const
{
return m_contacts;
}
QString ContactStore::dataFilePath() const
{
return QDir(
QCoreApplication::applicationDirPath()
).filePath("contacts.txt");
}
{
void ContactStore::load()
QFile file(dataFilePath());
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
return;
QTextStream in(&file);
while (!in.atEnd())
{
QString line = in.readLine();
int separator = line.indexOf('|');
if (separator <= 0)
continue;
EmergencyContact contact;
contact.name = line.left(separator).trimmed();
contact.phone = line.mid(separator + 1).trimmed();
if (!contact.name.isEmpty() &&
!contact.phone.isEmpty())
{
m_contacts.push_back(contact);
}
}
file.close();
}
bool ContactStore::addContact(
const QString& name,
const QString& phone,
QString& error)
{
QString cleanName = name.trimmed();
QString cleanPhone = phone.trimmed();
if (cleanName.isEmpty() || cleanPhone.isEmpty())
{
error = "Please enter both name and phone number.";
return false;
}
if (cleanName.contains('|') ||
cleanPhone.contains('|') ||
cleanName.contains('\n') ||
cleanPhone.contains('\n'))
{
SheSecure - README and Source Code Page 7
error = "Invalid contact details.";
return false;
}
{
for (const auto& contact : m_contacts)
if (contact.phone == cleanPhone)
error = "This phone number already exists.";
return false;
{
}
}
m_contacts.push_back({cleanName, cleanPhone});
if (!save(error))
{
m_contacts.removeLast();
return false;
}
return true;
}
{
bool ContactStore::removeContact(int index)
if (index < 0 || index >= m_contacts.size())
return false;
EmergencyContact removed = m_contacts.takeAt(index);
QString error;
if (!save(error))
{
m_contacts.insert(index, removed);
return false;
}
return true;
}
{
bool ContactStore::save(QString& error) const
QFile file(dataFilePath());
if (!file.open(
QIODevice::WriteOnly |
QIODevice::Text |
QIODevice::Truncate))
error = "Could not save contacts file.";
return false;
{
}
QTextStream out(&file);
for (const auto& contact : m_contacts)
{
out << contact.name
<< "|"
<< contact.phone
<< '\n';
}
file.close();
return true;
}
