#ifndef TABLEROW_H
#define TABLEROW_H

#include "TableCell.h"
#include "Definitions.h"
#include <vector>

namespace Api
{
    
    
        
    class Row :public Serializable
    {
        
    protected:
        
        std::vector<Cell> cells;
    
    public:
        
        Row();
        Row(const Row&);
        
        virtual ~Row() {}
    
        Row& operator=(const Row&);
        
        Row& operator+=(const Row&);
        
        Row& operator+=(const Cell&);
        
        Cell& operator[](CellID);
        
        unsigned int size() const;
        
        const Cell& getCell(CellID) const;
        
        Cell& addCell(CellID,const Cell&);
        Cell& addCell(CellID);
        Cell& pushCell(const Cell&);
        
        Cell& modifyCell(CellID,const Cell&);
        
        void removeCell(CellID);    

        const std::string serialize() const;
        void deserialize(const std::string&);


    
    };
    
    bool operator==(const Row&,const Row&);
    
}


#endif /* TABLEROW_H */

