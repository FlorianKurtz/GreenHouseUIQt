#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <math.h>

#include "gpio.hpp"

const std::string unexport_path = "/sys/class/gpio/unexport";		// PATH unexport
const std::string export_path = "/sys/class/gpio/export";			// PATH export


// ----------------- GPIO Functions ---------------

GPIO::GPIO(void)
{
    this->pin_number = "0";
}

GPIO::GPIO(std::string str)
{
    this->pin_number = str ;
}

void GPIO::setPinNumber(std::string str)
{
    this->pin_number = str;
}

int GPIO::exportPin(void)
{
    // -------------------------------------------------------------------------------------
    // 1. Activate GPIO pin

            // Open file
        std::ofstream export_file( export_path.c_str() );

        // Check if the file was actually opened
        if(!export_file.is_open())
        {
            std::cerr << "Unable to open " << export_path << std::endl;
            return -1;
        }
        // Write pin numbers to file
        export_file << this->pin_number ;

        // Close the file
        export_file.close();
        return 0;
}

int GPIO::unexportPin(void)
{
    // -------------------------------------------------------------------------------------
    //  1. Desactivate GPIO pin

            // Open file
        std::ofstream unexport_file( unexport_path.c_str() );

        // Check if the file was actually opened
        if(!unexport_file.is_open())
        {
            std::cerr << "Unable to open " << unexport_path << std::endl;
            return -1;
        }
        // Delete pin numbers to file
        unexport_file << this->pin_number ;

        // Close the file
        unexport_file.close();
        return 0;
}

int GPIO::setPinDirection(std::string str)
{
    // 2. Set directions

            // Define paths
        std::string pin_path = "/sys/class/gpio/gpio" + pin_number + "/direction";

            // Open files
        std::ofstream pin_file( pin_path.c_str() );
        if(!pin_file.is_open())
        {
            std::cerr << "Unable to open " << pin_path << std::endl;
            return -1;
        }

        // Write directions to the files
        pin_file << str;

        // Close the files
        pin_file.close();

        return 0;
}

int GPIO::setPinValue(std::string str)
{
    // 4. Write to the pin

            // Define path
        std::string write_pin_path = "/sys/class/gpio/gpio" + pin_number + "/value";

        // Open file
        std::ofstream write_pin_file( write_pin_path.c_str() );
        if(!write_pin_file.is_open())
        {
            std::cerr << "Unable to open " << write_pin_path << std::endl;
            return -1;
        }

        // Write value
        write_pin_file << str;
        return 0;
}

int GPIO::setPinValue(char carac)
{
    // 4. Write to the pin

            // Define path
        std::string write_pin_path = "/sys/class/gpio/gpio" + pin_number + "/value";

        // Open file
        std::ofstream write_pin_file( write_pin_path.c_str() );
        if(!write_pin_file.is_open())
        {
            std::cerr << "Unable to open " << write_pin_path << std::endl;
            return -1;
        }

        // Write value
        write_pin_file << carac;
        return 0;
}

int GPIO::getPinValue(std::string& str)
{
    // 3. Read the pin state

        // Define path
        std::string read_pin_path = "/sys/class/gpio/gpio" + pin_number + "/value";

        // Open file
        std::ifstream read_pin_file( read_pin_path.c_str() );
        if(!read_pin_file.is_open())
        {
            std::cerr << "Unable to open " << read_pin_path << std::endl;
            return -1;
        }

        // read value
        read_pin_file >> str;
        return 0;
}
int GPIO::set(std::string pinNumber, std::string pinDirection, std::string pinValue)
{

    this->pin_number = pinNumber ;
    this->exportPin();
    this->setPinDirection(pinDirection);
    this->setPinValue(pinValue);
    return 0 ;
}




