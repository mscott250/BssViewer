#ifndef PARSED_RECORDS_H
#define PARSED_RECORDS_H

#include "record.h"

#include <deque>

class ParsedRecords
{
public:
    ~ParsedRecords();

    void AddRecord(Record * record);
    int GetRecordCount();
    Record * GetRecord(int index);

private:
    std::deque<Record *> records;
};

#endif // PARSED_RECORDS_H
