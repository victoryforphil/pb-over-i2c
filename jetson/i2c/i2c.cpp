#include "i2c.hpp"
#include <iostream>
using namespace Jetson;

int I2C::setup( int addr)
{
    std::cout << "Starting new I2C Client at: " +std::to_string(addr) << std::endl;

    if ((file = open(path, O_RDWR)) < 0)
    {
        std::cout << "Failed to open I2C File" << std::endl;

        return 1;
    }

  
    if (ioctl(file, I2C_SLAVE, addr) < 0)
    {
        std::cout << "Failed to talk to I2C Slave" << std::endl;
        return 2;
    }
    std::cout << "Started" << std::endl;
    return 0;
}

int I2C::readData(char &out, char reg){
   
    unsigned char result;
    
    writeData(0x00, reg);
    
    if(read(file, &result, 1) != 1){
        return 1;
    }
	
   
    out = result;
    return 0;
    
}

int I2C::readData(char &out, char reg, char size){
   

    
    writeData(0x00, reg);
    
    if(read(file, &out, size) != size){
        return 1;
    }

    return 0;
    
}

int I2C::readDataRaw(char &data, int size){

    

    
    if(read(file, &data, size) != size){
        return 1;
    }
	
  
    return 0;
}

int I2C::writeData(char reg, char data){
    char buffer[] = {reg, data};
    if (write(file, &buffer, 2) != 2)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		
        return 1;
	}

 
    return 0;
}

int I2C::writeData(char reg, char* data, char size){
    char buffer[size + 2] ;
    buffer[0] = reg;
    buffer[1] = size;
    for(int i=0;i<size;i++){
        buffer[i+2] = data[i];
    }
    if (write(file, &buffer, size+ 2 ) != size+ 2 )		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		std::cout << "ERROR" << std::endl;
        return 1;
	}

 
    return 0;
}

int I2C::writeDataRaw(char* data, int size){
    if (write(file, data, size) != size)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		
        return 1;
	}

 
    return 0;
}