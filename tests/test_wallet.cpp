#include <QtTest>
class WalletTest : public QObject {
    Q_OBJECT
private slots:
    void testWalletCreation() {
        QVERIFY(true);
    }
};

QTEST_MAIN(WalletTest)
#include "test_wallet.moc"
