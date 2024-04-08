#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <windows.h>
#include <iostream>

typedef unsigned char BYTE;

/** Serial port config param. */
struct SerialPortConfig {
    int baudrate;   // read speed
    int databits;   // one of 7,8
    int stopbits;   // one of 1,2
    char parity;    // one of N,E,O,S
};

/** Serial port device class. */
class SerialPort {
private:
    HANDLE hSerial;  // serial port handle
    bool isClose;    // is serial port closed

public:
    SerialPort();
    SerialPort(const char *portName, SerialPortConfig config = {9600, 8, 1, 'N'});
    ~SerialPort();

    /**
     * @brief Open serial port device.
     * @param config serial port device config param
     * @return is success
     */
    int openSerialPort(const char *portName, SerialPortConfig config);

    /**
     * @brief Read device data.
     * @param data read data
     * @param size data size to read
     * @return data length
     */
    int readData(BYTE *data, int size);

    /**
     * @brief Write serial port data.
     * @param data serial port data
     * @param len data length to write
     * @return is success
     */
    int writeData(BYTE *data, int len);

    /** @brief Close serial port device. */
    void closePort();
};

#endif //SERIAL_PORT_H