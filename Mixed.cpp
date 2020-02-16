#include "Mixed.h"
#include "Utils.h"
#include "Exception.h"


    Api::Mixed::Mixed():Mixed(""){}
    
    
    Api::Mixed::Mixed(const std::string& val)
    {
        setValue(val);
    }
    
    Api::Mixed::Mixed(int val)
    {
        setValue(val);
    }
    
    Api::Mixed::Mixed(float val)
    {
        setValue(val);
    }
    
    Api::Mixed::Mixed(const Mixed& other)
    {
      (*this) = other;  
    }
    
    
    Api::Mixed& Api::Mixed::operator=(const Mixed& other)
    {
        setValue(other.getValString());
        
        return *this;
    }
    
    void Api::Mixed::setValue(int val)
    {
        this->value = std::to_string(val);
    }
    
    void Api::Mixed::setValue(float val)
    {
        this->value = std::to_string(val);
    }
    
    void Api::Mixed::setValue(const std::string& val)
    {
        this->value = val;
    }
    
    int Api::Mixed::getValInteger() const
    {
        if(!Api::Utils::isNumber(this->value.c_str()))throw Api::Exception::exception_mixed_cast();
        
        return atoi(this->value.c_str());
    }
    
    float Api::Mixed::getValFloat() const
    {
        if(!Api::Utils::isFloat(this->value.c_str())) throw Api::Exception::exception_mixed_cast();
        return atof(this->value.c_str());
    }
    
    const std::string& Api::Mixed::getValString() const
    {
        return this->value;
    }
    
    bool Api::operator ==(const Api::Mixed& f, const Api::Mixed& s)
    {
        return f.getValString() == s.getValString();
    }
    
    std::ostream& Api::operator<<(std::ostream& out,const Api::Mixed& obj)
    {
        out<<obj.getValString();
        return out;
    }
    
    std::istream& Api::operator>>(std::istream& in,Api::Mixed& obj)
    {
        std::string val;
        in>>val;
        
        obj.setValue(val);
        
        return in;
    }
    
    
       Api::Mixed::operator int() const
       {
           return this->getValInteger();
       }
       Api::Mixed::operator float() const
       {
           return this->getValFloat();
       }
       Api::Mixed::operator std::string() const
       {
           return this->getValString();
       }
  
       
       
    const std::string Api::Mixed::serialize() const
    {   
        return (std::string)(*this);
    }
    
    void Api::Mixed::deserialize(const std::string& value)
    {
        setValue(value);
    }
    
   
    