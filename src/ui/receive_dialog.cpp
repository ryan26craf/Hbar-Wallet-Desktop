#include "ui/receive_dialog.h"
#include <QVBoxLayout>
ReceiveDialog::ReceiveDialog(std::shared_ptr<Account> account, QWidget *parent) 
    : QDialog(parent) {
    setWindowTitle("Receive HBAR");
}
