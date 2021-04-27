#include "SpoilerPulse.h"

double SpoilerPulse::GetGradient (double const time)  {
    return 0.0;
}

bool SpoilerPulse::Prepare(PrepareMode mode)   {
    return true;
}

string SpoilerPulse::GetInfo() {
    // Debug output
    stringstream s;
    s << GradPulse::GetInfo();
    return s.str();
}
