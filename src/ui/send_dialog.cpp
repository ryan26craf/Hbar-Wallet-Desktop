#include "ui/send_dialog.h"
#include <QVBoxLayout>
SendDialog::SendDialog(std::shared_ptr<Account> account, QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("Send HBAR");
    auto *layout = new QVBoxLayout(this);
}
