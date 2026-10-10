#ifndef GEARLEVER_HPP
#define GEARLEVER_HPP

#include "Singleton.hpp"
#include "Gear.hpp"

// Hereda de Singleton pasándose a sí misma como tipo <T>
class GearLever : public Singleton<GearLever> {
    // Permitimos que la plantilla Singleton acceda al constructor privado de GearLever
    friend class Singleton<GearLever>;

private:
    Gear    _gears[6]; //Composición
    int     _level;

    // El constructor es privado para que NADIE pueda hacer "GearLever lever;" en el main
    GearLever() : _level(0) {} 
    ~GearLever() {}

public:
    void change();
    Gear* activeGear();
};

#endif
