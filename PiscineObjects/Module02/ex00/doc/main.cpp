#include "GearLever.hpp"

int main() {
    // ERROR DE COMPILACIÓN:
    // GearLever miPalanca; 

    // FORMA CORRECTA (Acceder al Singleton):
    GearLever& palanca = GearLever::getInstance();
    GearLever& palanca2 = GearLever::getInstance();

    //palanca.change(); // Usar sus métodos normalmente
    
    return 0;
}
