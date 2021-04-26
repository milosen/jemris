#ifndef SPOILERPULSE_H
#define SPOILERPULSE_H

#include "GradPulse.h"

class SpoilerPulse : public GradPulse {
 public:
    // Constructor
    SpoilerPulse() {}
    // Copy constructor.
    SpoilerPulse(const SpoilerPulse&) {}
    // Destructor.
    ~SpoilerPulse() {}
    // Cloning mechanism
    SpoilerPulse* Clone() const;
    // Prepare the spiral gradient pulse.
    // Please refer to above.
    virtual bool Prepare(PrepareMode mode);
    // Get gradient amplitude.
    // Please refer to GetMagnitude above.
    virtual double GetGradient (double const time);
    char16_t ch='T'; // T for test
 protected:
    // Get information for output.
    virtual string GetInfo ();
    // Constants as described in the paper.
    double m_A;
    double m_N;
};

#endif // SPOILERPULSE_H
