// bmi.cpp
#include "../include/bmi.hpp"

namespace pt {

    double bmi(double height_cm, double weight_kg) {
        double height_m = height_cm / 100.0;
        return weight_kg / (height_m * height_m);
    }
    
    const char* bmi_category(double bmi_value) {
        if (bmi_value < 18.5) return "Underweight";
        if (bmi_value < 25.0) return "Normal";
        if (bmi_value < 30.0) return "Overweight";
        return "Obese";
    }
    
}