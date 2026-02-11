#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <memory>
#include <utility>
#include <mutex>
#include <queue>
#include <condition_variable>

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
struct Line
{
	std::string name;
	double value;
};

class SensorControlUnit
{
	private:
		std::mutex key;
		std::condition_variable cv;
		std::queue<Line> line;
		bool active = true;
	public:
		void push_data(const std::string& name, double value)
		{
			{
				std::lock_guard<std::mutex> lock(key);
				line.push({name, value});
			}
			cv.notify_one();
		}
		
		void process_data()
		{
			while(true)
			{
				std::unique_lock<std::mutex> lock(key);
				cv.wait(lock, [this]()
				{
					return !active || !line.empty();
				});
				
				if (!active && line.empty())
				{
					std::cout << "----Program Terminated----" << std::endl;
					return;
				}
				
				if (!line.empty())
				{
					Line data = line.front();
					line.pop();
					
					lock.unlock();
					std::cout << "Sensor: " << data.name << " Value: " << data.value << std::endl;
				}
			}
		}
		void stop()
		{	
			{
				std::lock_guard<std::mutex> lock(key);
				active = false;
			}
			cv.notify_all();
		}
};

void sensor_task(SensorControlUnit& scu)
{
	std::vector<std::unique_ptr<Sensor>> sensors;
	sensors.push_back(std::make_unique<Altimeter>("Main Altimeter"));
	sensors.push_back(std::make_unique<Altimeter>("Backup Altimeter"));
	sensors.push_back(std::make_unique<Thermometer>("Engine Thermometer"));
	sensors.push_back(std::make_unique<Thermometer>("Cabin Thermometer"));
	
	for (int i = 0; i < 10; i++)
	{
		for (const auto& sensor : sensors)
		{
			double value = sensor->read_data();
			sensor->check_warning(value);
			scu.push_data(sensor->get_name(), value);
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "----Sensor Data Stream Terminated-----" << std::endl;
} 

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	SensorControlUnit scu;
	
	std::cout << "---System Initiated----" << std::endl;
	std::thread display_thread(&SensorControlUnit::process_data, &scu);
	std::thread sensor_thread(&sensor_task, std::ref(scu));
	
	sensor_thread.join();
	scu.stop();
	display_thread.join();
	return 0;
}
	
	
	
	
	
	
	
					
 




























