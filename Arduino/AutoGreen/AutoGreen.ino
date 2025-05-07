#include "src/MotorStepper/MotorStepper.h"
#include "src/ClientServer/ClientServerManager.h"
#include "src/MatrixLed/MatrixLed.h"

int led =  LED_BUILTIN;

MotorStepper *motorStepper;
ClientServerManager *clientServerManager;
MatrixLed *matrixLed;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);

    matrixLed = new MatrixLed();

    matrixLed->setOffline();

    clientServerManager = new ClientServerManager();

    clientServerManager->Connection();

    matrixLed->setOnline();

    motorStepper = new MotorStepper(20);
}

void loop() {
    // clientServerManager->Refresh();

    // if (clientServerManager->isWifiConnected()) {
    //     matrixLed->setOnline();
    // } else {
    //     matrixLed->setOffline();
    // }
    motorStepper->step();
}
