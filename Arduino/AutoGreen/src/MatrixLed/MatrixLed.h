#ifndef MATRIX_LED_H 
#define MATRIX_LED_H

#include "Arduino_LED_Matrix.h"

const uint32_t online[] = {
    0x01f00e00,
    0x40000000,
    0x00000000
};

const uint32_t defaultMatrix[] = {
    0x00000000,
    0x00000000,
    0x00000000
};

class MatrixLed{
private:
    ArduinoLEDMatrix m_matrix;
    uint32_t frame[3];

public:
    MatrixLed(){
        memcpy(frame, defaultMatrix, sizeof(frame));
        m_matrix.begin();
        m_matrix.loadFrame(frame);
    }

    void setOnline() {
        for (int i = 0; i < 3; i++) {
            frame[i] |= online[i];
        }
        m_matrix.loadFrame(frame);
    }

    void setOffline() {
        for (int i = 0; i < 3; i++) {
            frame[i] &= ~online[i];
        }

        m_matrix.loadFrame(frame);
    }

};

#endif