#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <memory>
#include <utility>

class Sensor
{
	protected:
		std::string name;
	public:
		explicit Sensor(const std::string& n) : name(n) {}
		virtual ~Sensor()
		{
			std::cout << name << " is Erased from Memory." << std::endl;
		}

		std::string get_name() const
		{
			return name;
		}
		virtual double read_data() = 0;

		virtual void check_warning(double val) = 0;
};

class Altimeter : public Sensor
{
	public:
		explicit Altimeter(const std::string& n) : Sensor(n) {}

		double read_data() override
		{
			return 1000 + (std::rand() % 500) / 10.0;
		}
		void check_warning(double val) override
		{
			if (val < 1010)
			{
				std::cout << "[WARNING] " << name << " is too low" << std::endl;
			}
		}
};

class Thermometer : public Sensor
{
	public:
		explicit Thermometer(const std::string& n) : Sensor(n) {}

		double read_data() override
		{
			return 20 + (std::rand() % 100) / 10.0;
		}
		void check_warning(double val) override
		{
			if (val > 28)
			{
				std::cout << "[WARNING] " << name << " is too high" << std::endl;
			}
		}
};

class SensorControlUnit
{
	private:
		std::vector<std::unique_ptr<Sensor>> sensors;
	public:
		void add_sensor(std::unique_ptr<Sensor> sensor)
		{
			sensors.push_back(std::move(sensor));
		}
		void display_data()
		{
			for (const auto& sensor : sensors)
			{
				double data = sensor->read_data();
				std::cout << "Sensor: " << sensor->get_name() << "   Value: " << data << std::endl;
				sensor->check_warning(data);
			}
		}
};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	SensorControlUnit sci;
	
	sci.add_sensor(std::make_unique<Altimeter>("Main Altimeter"));
	sci.add_sensor(std::make_unique<Altimeter>("Backup Altimeter"));
	sci.add_sensor(std::make_unique<Thermometer>("Engine Thermometer"));
	sci.add_sensor(std::make_unique<Thermometer>("Cabin Thermometer"));
	
	int cycle = 0;
	const int MAX_CYCLES = 4;
	
	std::cout << "----[SYSTEM] Avionic Control Unit Initiating------" << std::endl;
	
	while(cycle < MAX_CYCLES)
	{
		sci.display_data();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cycle++;
	}
	std::cout << "----[SYSTEM] Avionic Control Unit Shut Down------" << std::endl;
	return 0;
}
	
	
	
	
	
	
	
	
	
	
					
 




























