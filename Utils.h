#ifndef UTILS_H
#define UTILS_H

#include <regex>
#include <string>

using namespace std;

namespace Api{
    
    namespace Utils{
        
        /*Regex is copied from stackoverflow as it's sensitive and I'd rather have it right than writing it myself */
        
        static const std::regex _rgx_int ("^-?\\d+"); 
        static const std::regex _rgx_float("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
     
        static bool isNumber(const std::string& value)
        {
            
            
            return std::regex_match(value,_rgx_int);
            
        }
        
        static bool isFloat(const std::string& value)
        {
          return std::regex_match(value,_rgx_float);
        }
        
    }
}


#endif /* UTILS_H */

