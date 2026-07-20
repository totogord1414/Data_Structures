#ifndef  PACKAGE_H
#define PACKAGE_H

namespace models {

    struct Package {
        int id;             
        double weight;      
        int dest;           
        double arrive_time; 
        double deadline;    

        Package() : id(-1), weight(0.0), dest(-1), arrive_time(0.0), deadline(0.0) {}
        Package(int _id, double _w, int _dest, double _arrive, double _deadline)
            : id(_id), weight(_w), dest(_dest), arrive_time(_arrive), deadline(_deadline) {}
    };

}

#endif
