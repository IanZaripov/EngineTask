#pragma once
#include <vector>
#include <iostream>


class Engine {
public:
    Engine(double I, const std::vector<double>& M,const std::vector<double>& V,
        double T,double Hm,double Hv,double C,double temp);

    virtual ~Engine() = default;

    virtual void Simulation(double time_step) = 0;

    double GetTemperature() const {
        return temperature;
    }

    bool IsOverHeat() const;

    bool IsMaxPower() const;

    virtual double GetPower() const = 0;

    virtual double GetSpeed() const = 0;

    virtual double GetTorque() const = 0;
protected:
    const double moment_of_inertia;                           // I - момент инерции
    const double overheat_temp;                               // Tперегрева
    const double heating_speed_on_torque_coeff;               // HM
    const double heating_speed_of_rotation_crankshaft_coeff;  // HV
    const double cooling_coeff;                               // C
    const double environmental_temperature;
    const std::vector<double> speed_points;
    const std::vector<double> torque_points;
    double temperature = 0.0;
};

class InternalCombustionEngine : public Engine {
public:
    InternalCombustionEngine(double I, const std::vector<double>& M, const std::vector<double>& V,
        double T, double Hm, double Hv, double C, double temp);

    double GetPower() const override;

    double GetSpeed() const override;

    void Simulation(double time_step) override;

    double Interpolation(double speed) const;

    double GetTorque() const override;

private:
    double current_speed = 0.0;
    double current_temperature = 0.0;
};