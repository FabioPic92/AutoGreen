#include "UI/Pages/MainPage.hpp"

MainPage::MainPage(QWidget *parent) {
    m_publisher = new CameraPublisher("tcp://localhost:1883", "MainPagePublisher");

    try {
        m_publisher->connect();
        qDebug() << "MainPage: Publisher connesso con successo.";
    } catch (const std::runtime_error& e) {
        qCritical() << "MainPage: Errore di connessione MQTT Publisher:" << e.what();
        QMessageBox::critical(this, "Errore MQTT", QString("Impossibile connettersi al broker MQTT: ") + e.what() + "\nAssicurati che sia in esecuzione a localhost:1883.");
    }

    setupUI();
};

void MainPage::onMyNewButtonClicked() {
    if (m_publisher && m_publisher->isConnected()) { 
        try {
            m_publisher->requestPhoto("camera/request");
            emit photoClicked();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Publish Error", QString("Failed to send photo request: %1").arg(e.what()));
            std::cerr << "Error sending photo request: " << e.what() << std::endl;
        }
    }    
}