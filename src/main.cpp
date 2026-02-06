#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>
#include "ui/main_window.h"
#include "utils/logger.h"
#include "storage/config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application metadata
    QApplication::setApplicationName("HBAR Wallet Desktop");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("HBAR Wallet");
    QApplication::setOrganizationDomain("hbarwallet.com");
    
    // Initialize logger
    Logger::getInstance().initialize("hbar_wallet.log");
    Logger::getInstance().log(LogLevel::INFO, "Application started");
    
    // Load configuration
    Config::getInstance().load();
    
    // Set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    try {
        // Create and show main window
        MainWindow mainWindow;
        mainWindow.show();
        
        Logger::getInstance().log(LogLevel::INFO, "Main window displayed");
        
        return app.exec();
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Fatal error: ") + e.what());
        
        QMessageBox::critical(nullptr, 
            "Fatal Error", 
            QString("An error occurred: %1").arg(e.what()));
        
        return 1;
    }
}
