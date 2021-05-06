#include "SpoilerPulse.h"

double SpoilerPulse::GetGradient (double const time)  {
    return 0.0;
}

string SpoilerPulse::GetInfo() {
    // Debug output
    stringstream s;
    s << TrapGradPulse::GetInfo();
    return s.str();
}
