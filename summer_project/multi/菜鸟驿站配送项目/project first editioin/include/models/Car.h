#ifndef CAR_H
#define CAR_H

namespace models {

    struct Car {
        double speed;       
        double car_weight; 
        double capacity;    

        Car() : speed(0.0), car_weight(0.0), capacity(0.0) {}
        Car(double _speed, double _weight, double _capacity)
            : speed(_speed), car_weight(_weight), capacity(_capacity) {}
    };

}

#endif
