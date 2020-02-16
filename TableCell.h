#ifndef TABLECELL_H
#define TABLECELL_H

#include "Mixed.h"



namespace Api{

    
    class Cell :public Serializable{
    protected:
        
        Mixed val;
        bool fnull;
       
    public:
        
        Cell();
        Cell(const Mixed&);
        Cell(const Cell&);
        
        virtual ~Cell(){}
        
        Cell& operator= (const Cell&);
        
        void setValue(const Mixed&);
        void removeValue();
        
        const Mixed& getValue() const;
        bool isNull() const;
        
        const std::string serialize() const;
        void deserialize(const std::string&);

        
    };
    
    bool operator==(const Cell&,const Cell&);
    
};


#endif /* TABLECELL_H */

