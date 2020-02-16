#include "TableCell.h"
#include "Exception.h"

Api::Cell::Cell()
{
    this->fnull = true;
}

Api::Cell::Cell(const Mixed& val)
{
    this->fnull = false;
    setValue(val);
}

Api::Cell::Cell(const Cell& other)
{
 (*this) = other;   
}

Api::Cell& Api::Cell::operator=(const Api::Cell& other)
{\
    if(other.isNull())this->removeValue();
    else this->setValue(other.getValue());
    
return *this;
}

const Api::Mixed& Api::Cell::getValue() const
{
    if(this->isNull()) throw Api::Exception::exception_cell_value();
    return this->val;
}

bool Api::Cell::isNull() const
{
    return this->fnull;
}

void Api::Cell::removeValue(){
    this->fnull = true;
}

void Api::Cell::setValue(const Mixed& val) {
    this->fnull = false;
    this->val = val;
}


    const std::string Api::Cell::serialize() const
    {
        
        if(isNull())return (std::string)"";
        return getValue().getValString();
    }
        
    void Api::Cell::deserialize(const std::string& val)
    {
        if(val.size() == 0) removeValue();
        else 
        {
            Mixed m;
            m.deserialize(val);
            setValue(m);
        }
    }

bool Api::operator ==(const Cell& f,const Cell& s)
{
  if(f.isNull() || s.isNull())
      return f.isNull() == s.isNull();
  
  return f.getValue() == s.getValue();
}