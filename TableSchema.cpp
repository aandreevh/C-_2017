#include "TableSchema.h"
#include "Utils.h"
#include "Exception.h"

#include <string>

using namespace Api;

    Api::Schema::Schema(){}
    
    Api::Schema::Schema(const Schema& other)
    {
        (*this) = other;
    }
    
   
    
    Schema& Api::Schema::operator= (const Schema& other)
    {
        schema.erase(schema.begin(),schema.end());
        
        (*this)+= other;
        
        return *this;
    }
    
    
    Schema& Api::Schema::operator+=(const Schema& other)
    {
        for(auto e = other.schema.begin();e != other.schema.end();e++)
            (*this)+= *e;
        
        return *this;
        
    }
    Schema& Api::Schema::operator+=(ColumnType type)
    {
        addColumn(size(),type);       
        return *this;
    }
    
    ColumnType& Api::Schema::operator [](ColumnID index)
    {
        if(index >= size()) throw Exception::exception_schema_index();
        
        return schema[index];
    }
    
     unsigned int Api::Schema::size() const
     {
         return schema.size();
     }
     
    ColumnType Api::Schema::getColumnType(ColumnID index) const
    {
        if(index >= size()) throw  Exception::exception_schema_index();
        
        return schema[index];
    }
    
    void Api::Schema::addColumn(ColumnID index,ColumnType type)
    {
        if(!isType(type)) throw Exception::exception_column_type();
        if(index > size()) throw Exception::exception_schema_index();
        
        if(index == size()) schema.push_back(type);
        else schema.insert(schema.begin() + index,type);
    }
    
    void Api::Schema::modifyColumn(ColumnID index,ColumnType type)
    {
        if(!isType(type)) throw Exception::exception_column_type();
        if(index >= size()) throw Exception::exception_schema_index();
    
        schema[index] = type;
        
    }
    void Api::Schema::removeColumn(ColumnID index)
    {
        if(index >= size()) throw Exception::exception_schema_index();
      
        schema.erase(schema.begin() + index);
        
    }
    
    bool Api::Schema::isType(ColumnType type) const
    {
        return (type == Api::CTYPE_INT) ||(type == Api::CTYPE_FLOAT) || (type == Api::CTYPE_STRING);
    }
    
    bool Api::Schema::checkRow(const Row& row) const
    {
       
            if(row.size() != size()) return false;
            
            for(ColumnID index =0;index<size();index++)
            {
                if(row.getCell(index).isNull()) continue;
                
                switch(getColumnType(index))
                {
                    case Api::CTYPE_INT:
                        if(!Utils::isNumber(row.getCell(index).getValue().getValString())) return false;
                         break;
                         
                    case Api::CTYPE_FLOAT:
                        if(!Utils::isFloat(row.getCell(index).getValue().getValString())) return false;
                        break;
                        
                    case Api::CTYPE_STRING:
                        break;
                        
                    default:
                        throw Exception::exception_column_type();
                        break;
                }
            }
            
            return true;
    }
    
    void Api::Schema::deserialize(const std::string& val)
    {
       
            schema.clear();
        
            std::string s = val;
            int pos = 0;
            
        while ((pos = s.find((char)2)) != std::string::npos)
        {
            
            schema.push_back((Mixed(s.substr(0, pos)).getValInteger()));          
            s.erase(0, pos + 1);

        }
            
    }
     
    const std::string Api::Schema::serialize() const
    {
        std::string out = "";
        
        for(auto e = schema.begin(); e != schema.end();e++)
        {
            out += std::to_string((*e));
            out += (char)2;
        }
        
        return out;
        
    }
    
    bool Api::operator==(const Schema& f,const Schema& s)
    {
        if(f.size() != s.size()) return false;
        for(ColumnID i =0;i<s.size();i++) if(f.getColumnType(i) != s.getColumnType(i)) return false;
        return true;
    }
    
    
    
    
    