#ifndef CREATE_WALLET_DIALOG_H
#define CREATE_WALLET_DIALOG_H
#include <QDialog>
#include <QLineEdit>
class CreateWalletDialog : public QDialog {
    Q_OBJECT
public:
    explicit CreateWalletDialog(QWidget *parent = nullptr);
    QString getPassword() const { return password->text(); }
private:
    QLineEdit *password;
};
#endif
