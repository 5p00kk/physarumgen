#include <iostream>
#include "simulation.h"

int main()
{
    /* Simulation params */
    const int world_width = 300;
    const int world_height = 600;
    float population = 0.1;
    float decay_mult = 0.1f;
    float decay_sub = 0.5f;
    unsigned int diff_size = 3;

    /* Prepare simulation */
    c_simulation simulation(world_width, world_height);
    simulation.spawn_agents_uniform(population);
    simulation.set_world_decay(decay_mult, decay_sub);
    simulation.set_world_diffusion(diff_size);

    /* Start recording */
    simulation.start_recording("rec/");

    /* Run simulation */   
    for(int i=0;i<300;i++)
    {
        simulation.tick();
    }
}