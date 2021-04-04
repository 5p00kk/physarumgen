#include <iostream>
#include "simulation.h"

int main()
{
    c_simulation simulation(600, 600);
    simulation.spawn_agents(0.05);
    
    for(int i=0;i<10000;i++)
    {
        simulation.tick();
    }
}