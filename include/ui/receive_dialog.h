#ifndef RECEIVE_DIALOG_H
#define RECEIVE_DIALOG_H
#include <QDialog>
#include <memory>
class Account;
class ReceiveDialog : public QDialog {
    Q_OBJECT
public:
    explicit ReceiveDialog(std::shared_ptr<Account> account, QWidget *parent = nullptr);
};
#endif
