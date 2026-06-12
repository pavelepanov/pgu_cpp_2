#ifndef APPLICATION_DEAL_VALIDATOR_H
#define APPLICATION_DEAL_VALIDATOR_H

#include "domain/Deal.h"

class DealValidator {
public:
    void validate(const Deal& deal) const;
};

#endif
