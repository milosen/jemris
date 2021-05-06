#ifndef SPOILERPULSE_H
#define SPOILERPULSE_H

#include "TrapGradPulse.h"

class SpoilerPulse : public TrapGradPulse {
 public:
    // Default constructor
    SpoilerPulse() {};
    // Default copy constructor.
    SpoilerPulse  (const SpoilerPulse&) {};
    // Default destructor.
    ~SpoilerPulse () {};
    // Cloning mechanism as descibed by Gamma et al "Design patterns"
    inline SpoilerPulse* Clone() const { return (new SpoilerPulse(*this)); };
    // Returns a constant Magnitude for all times.
    //
    // param time. The magnitude is requested for "time". Offset is the start time of the pulse.
    // returns     Magnitude at time "time".
    inline virtual double GetGradient (double const time );
 private:
    // Get information for output.
    virtual string GetInfo ();
};

#endif // SPOILERPULSE_H
