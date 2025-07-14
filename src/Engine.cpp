#include "Engine.h"

using namespace std;

Engine::Engine(double I, const std::vector<double>& M, const std::vector<double>& V,
    double T, double Hm, double Hv, double C, double temp) : 
    moment_of_inertia(I),torque_points(M),
    speed_points(V),overheat_temp(T), 
    heating_speed_on_torque_coeff(Hm),
    heating_speed_of_rotation_crankshaft_coeff(Hv),
    cooling_coeff(C), 
    environmental_temperature(temp) {
};


InternalCombustionEngine::InternalCombustionEngine(double I,const std::vector<double>& M, const std::vector<double>& V,
    double T,double Hm,double Hv,double C,double temp) : Engine(I,M,V,T,Hm,Hv,C,temp) {

}

double InternalCombustionEngine::GetPower() const {
    return (GetTorque()*current_speed) / 1000;
}

double InternalCombustionEngine::GetSpeed() const {
    return current_speed;
}

bool Engine::IsMaxPower() const {
    return std::abs(GetTorque()) < 0.00001;
}

bool Engine::IsOverHeat() const {
    return temperature >= overheat_temp;
}


void InternalCombustionEngine::Simulation(double time_step) {
    double cur_torque = GetTorque();
    double a = cur_torque / moment_of_inertia;
    current_speed = std::max(0.0, current_speed + a * time_step);

    double heating_rate = cur_torque * heating_speed_on_torque_coeff +
        (current_speed * current_speed) * heating_speed_of_rotation_crankshaft_coeff;
    double cooling_rate = cooling_coeff * (environmental_temperature - temperature);
    temperature += (heating_rate + cooling_rate) * time_step;

}

double InternalCombustionEngine::Interpolation(double speed) const {
    if (speed <= speed_points.front()) return torque_points.front();
    if (speed >= speed_points.back()) return 0.0;
    
    for (size_t i = 0; i < speed_points.size() - 1; ++i) {
        if (speed >= speed_points[i] && speed <= speed_points[i+1]) {
            double t = (speed - speed_points[i]) / (speed_points[i+1] - speed_points[i]);
            return torque_points[i] + t * (torque_points[i+1] - torque_points[i]);
        }
    }
    return 0.0;
}

double InternalCombustionEngine::GetTorque() const {
    return Interpolation(current_speed);
}