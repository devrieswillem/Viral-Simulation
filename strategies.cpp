#include "strategies.h"

namespace corsim
{
    int NormalMovement::move(int dt, std::vector<Subject> &subjects, int week)
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
            // 75 procent of subjects which will be stopped
            int num = subjects.size()*0.75;
            // stop the selected 75 procent of subjects
            for (int i = 0; i < num; i++)
            {
                subjects.at(i).setLocked(true);
            }
            
            run = true;
        }

        int numberInfected = 0;
        // move the subject if its not in the stop group
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

    int RestrictedMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        // select half of the subjects
        int halfSubjects = subjects.size() * 0.5;
        // which subjects of the 75 procent will be slowed
        int slowedSubjects = subjects.size() * 0.75;
        // the speed of which the slowed subjects will be moving at
        int dtSlowed = dt * 0.35;
        int numberInfected = 0;

        for (int i = 0; i < slowedSubjects; i++)
        {
            subjects.at(i).setSlow(true);
        }
        

        for (Subject& s : subjects)
        {
            if (s.infected())
            {
                numberInfected++;
            }
            // when less than half of the subjects are infected move normally
            if(numberInfected < halfSubjects)
            {
                s.set_x(s.x() + s.dx() * dt);
                s.set_y(s.y() + s.dy() * dt);  
            }
            // slow 75 procent of the subjects if more than half of the population is infected
            else if(numberInfected >= halfSubjects)
            {
                // reduce the movementspeed of 75 procent
                if (s.slow() == true)
                {
                    s.set_x(s.x() + s.dx() * dtSlowed);
                    s.set_y(s.y() + s.dy() * dtSlowed);
                }

                // otherwise if the person doesn't belong to the 75 procent, keep them moving at the normal speed
                else 
                {
                    s.set_x(s.x() + s.dx() * dt);
                    s.set_y(s.y() + s.dy() * dt);
                }
            }
        }
        return numberInfected;
    }
}