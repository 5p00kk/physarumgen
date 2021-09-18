/* TODO better solution for different spawners */

#include "simulation.h"
#include "utils.h"
#include <iostream>

c_simulation::c_simulation(unsigned int width, unsigned int height)
    : m_world{width, height}
    , m_world_sampler{width, height}
    , m_width{width}
    , m_height{height}
{

}


void c_simulation::spawn_world(unsigned int width, unsigned int height)
{
    /* Stop recording as image size might change */
    m_recorder.stop_recording();

    /* Clear old world's agents */
    m_agents.clear();

    /* Create a new empty world */
    m_world = c_world(width, height);
    m_width = width;
    m_height = height;
    m_ticks = 0;

    /* Reset the sampler */
    m_world_sampler.reset_range(width, height);
}


void c_simulation::set_world_diffusion(unsigned int diff_size)
{
    m_world.set_diffusion(diff_size);
}


void c_simulation::set_world_decay(float decay_mult, float decay_sub)
{
    m_world.set_decay(decay_mult, decay_sub);
}


bool c_simulation::spawn_agents_uniform(float world_percentage)
{
    bool ret_val = true;

    /* Calculate how many agents are requested */
    unsigned int world_area = m_width * m_height;
    unsigned int num_agents = (unsigned int)(world_percentage * world_area);
    
    /* Make sure that there are not too many agents requested */
    if(num_agents >= world_area)
    {
        std::cout << "<c_world::spawn_agents>: Could not spawn agents" << std::endl;
        return false;
    }

    /* (Re)spawn agents */
    m_agents.clear();
    m_agents.reserve(num_agents);
    for(int i=0; i<num_agents; i++)
    {
        s_ui_vec2 tmp_pos = m_world_sampler.get_next_position();
        if(m_world.place_agent(tmp_pos))
        {
            m_agents.emplace_back(std::make_unique<c_physarum>((float)tmp_pos.x, (float)tmp_pos.y, random_angle(), &m_world));
        }
        else
        {
            std::cout << "<c_world::spawn_agents>: Invalid spawn position" << std::endl;
            ret_val = false;
        }
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    return ret_val;
}


bool c_simulation::spawn_agents_square(unsigned int square_side)
{
    /* Check if the square can fit into the world */
    if(square_side > m_width || square_side > m_height)
    {
        std::cout << "<c_world::spawn_agents>: Could not spawn agents" << std::endl;
        return false;
    }

    bool ret_val = true;
    s_ui_vec2 spawn_corner = {(m_width-square_side)/2, (m_height-square_side)/2};
    unsigned int num_agents = square_side*square_side;

    /* (Re)spawn agents */
    m_agents.clear();
    m_agents.reserve(num_agents);
    for(int i=0; i<num_agents; i++)
    {
        s_ui_vec2 tmp_pos = {(spawn_corner.x + i%square_side), (spawn_corner.y + i/square_side)};
        if(m_world.place_agent(tmp_pos))
        {
            m_agents.emplace_back(std::make_unique<c_physarum>((float)tmp_pos.x, (float)tmp_pos.y, random_angle(), &m_world));
        }
        else
        {
            std::cout << "<c_world::spawn_agents>: Invalid spawn position" << std::endl;
            ret_val = false;
        }
    }

    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;

    return ret_val;
}


bool c_simulation::spawn_agents_circle(unsigned int circle_radius)
{
    /* Check if the square can fit into the world */
    if(2*circle_radius > m_width || 2*circle_radius > m_height)
    {
        std::cout << "<c_world::spawn_agents>: Could not spawn agents" << std::endl;
        return false;
    }

    bool ret_val = true;
    /* (Re)spawn agents */
    m_agents.clear();
    /* For now reserve more than needed */
    m_agents.reserve(4*circle_radius*circle_radius);

    /* Go through square and find points inside of the circle */
    for(int i=-1*(int)circle_radius; i<(int)circle_radius; i++)
    {
        for(int j=-1*(int)circle_radius; j<(int)circle_radius; j++)
        {
            if((int)sqrt((i*i)+(j*j))<=circle_radius)
            {
                /* Point is inside of the spawn circle */
                /* Add the agent */
                s_ui_vec2 tmp_pos = {(i+(int)m_width/2), (j+(int)m_height/2)};
                if(m_world.place_agent(tmp_pos))
                {
                    m_agents.emplace_back(std::make_unique<c_physarum>((float)tmp_pos.x, (float)tmp_pos.y, random_angle(), &m_world));
                }
                else
                {
                    std::cout << "<c_world::spawn_agents>: Invalid spawn position" << std::endl;
                    ret_val = false;
                }
            }
        }
    }
    std::cout << "Spawned " << m_agents.size() << " agents" << std::endl;
    return ret_val;
}

void c_simulation::start_recording(const std::string &path)
{
    m_recorder.new_recording(2*m_width, m_height, path);
}


void c_simulation::tick()
{
    /* Shuffle agent to avoid emergent patterns due to move sequence */
    /* TODO - this seems slow, potential optimization */
    std::random_shuffle(m_agents.begin(), m_agents.end());

    for(auto &agent : m_agents) 
    {
        agent->movement_step();
    }

    for(auto &agent : m_agents) 
    {
        agent->sensing_step();
    }

    /* Update world */
    m_world.diffuse();
    m_world.decay();
    
    /* DIsplay world */
    m_world.display(1);

    /* If simulation recording is running, add frames */
    if(m_recorder.m_recording)
    {
        /* Add frame to video */
        m_recorder.video_add_frame(m_world.get_world_snap());

        /* Save every 100th image */
        if(m_ticks%100 == 0)
        {
            m_recorder.save_image(m_world.get_world_snap());
        }
    }

    m_ticks++;
}