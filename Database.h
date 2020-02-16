#ifndef DATABASE_H
#define DATABASE_H

#include<map>
#include<string>

#include "Table.h"

namespace Api{

class Database{
private:
   
protected:
    
    std::string name;
    std::map<std::string,Table> tables;
    
public:
    
    Database();
    Database(std::string);
    Database(const Database&);
    
    virtual ~Database(){}
    
    Database& operator=(const Database&);
    
    std::vector<Table> getTables() const;
    
    
    Table& operator[](const std::string&);
    
    Table& getTable(const std::string&);
    Table& addTable(const Table&,bool fitName= true);
    bool isTable(const std::string&)const;
    void renameTable(const std::string&,const std::string&);
    void deleteTable(const std::string&);
    Table copyTable(const std::string&) const;
    
    
    unsigned int size() const;
    
    
    
    const std::string& getName() const;
    void setName(const std::string&);
    
    Table query(const std::string&, const std::string&,BinaryQuery&) const;
    
    void update(const std::string&, const std::string&,BinaryQuery&);
    
    Table& loadTable(const std::string&);
    void saveTable(const std::string&, const std::string&) const;
    
};
    
}


#endif /* DATABASE_H */

