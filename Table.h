#ifndef TABLE_H
#define TABLE_H


#include <string>
#include <vector>

#include "TableRow.h"
#include "TableSchema.h"
#include "Query.h"
#include "Definitions.h"


namespace Api
{
    
    
    
    class Table : public Serializable
    {
        
    protected:
        
        std::string name;
        
        Schema schema;
        std::vector<Row> rows;
        
    public:
        
        Table();
        Table(const std::string&);
        Table(const std::string&,const Schema&);
        Table(const Table&);
        
        virtual ~Table() {}
        
        Table& operator=(const Table&);
        
        Table& operator+=(const Row&);
        
        Row& operator[](RowID);
        
        void addColumn(ColumnID,ColumnType);
        void pushColumn(ColumnType);
        void removeColumn(ColumnID);
        
        Row& addRow(RowID,const Row&);
        Row& pushRow(const Row&);
        const Row& getRow(RowID) const;
        void removeRow(RowID);
        
        std::vector<Cell> getColumnValues(ColumnID) const;
        
        void setName(const std::string&);
        const std::string& getName() const;
        
        
        const Schema& getSchema() const;
        
        unsigned int size() const;
        
        
        Table query(UnaryQuery&) const;
        
        void update(UnaryQuery&);
        

        void deserialize(const std::string&);
        const std::string serialize() const;


        
        friend bool operator==(const Table&,const Table&);
    };
    
    
    
}

#endif /* TABLE_H */

