#pragma once
#include <iostream>
#include "Engine.h"
#include <memory>

class Test {
public:
	virtual void RunTest(std::shared_ptr<Engine> engine)  = 0;
	virtual void PrintResult() const = 0;

protected:
	const double time_step = 0.1;
};

class TestMaxPower : public Test {
public:
	void RunTest(std::shared_ptr<Engine> engine) override;
	void PrintResult() const override;
private:
	double max_power = 0.0;
	double speed_at_time = 0.0;
	double time_spend = 0.0;
};

class TestOverHeat : public Test {
public:
	void RunTest(std::shared_ptr<Engine> engine) override;
	void PrintResult() const override;
private:
	double overheat_time = 0.0;
};