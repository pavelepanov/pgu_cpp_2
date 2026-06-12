#ifndef INFRASTRUCTURE_DEAL_FILE_READER_H
#define INFRASTRUCTURE_DEAL_FILE_READER_H

#include "domain/Deal.h"

#include <string>

class DealFileReader {
public:
    Deal readFromFile(const std::string& path) const;
};

#endif
