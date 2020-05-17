#pragma once
#include <vector>
#include "simulation.h"

namespace corsim
{
    class MovementStrategy
    {
        public:
        virtual int move(int dt, std::vector<Subject> &subjects, int week) = 0;
    };

    class NormalMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
    };

    class LockdownMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
        private:
        bool run;
    };

    class RestrictedMovement: public MovementStrategy
    {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
        private:
        bool run;
    };
}