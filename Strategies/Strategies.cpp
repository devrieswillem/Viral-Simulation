#include "Strategies.h"

namespace corsim
{
    int RegularMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        int numberInfected = 0;
        for(Subject& s : subjects)
        {
            s.set_x(s.x() + s.dx() * dt);
            s.set_y(s.y() + s.dy() * dt);
            if(s.infected())
            {
                numberInfected++;
            }
        }
        return numberInfected;
    }

    int LockdownMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        if (run == NULL)
        {
            int num = subjects.size()/4*3;

            for (int i = 0; i < num; i++)
            {
                subjects.at(i).setLocked(true);
            }
            
            run = true;
        }

        int numberInfected = 0;

        for (Subject& s : subjects)
        {
            if (s.getLocked() != true)
            {
                s.set_x(s.x() + s.dx() * dt);
                s.set_y(s.y() + s.dy() * dt);
            }
            if(s.infected())
            {
                numberInfected++;
            }
        }
        
        return numberInfected;
    }
}