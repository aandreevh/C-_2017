#include "Database.h"
#include "Exception.h"

#include <fstream>
#include <streambuf>

using namespace Api;


    Api::Database::Database(): Database(""){}
    
    Api::Database::Database(std::string name)
    {
        setName(name);
    }
    
    Api::Database::Database(const Database& other)
    {
        (*this) = other;   
    }
    
    Database& Api::Database::operator=(const Database& other)
    {
        
        tables.clear();
        
        setName(other.getName());
        
        std::vector<Table> otable = other.getTables();
        
        for(auto e= otable.begin(); e != otable.end(); e++)
            addTable(*e);
        
        return (*this);
    }
    
    std::vector<Table> Api::Database::getTables() const
    {
     std::vector<Table> out;
     
     for(auto it = tables.begin(); it != tables.end(); ++it) 
      out.push_back(it->second);
    
     return out;
     
    }
    
    Table& Api::Database::getTable(const std::string& name)
    {
        if(!isTable(name)) throw Exception::exception_invalid_table();
        
        return tables[name];
        
    }
    Table& Api::Database::addTable(const Table& other,bool fitName)
    {
        if(fitName)
        {
            
        std::string nname = other.getName();
        while(isTable(nname)) nname += "_";
        
        Table temp = other;
        temp.setName(nname);
        tables[temp.getName()] = temp;
        
        return tables[temp.getName()];
        }
        
        if(isTable(other.getName())) throw Exception::exception_invalid_table();
        
        tables[other.getName()] = other;
        
        return tables[other.getName()];
        
    }
    bool Api::Database::isTable(const std::string& name)const
    {
        return (tables.find(name) != tables.end());
    }
    
    void Api::Database::renameTable(const std::string& table, const std::string& name)
    {
        if(!isTable(table)) throw Exception::exception_invalid_table();
        if(table == name) ;
        if(isTable(name)) throw Exception::exception_invalid_table();
        
        Table t = tables[table];
        t.setName(name);
        
        deleteTable(table);
        addTable(t);
    }
    
    void Database::deleteTable(const std::string& name) 
    {
        if(!isTable(name)) throw Exception::exception_invalid_table();
        
        tables.erase( tables.find(name));
    }

    Table Database::copyTable(const std::string& name) const
    {
        if(!isTable(name)) throw Exception::exception_invalid_table();
        
        return tables.at(name);
        
    }
    const std::string& Api::Database::getName() const
    {
        return name;
    }
    void Api::Database::setName(const std::string& name)
    {
        this->name = name;
    }
    
    Table& Api::Database::operator[](const std::string& name)
    {
         if(!isTable(name)) throw Exception::exception_invalid_table();
         
         return tables[name];
    }
    
    unsigned int Api::Database::size() const
    {
        return tables.size();
    }
    
   
    Table Api::Database::query(const std::string& first,const std::string& second,BinaryQuery& query) const
    {
        if(!isTable(first)) throw Exception::exception_invalid_table();
        if(!isTable(second)) throw Exception::exception_invalid_table();
        
        
       Table ftable = copyTable(first);
       Table stable = copyTable(second);
        
        Table outt(ftable.getName() + "_"+stable.getName()+"_query",query.buildSchema(ftable.getSchema(),stable.getSchema()));
        
        
        for(RowID a = 0; a<ftable.size();a++)
        {
            for(RowID b=0;b<stable.size();b++)
            {
               std::vector<Row> outr = query.execute(ftable[a],stable[b]);
               
                for(auto c = outr.begin();c != outr.end();c++)
                    outt += (*c);
                
            }
        }
        
        query.reset();
        
        return outt;
        
    }
    
    void Api::Database::update(const std::string& first,const std::string& second,BinaryQuery& query)
    {
        
        
        if(!isTable(first)) throw Exception::exception_invalid_table();
        if(!isTable(second)) throw Exception::exception_invalid_table();
        
        
       Table ftable = copyTable(first);
       Table stable = copyTable(second);
        
        Table outt(ftable.getName(),query.buildSchema(ftable.getSchema(),stable.getSchema()));
        
        for(RowID a = 0; a < ftable.size();a++)
        {
            for(RowID b=0;b<stable.size();b++)
            {
                std::vector<Row> outr = query.execute(ftable[a],stable[b]);
                for(auto c = outr.begin();c != outr.end();c++)
                    outt += *c;
            }
        }
        
        query.reset();
        
        tables[first] = outt;
    }
    
    
    Table& Api::Database::loadTable(const std::string& filename)
    {
       
        
                std::ifstream handle(filename);
                std::string str((std::istreambuf_iterator<char>(handle)),std::istreambuf_iterator<char>());
                
                
                Table ntable;
                ntable.deserialize(str);
                
               Table& tbl= (*this).addTable(ntable);
                
                handle.close();
                
                return tbl;
        
    }
    
    void Api::Database::saveTable(const std::string& filename,const std::string& tablename) const
    {
        
        std::string str = copyTable(tablename).serialize();
        
        std::ofstream handle(filename);
        
        handle<<str;
        
        handle.close();
        
    }