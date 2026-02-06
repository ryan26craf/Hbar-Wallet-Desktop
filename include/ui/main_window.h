#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <memory>
#include "wallet/wallet.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateWallet();
    void onOpenWallet();
    void onSend();
    void onReceive();
    void onRefresh();
    void onSettings();
    void onAbout();
    void onAccountSelected(int index);
    void onLockWallet();

private:
    void setupUi();
    void createMenuBar();
    void createToolBar();
    void createCentralWidget();
    void updateAccountList();
    void updateBalance();
    void updateTransactionHistory();
    void setWalletLoaded(bool loaded);

    // Wallet
    std::unique_ptr<Wallet> wallet;
    bool walletLoaded;
    
    // UI Components
    QListWidget* accountList;
    QLabel* balanceLabel;
    QLabel* accountIdLabel;
    QPushButton* sendButton;
    QPushButton* receiveButton;
    QPushButton* refreshButton;
    QTableWidget* transactionTable;
    
    // Current selected account
    std::shared_ptr<Account> currentAccount;
};

#endif // MAIN_WINDOW_H
