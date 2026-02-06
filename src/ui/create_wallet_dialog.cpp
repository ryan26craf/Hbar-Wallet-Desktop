#include "ui/create_wallet_dialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

CreateWalletDialog::CreateWalletDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Create Wallet");
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Enter password:"));
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    layout->addWidget(password);
    auto *okBtn = new QPushButton("Create");
    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(okBtn);
}
