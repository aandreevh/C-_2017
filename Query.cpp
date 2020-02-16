#include "Query.h"

using namespace Api;


   Queries::QueryDelete::QueryDelete(ColumnID id,const Cell& value)
   {
       this->id = id;
       this->value = value;
   }
            
   std::vector<Row> Queries::QueryDelete::execute(const Row& r)
   {
       std::vector<Row> out;
       
       if(!(r.getCell(id) == value ))out.insert(out.begin(),r);
       return out;
   }
            
   void Queries::QueryDelete::reset(){}
        

 Queries::QueryUpdate::QueryUpdate(ColumnID id1,ColumnID id2, const Cell& a ,const Cell& b)
 {
     this->id = id1;
     this->id2 = id2;
     this->value = a;
     this->value2 = b;
 }
            
 std::vector<Row> Queries::QueryUpdate::execute(const Row& row)
 {
     std::vector<Row> out;
     if(row.getCell(id) == value )
     {
         Row nrow = row;
         nrow[id2] = value2;;
         out.insert(out.begin(),nrow);
     }
     
     return out;
 }
            
void Queries::QueryUpdate::reset(){}

Schema Api::BinaryQuery::buildSchema(const Schema& schema1,const Schema& schema2)
{
    Schema a = schema1;
    a+= schema2;
    
    return a;
}

Schema Api::UnaryQuery::buildSchema(const Schema& other)
{
    return other;
}

Api::Queries::QueryInnerJoin::QueryInnerJoin(ColumnID id1, ColumnID id2) {
 this->id1 = id1;
 this->id2 = id2;
}

std::vector<Row> Api::Queries::QueryInnerJoin::execute(const Row& a,const Row& b)
{
    std::vector<Row> out;
    Row c = a;
    c+= b;
    
    if(a.getCell(id1) == b.getCell(id2))out.push_back(c);
    
    return out;
}
void Api::Queries::QueryInnerJoin::reset(){}

Api::Queries::QueryFilter::QueryFilter(ColumnID id, const Cell& val)
{
  this->id = id;
  this->value = val;
}

std::vector<Row> Api::Queries::QueryFilter::execute(const Row& row) 
{
    std::vector<Row> out;
    if(row.getCell(id) == value)out.push_back(row);
    
    return out;
}

void Api::Queries::QueryFilter::reset(){}


 Api::Queries::QueryLimit::QueryLimit(RowID minrow, RowID maxrow)
{
    this->crow = 0;
    this->minrow = minrow;
    this->maxrow = maxrow;
}

std::vector<Row> Api::Queries::QueryLimit::execute(const Row& row) 
{
    
    std::vector<Row> out;
    
    if(crow >= minrow && crow <=maxrow) out.push_back(row);
    
    crow++;
    return out;
}

void Api::Queries::QueryLimit::reset()
{
    this->crow = 0;
}

