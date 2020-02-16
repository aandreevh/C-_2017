#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H

#include "Definitions.h"
#include "TableRow.h"

#include <vector>

namespace Api
{
    
    
    
class Schema : public Serializable
{
    
protected:
    
    std::vector<ColumnType> schema;
    
    bool isType(ColumnType) const;
    
public:
    
    Schema();
    Schema(const Schema&);
    
    virtual ~Schema() {}
    
    Schema& operator= (const Schema&);
    
    
    Schema& operator+=(const Schema&);
    Schema& operator+=(ColumnType);
    
    ColumnType& operator[](ColumnID);
    
     unsigned int size() const;
     
    ColumnType getColumnType(ColumnID) const;
    
    void addColumn(ColumnID,ColumnType);
    
    void modifyColumn(ColumnID,ColumnType);
    
    void removeColumn(ColumnID);
    
    bool checkRow(const Row&) const;
   

    void deserialize(const std::string&);
    const std::string serialize() const;


    
    
    
};

bool operator==(const Schema&,const Schema&);

}
#endif /* TABLESCHEMA_H */

