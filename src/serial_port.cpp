#include "serial_port.h"

SerialPort::SerialPort() : hSerial(INVALID_HANDLE_VALUE), isClose(true) {}

SerialPort::SerialPort(const char *portName, SerialPortConfig config) : hSerial(INVALID_HANDLE_VALUE), isClose(true) {
    openSerialPort(portName, config);
}

SerialPort::~SerialPort() {
    closePort();
}

int SerialPort::openSerialPort(const char *portName, SerialPortConfig config) {
    if (!isClose) {
        std::cerr << "Serial port is already open!" << std::endl;
        return FALSE;
    }

    hSerial = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port!" << std::endl;
        return FALSE;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state!" << std::endl;
        CloseHandle(hSerial);
        return FALSE;
    }

    // Set serial port configurations
    dcbSerialParams.BaudRate = config.baudrate;
    dcbSerialParams.ByteSize = config.databits;
    dcbSerialParams.StopBits = config.stopbits;
    dcbSerialParams.Parity = config.parity;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port state!" << std::endl;
        CloseHandle(hSerial);
        return FALSE;
    }

    isClose = false;
    return TRUE;
}

int SerialPort::readData(BYTE *data, int size) {
    DWORD bytesRead;
    if (isClose || hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Serial port is not open!" << std::endl;
        return 0;
    }

    if (!ReadFile(hSerial, data, size, &bytesRead, NULL)) {
        std::cerr << "Error reading from serial port!" << std::endl;
        return 0;
    }

    return bytesRead;
}

int SerialPort::writeData(BYTE *data, int len) {
    DWORD bytesWritten;
    if (isClose || hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Serial port is not open!" << std::endl;
        return FALSE;
    }

    if (!WriteFile(hSerial, data, len, &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port!" << std::endl;
        return FALSE;
    }

    return TRUE;
}

void SerialPort::closePort() {
    if (!isClose && hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        isClose = true;
    }
}