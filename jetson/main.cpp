#include <iostream>
#include "i2c/i2c.hpp"

using namespace Jetson;
int main(){
    std::cout << "Test" << std::endl;
    I2C i2c;

    i2c.setup(0x22);

    char data;
    char* mockPacket = new char[32];
    char* readPacket = new char[32];
    
    mockPacket[0] = 0xAA; // Tag
    for(int i=1;i<32;i++){
        mockPacket[i] = i;
    }
 
    i2c.writeData(0x31, mockPacket, 32);
    mockPacket[0] = 0xBB;
     for(int i=1;i<32;i++){
        mockPacket[i] = i*2;
    }
 
    i2c.writeData(0x32, mockPacket, 32);

    i2c.readData(*readPacket, 0x31, 32);
      for(int i=0;i<32;i++){
         std::cout <<std::to_string(readPacket[i]) << std::endl;
    }
    i2c.readData(*readPacket, 0x32, 32);

    for(int i=0;i<32;i++){
         std::cout <<std::to_string(readPacket[i]) << std::endl;
    }
   
}