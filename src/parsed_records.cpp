#include "parsed_records.h"

ParsedRecords::~ParsedRecords()
{
    for (auto const & record : this->records) {
        delete record;
    }
}

void ParsedRecords::AddRecord(Record * record) {
    this->records.push_back(record);
}

int ParsedRecords::GetRecordCount() {
    return this->records.size();
}

Record * ParsedRecords::GetRecord(int index) {
    return this->records.at(index);
}
