#include "ui/main_window.h"
#include "ui/create_wallet_dialog.h"
#include "ui/send_dialog.h"
#include "ui/receive_dialog.h"
#include "ui/settings_dialog.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , walletLoaded(false)
{
    setupUi();
    setWalletLoaded(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    setWindowTitle("HBAR Wallet Desktop");
    resize(900, 600);
    
    createMenuBar();
    createToolBar();
    createCentralWidget();
    
    statusBar()->showMessage("Ready");
}

void MainWindow::createMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu("&File");
    
    QAction* createAction = fileMenu->addAction("&Create Wallet");
    connect(createAction, &QAction::triggered, this, &MainWindow::onCreateWallet);
    
    QAction* openAction = fileMenu->addAction("&Open Wallet");
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenWallet);
    
    fileMenu->addSeparator();
    
    QAction* lockAction = fileMenu->addAction("&Lock Wallet");
    connect(lockAction, &QAction::triggered, this, &MainWindow::onLockWallet);
    
    fileMenu->addSeparator();
    
    QAction* exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    QMenu* walletMenu = menuBar()->addMenu("&Wallet");
    
    QAction* sendAction = walletMenu->addAction("&Send");
    connect(sendAction, &QAction::triggered, this, &MainWindow::onSend);
    
    QAction* receiveAction = walletMenu->addAction("&Receive");
    connect(receiveAction, &QAction::triggered, this, &MainWindow::onReceive);
    
    walletMenu->addSeparator();
    
    QAction* refreshAction = walletMenu->addAction("&Refresh");
    connect(refreshAction, &QAction::triggered, this, &MainWindow::onRefresh);
    
    QMenu* toolsMenu = menuBar()->addMenu("&Tools");
    
    QAction* settingsAction = toolsMenu->addAction("&Settings");
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);
    
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    
    QAction* aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::createToolBar()
{
    QToolBar* toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);
    
    sendButton = new QPushButton("Send");
    receiveButton = new QPushButton("Receive");
    refreshButton = new QPushButton("Refresh");
    
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSend);
    connect(receiveButton, &QPushButton::clicked, this, &MainWindow::onReceive);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::onRefresh);
    
    toolbar->addWidget(sendButton);
    toolbar->addWidget(receiveButton);
    toolbar->addSeparator();
    toolbar->addWidget(refreshButton);
}

void MainWindow::createCentralWidget()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    // Left panel - Accounts
    QVBoxLayout* leftLayout = new QVBoxLayout();
    
    QGroupBox* accountsGroup = new QGroupBox("Accounts");
    QVBoxLayout* accountsLayout = new QVBoxLayout(accountsGroup);
    
    accountList = new QListWidget();
    connect(accountList, &QListWidget::currentRowChanged, 
            this, &MainWindow::onAccountSelected);
    accountsLayout->addWidget(accountList);
    
    QPushButton* addAccountBtn = new QPushButton("+ Add Account");
    accountsLayout->addWidget(addAccountBtn);
    
    leftLayout->addWidget(accountsGroup);
    leftLayout->addStretch();
    
    // Right panel - Account details and transactions
    QVBoxLayout* rightLayout = new QVBoxLayout();
    
    // Account info
    QGroupBox* infoGroup = new QGroupBox("Account Information");
    QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);
    
    accountIdLabel = new QLabel("No account selected");
    accountIdLabel->setWordWrap(true);
    infoLayout->addWidget(accountIdLabel);
    
    balanceLabel = new QLabel("Balance: 0.00 HBAR");
    QFont balanceFont = balanceLabel->font();
    balanceFont.setPointSize(16);
    balanceFont.setBold(true);
    balanceLabel->setFont(balanceFont);
    infoLayout->addWidget(balanceLabel);
    
    rightLayout->addWidget(infoGroup);
    
    // Transaction history
    QGroupBox* txGroup = new QGroupBox("Transaction History");
    QVBoxLayout* txLayout = new QVBoxLayout(txGroup);
    
    transactionTable = new QTableWidget();
    transactionTable->setColumnCount(5);
    transactionTable->setHorizontalHeaderLabels(
        {"Date", "Type", "Amount", "To/From", "Status"});
    transactionTable->horizontalHeader()->setStretchLastSection(true);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    txLayout->addWidget(transactionTable);
    
    rightLayout->addWidget(txGroup);
    
    // Add layouts to main layout
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 3);
    
    setCentralWidget(centralWidget);
}

void MainWindow::onCreateWallet()
{
    CreateWalletDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        wallet = std::make_unique<Wallet>();
        
        if (wallet->create(dialog.getPassword())) {
            walletLoaded = true;
            setWalletLoaded(true);
            updateAccountList();
            
            QMessageBox::information(this, "Success", 
                "Wallet created successfully!\n\nPlease save your recovery phrase:\n" 
                + QString::fromStdString(wallet->getMnemonic()));
        } else {
            QMessageBox::critical(this, "Error", "Failed to create wallet");
        }
    }
}

