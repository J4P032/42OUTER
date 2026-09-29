#include "Vect2.hpp"
#include "Graph.hpp"
#include <iostream>
#include <iomanip>

int main() {
    try{
        Vect2 p1(0,0);
        Vect2 p2(2,2);
        Vect2 p3(4,2);
        Vect2 p4(2,4);
        Vect2 p5(-1,3);
        Graph g(5.0f, 5.0f);
        g.add_point(p1);
        g.add_point(p2);
        g.add_point(p3);
        g.add_point(p4);
        g.add_point(p5);
        g.print_graph();
    }
    catch (const std::exception& e){
        std::cout << "Error atrapado: " << e.what() << std::endl;      
    }

    return 0;
}
