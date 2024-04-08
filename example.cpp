#include <iostream>
#include "serial_port.h"

int main()
{
    // 串口配置
    SerialPortConfig config = {9600, 8, 1, 'N'};
    
    // 串口对象
    SerialPort serialPort("COM1", config);

    // 打开串口
    if (serialPort.openSerialPort("COM1", config))
    {
        std::cout << "Serial port opened successfully!" << std::endl;

        // 读取数据
        BYTE readData[100];
        int bytesRead = serialPort.readData(readData, sizeof(readData));
        if (bytesRead > 0)
        {
            std::cout << "Read " << bytesRead << " bytes from serial port." << std::endl;
            // 处理读取到的数据
            // ...
        }
        else
        {
            std::cerr << "Error reading from serial port!" << std::endl;
        }

        // 写入数据
        BYTE writeData[] = "Hello, serial port!";
        int bytesWritten = serialPort.writeData(writeData, sizeof(writeData) - 1); // 减去字符串末尾的空字符
        if (bytesWritten)
        {
            std::cout << "Write " << bytesWritten << " bytes to serial port." << std::endl;
        }
        else
        {
            std::cerr << "Error writing to serial port!" << std::endl;
        }

        // 关闭串口
        serialPort.closePort();
        std::cout << "Serial port closed." << std::endl;
    }
    else
    {
        std::cerr << "Failed to open serial port!" << std::endl;
    }

    return 0;
}
