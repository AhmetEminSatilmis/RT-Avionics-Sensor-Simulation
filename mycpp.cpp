#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

class Sensor
{
	protected:
		std::string name;
	public:
		Sensor(const std::string& n) : name(n) {}

		virtual ~Sensor()
		{
			std::cout << "[SYSTEM] " << name << " is erased from memory." << std::endl;
		}

		virtual double read_data() = 0;
		virtual void check_warning(double val) = 0;
		
		std::string get_name() const
		{
			return name;
		}
};

class Altimeter : public Sensor
{
	public:
		Altimeter(const std::string& n) : Sensor(n) {}

		double read_data() override
		{
			return 1000 + (std::rand() % 500) / 10.0;
		}
		void check_warning(double val) override
		{
			if (val < 1010)
			{
				std::cout << "[WARNING] Altitude is too Low!" << std::endl;
			}
		}	
};

class Thermometer : public Sensor
{
	public:
		Thermometer(const std::string& n) : Sensor(n) {}
	
		double read_data() override
		{
			return 20 + (std::rand() % 100) / 10.0;	
		}
		void check_warning(double val) override
		{
			if (val > 28)
			{
				std::cout << "[WARNING] Motor is Too Hot!" << std::endl;
			}
		} 
};

int main()
{
	std::srand(std::time(nullptr));	

		std::vector<Sensor*> sensors;
	
	
		sensors.push_back(new Altimeter("Main Altimeter"));
		sensors.push_back(new Thermometer("Motor Temperature"));
		sensors.push_back(new Altimeter("Backup Altimeter"));
		
		std::cout << "----Sensor Data Collection Initiating----" << std::endl;

	while(true)
	{
		for (const auto& sensor : sensors)
		{
			double current_value = sensor->read_data();
			std::cout << "Sensor: " << sensor->get_name() << " Value: " << current_value << std::endl;
			sensor->check_warning(current_value);
		}
		std::this_thread::sleep_for(std::chrono::seconds(3));	
	}
	std::cout << "----Program Terminating(Memory Cleanup)-----" << std::endl;
	for (auto& sensor : sensors)
	{
		delete sensor;
	}
				
	sensors.clear();
	
	return 0;
}














































		