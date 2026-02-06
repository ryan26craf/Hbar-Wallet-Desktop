#ifndef SEND_DIALOG_H
#define SEND_DIALOG_H
#include <QDialog>
#include <memory>
class Account;
class SendDialog : public QDialog {
    Q_OBJECT
public:
    explicit SendDialog(std::shared_ptr<Account> account, QWidget *parent = nullptr);
};
#endif
