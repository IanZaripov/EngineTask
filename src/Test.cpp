#include "Test.h"

void TestMaxPower::RunTest(std::shared_ptr<Engine> engine) {
	while (!engine->IsMaxPower()) {
		engine->Simulation(time_step);
		time_spend += time_step;
		double cur_power = engine->GetPower();
		if (cur_power > max_power) {
			max_power = cur_power;
			speed_at_time = engine->GetSpeed();
		}
	}
}

void TestMaxPower::PrintResult() const {
	std::cout << "Max power: " << max_power << std::endl;
	std::cout << "Speed at Max power: " << speed_at_time << std::endl;
}

void TestOverHeat::RunTest(std::shared_ptr<Engine> engine) {
	const double timeout = 1000.0;
	while (!engine->IsOverHeat() && overheat_time < timeout) {
		engine->Simulation(time_step);
		overheat_time += time_step;
	}
}

void TestOverHeat::PrintResult() const {
	std::cout << "Overheat Time Result: " << overheat_time << std::endl;
}