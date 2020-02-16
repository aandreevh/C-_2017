#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

namespace Api{
    
    
class Serializable{
    
public:
    
    virtual const std::string serialize() const =0;
    virtual void deserialize(const std::string&) =0;
};
    
}


#endif /* SERIALIZABLE_H */

