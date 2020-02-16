#include "TableRow.h"
#include "Exception.h"

using namespace Api;

        Api::Row::Row(){}
        
        Api::Row::Row(const Row& other)
        {
            (*this) = other;
        }
       
    
        Row& Api::Row::operator=(const Row& other)
        {
            cells.erase(cells.begin(),cells.end());
            (*this) += other;
            
            return *this;
        }
        
        Row& Api::Row::operator+=(const Row& other)
        {
            for(auto e = other.cells.begin();e != other.cells.end(); e++)
                (*this) += *e;
            
            return *this;
        }
        
        Row& Api::Row::operator+=(const Cell& c)
        {
            addCell(size(),c);
            return *this;
        }
        
        Cell& Api::Row::operator[](CellID index)
        {
            if(index >= size()) throw Exception::exception_cell_index();
            
            return cells[index];
            
        }
        
        unsigned int Api::Row::size() const
        {
            return cells.size();
        }
        
        const Cell& Api::Row::getCell(CellID index) const
        {
            
            if(index >= size()) throw Exception::exception_cell_index();
            
            return cells[index];
            
        }
        
        Cell& Api::Row::pushCell(const Cell& c)
        {
            return addCell(size(),c);
        }
        
        Cell& Api::Row::addCell(CellID index,const Cell& c)
        {
            if(index > size()) throw Exception::exception_cell_index();
            
            if(index == size()) cells.push_back(c);
            else cells.insert(cells.begin()+ index,c);
            
            return cells[index];
            
        }
        
        Cell& Api::Row::addCell(CellID index)
        {
            return (*this).addCell(index,Cell());
        }
        
        Cell& Api::Row::modifyCell(CellID index,const Cell& c)
        {
            if(index >= size()) throw Exception::exception_cell_index();
            
            cells[index] = c;
            return cells[index];
        }
        
        void Api::Row::removeCell(CellID index)
        {
         if(index >= size()) throw Exception::exception_cell_index();
         
         cells.erase(cells.begin() + index);
            
        }
        
        
        const std::string Api::Row::serialize() const
        {
            std::string out="";
            
            for(auto e = cells.begin();e != cells.end();e++)
            {
                out += (*e).serialize();
                out += (char)1;
            }
            
            return out;
            
        }
        
        void Api::Row::deserialize(const std::string& val)
        {
            cells.clear();
            
            std::string s = val;
            int pos = 0;
        while ((pos = s.find((char)1)) != std::string::npos)
        {
            Cell c;
            
            c.deserialize(s.substr(0, pos));
            s.erase(0, pos + 1);
            
            (*this)+=c;
            
        }
            
        }
        
        
        bool Api::operator ==(const Row& f, const Row& s)
        {
            if(f.size() != s.size()) return false;
            
            for(CellID i =0;i<f.size();i++) if(!(f.getCell(i) == s.getCell(i))) return false;
            
            return true;
            
        }