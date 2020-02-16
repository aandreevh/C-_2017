#include "Table.h"
#include "TableCell.h"
#include "Utils.h"
#include "Exception.h"

using namespace Api;

        Api::Table::Table():Table(""){}
        Api::Table::Table(const std::string& name)
        {
            setName(name);
        }
        
        Api::Table::Table(const std::string& name,const Schema& schema) : Table(name)
        {
            this->schema = schema;
        }
        
        Api::Table::Table(const Table& other)
        {
            setName(other.getName());
            
            schema = Schema();        
            rows.erase(rows.begin(),rows.end());
            
            (*this) = other;
            
        }
        
        
        Table& Api::Table::operator=(const Table& other)
        {
            schema = other.schema;
            setName(other.getName());
            rows.clear();
            
            for(auto e = other.rows.begin();e != other.rows.end();e++)
            {
                (*this) += *e;
            }
            
            return *this;
        }
        
        
        Table& Api::Table::operator+=(const Row& row)
        {   
            addRow(size(),row);
            
            return *this;
        }
        
        Row& Api::Table::operator[](RowID index)
        {
            if(index >= size()) throw Exception::exception_row_index();
            
            return rows[index];
        }
        
         std::vector<Cell> Api::Table::getColumnValues(ColumnID index) const
        {
         std::vector<Cell > cells;
         
         for(RowID  i=0 ;i<size() ;i++)
         {
             cells.push_back(rows[i].getCell(index));
         }
                     
         return cells;
        }
         void Api::Table::pushColumn(ColumnType type)
         {
             addColumn(schema.size(),type);
         }
        void Api::Table::addColumn(ColumnID index,ColumnType type)
        {
            schema.addColumn(index,type);
            
            for(auto e = rows.begin();e != rows.end(); e++)
            {
                (*e).addCell(index,Cell());
            }
        }
        void Api::Table::removeColumn(ColumnID index)
        {
            schema.removeColumn(index);
            
            for(auto e = rows.begin();e != rows.end(); e++)
            {
                (*e).removeCell(index);
            }\

        }
        
        
        Row& Api::Table::addRow(RowID index,const Row& row)
        {
            if(!schema.checkRow(row)) throw Exception::exception_row_validation();
            if(index > size()) throw Exception::exception_row_index();
            
            if(index == size()) rows.push_back(row);
            else rows.insert(rows.begin()+index,row);
            
            return (*this)[index];
            
        }
        
        const Row& Api::Table::getRow(RowID index) const
        {
            
            if(index >= size()) throw Exception::exception_row_index();
            return rows[index];     
            
        }
        
        Row& Api::Table::pushRow(const Row& row)
        {
            return addRow(size(),row); 
        }
        
        void Api::Table::removeRow(RowID index)
        {         
            if(index >=size()) throw Exception::exception_row_index();
            
            rows.erase(rows.begin()+ index);
            
        }
        
        
        void Api::Table::setName(const std::string& name)
        {
            this->name = name;
        }
        const std::string& Api::Table::getName() const
        {
            return this->name;
        }
        
        const Schema& Api::Table::getSchema() const
        {
            return schema;
        }
        
        unsigned int Api::Table::size() const
        {
            return rows.size();
        }
        
        
        Table Api::Table::query(UnaryQuery& query) const
        {
            Table t(getName()+"_query",query.buildSchema(this->schema));
            
            for(auto e = rows.begin();e!= rows.end();e++)
            {
                std::vector<Row> nrows = query.execute(*e);
                for(auto u = nrows.begin();u != nrows.end();u++)
                {
                    t += (*u);
                }
            }
            
            query.reset();
            
            return t;
        }
        
        void Api::Table::update(UnaryQuery& query)
        {
               Table t(getName(),query.buildSchema(this->schema));
            
            for(auto e = rows.begin();e!= rows.end();e++)
            {
                std::vector<Row> nrows = query.execute(*e);
                for(auto u = nrows.begin();u != nrows.end();u++)
                {
                    t += (*u);
                }
            }
            
            query.reset();
            
            (*this) = t;
        }
        
        void Api::Table::deserialize(const std::string& val)
        {
                  rows.clear();
            
            std::string s = val;
            int pos = 0;
            int counter = 0;
        while ((pos = s.find((char)3)) != std::string::npos)
        {
            std::string ss =  s.substr(0,pos);
            
            counter ++;
            
            if(counter == 1)
            {
                //for name
                setName(ss);
            } else if (counter ==2)
            {
                // for schema
                
                schema.deserialize(ss);
                
            }else
            {
                  // for rows
                
                Row r;
                r.deserialize(ss);
                rows.push_back(r);     
               
            }
            
            s.erase(0, pos + 1);
      
        }
            
        }
        const std::string Api::Table::serialize() const
        {
            std::string out = "";
            out += getName();
            out += (char)3;
            out += schema.serialize();
            out += (char)3;
            
            for(auto e = rows.begin();e != rows.end(); e++)
            {
               out += (*e).serialize();
               out += (char)3;
            }
            
            return out;
                 
        }
        
        
        bool Api::operator==(const Table& f,const Table& s)
        {
            if(!(f.schema == s.schema))return false;
            
            auto rf = f.rows.begin();
            auto rs = s.rows.begin();
            
            while(rf != f.rows.end())
            {
                if(!((*rf) == (*rs))) return false;
                
                rf++;
                rs++;
            }
        }
    