void MainWindow::onOpenWallet()
{
    QString filePath = QFileDialog::getOpenFileName(this, 
        "Open Wallet", "", "Wallet Files (*.hbar)");
    
    if (filePath.isEmpty()) {
        return;
    }
    
    bool ok;
    QString password = QInputDialog::getText(this, "Unlock Wallet",
        "Enter password:", QLineEdit::Password, "", &ok);
    
    if (!ok || password.isEmpty()) {
        return;
    }
    
    wallet = std::make_unique<Wallet>();
    
    if (wallet->load(filePath.toStdString(), password.toStdString())) {
        walletLoaded = true;
        setWalletLoaded(true);
        updateAccountList();
        QMessageBox::information(this, "Success", "Wallet opened successfully");
    } else {
        QMessageBox::critical(this, "Error", "Failed to open wallet");
    }
}

void MainWindow::onSend()
{
    if (!currentAccount) {
        QMessageBox::warning(this, "Warning", "Please select an account first");
        return;
    }
    
    SendDialog dialog(currentAccount, this);
    if (dialog.exec() == QDialog::Accepted) {
        updateBalance();
        updateTransactionHistory();
    }
}

void MainWindow::onReceive()
{
    if (!currentAccount) {
        QMessageBox::warning(this, "Warning", "Please select an account first");
        return;
    }
    
    ReceiveDialog dialog(currentAccount, this);
    dialog.exec();
}

void MainWindow::onRefresh()
{
    if (!walletLoaded) {
        return;
    }
    
    updateBalance();
    updateTransactionHistory();
    statusBar()->showMessage("Refreshed", 2000);
}

void MainWindow::onSettings()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About HBAR Wallet Desktop",
        "HBAR Wallet Desktop v1.0.0\n\n"
        "A secure desktop wallet for Hedera (HBAR)\n\n"
        "To download the latest version, visit:\n"
        "https://github.com/yourusername/hbar-wallet-desktop/releases");
}

void MainWindow::onAccountSelected(int index)
{
    if (!walletLoaded || index < 0) {
        return;
    }
    
    auto accounts = wallet->getAccounts();
    if (index >= static_cast<int>(accounts.size())) {
        return;
    }
    
    currentAccount = accounts[index];
    updateBalance();
    updateTransactionHistory();
}

void MainWindow::onLockWallet()
{
    if (wallet) {
        wallet->lock();
        setWalletLoaded(false);
        statusBar()->showMessage("Wallet locked");
    }
}

void MainWindow::updateAccountList()
{
    accountList->clear();
    
    if (!walletLoaded) {
        return;
    }
    
    auto accounts = wallet->getAccounts();
    for (const auto& account : accounts) {
        QString item = QString::fromStdString(account->getName()) 
            + " - " + QString::fromStdString(account->getAccountId());
        accountList->addItem(item);
    }
    
    if (!accounts.empty()) {
        accountList->setCurrentRow(0);
    }
}

void MainWindow::updateBalance()
{
    if (!currentAccount) {
        balanceLabel->setText("Balance: 0.00 HBAR");
        accountIdLabel->setText("No account selected");
        return;
    }
    
    double balance = currentAccount->getBalance();
    balanceLabel->setText(QString("Balance: %1 HBAR")
        .arg(balance, 0, 'f', 2));
    
    accountIdLabel->setText(QString("Account ID: %1")
        .arg(QString::fromStdString(currentAccount->getAccountId())));
}

void MainWindow::updateTransactionHistory()
{
    transactionTable->setRowCount(0);
    
    if (!currentAccount) {
        return;
    }
    
    auto transactions = currentAccount->getTransactions();
    
    for (const auto& tx : transactions) {
        int row = transactionTable->rowCount();
        transactionTable->insertRow(row);
        
        // Date
        QDateTime dateTime;
        dateTime.setTime_t(tx.timestamp);
        transactionTable->setItem(row, 0, 
            new QTableWidgetItem(dateTime.toString("yyyy-MM-dd hh:mm")));
        
        // Type
        bool isSent = (tx.from == currentAccount->getAccountId());
        transactionTable->setItem(row, 1, 
            new QTableWidgetItem(isSent ? "Sent" : "Received"));
        
        // Amount
        transactionTable->setItem(row, 2, 
            new QTableWidgetItem(QString::number(tx.amount, 'f', 2)));
        
        // To/From
        std::string address = isSent ? tx.to : tx.from;
        transactionTable->setItem(row, 3, 
            new QTableWidgetItem(QString::fromStdString(address)));
        
        // Status
        transactionTable->setItem(row, 4, 
            new QTableWidgetItem(QString::fromStdString(tx.status)));
    }
}

void MainWindow::setWalletLoaded(bool loaded)
{
    sendButton->setEnabled(loaded);
    receiveButton->setEnabled(loaded);
    refreshButton->setEnabled(loaded);
}
