

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>

namespace Api
{
    namespace Exception{
     
        
    class exception_query_schema : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Invalid query schema !";
        }
    };
     
    class exception_mixed_cast : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Mixed cannot be cast !";
        }
    };
    
    class exception_cell_value : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Cell value is null !";
        }
    };
    
    class exception_schema_index : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Schema index out of bounds !";
        }
    };
    
    
    class exception_column_type : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Schema column type not supported !";
        }
    };
    
     class exception_cell_index : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Cell index out of bounds !";
        }
    };
    
    class exception_row_validation : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Invalid row schema !";
        }
    };
    
    
    class exception_row_index : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Row index out of bounds !";
        }
    };
   
    
    class exception_invalid_table : public std::exception 
    {
    
    public:
        const char* what()const throw()
        {
            return "Table is not valid !";
        }
    };
    
    }
}


#endif /* EXCEPTIONS_H */

