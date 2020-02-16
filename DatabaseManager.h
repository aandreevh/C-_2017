#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Database.h"

namespace Api
{
    
class DatabaseManager{
    
protected:
    
    Database db;
    
public:
    
    DatabaseManager();
    
    
    virtual ~DatabaseManager(){}
    
    
    void printMenu() const;
    void pause() const;
    void clearBuffer() const;
    
    UInput requestInput() const;
    bool handleInput(UInput);
    
    void run();
    
};

    
}

#endif /* DATABASEMANAGER_H */

