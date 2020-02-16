#ifndef TABLEQUERY_H
#define TABLEQUERY_H

#include <vector>

#include "TableRow.h"
#include "TableSchema.h"
namespace Api{
    
    
    class UnaryQuery{
        
        
    public:
      
        virtual Schema buildSchema(const Schema& );
        virtual std::vector<Row> execute(const Row&) = 0; 
        virtual void reset() = 0;
        
    };
    
    class BinaryQuery{
        
    public:
        
        
        virtual Schema buildSchema(const Schema&,const Schema&);
        virtual std::vector<Row> execute(const Row&,const Row&)=0;
        virtual void reset()=0;
        
    };
    
    namespace Queries{
        
        class QueryInnerJoin : public BinaryQuery{
            
        protected:
            
            ColumnID id1,id2;
            
        public:
            
            QueryInnerJoin(ColumnID,ColumnID);
            std::vector<Row> execute(const Row&,const Row&);
            void reset();
        };
        
        class QueryUpdate: public UnaryQuery{
            
        protected:
            ColumnID id;
            Cell value;
            
            ColumnID id2;
            Cell value2;
        public:
            
            QueryUpdate(ColumnID,ColumnID, const Cell& ,const Cell&);
            
            std::vector<Row> execute(const Row&);           
            void reset();
        };
        
           class QueryDelete: public UnaryQuery{
            
        protected:
            ColumnID id;
            Cell value;
            
        public:
            
            QueryDelete(ColumnID,const Cell&);
            
            std::vector<Row> execute(const Row&);           
            void reset();
        };
        
        
        class QueryFilter: public UnaryQuery{
            
        protected:
            ColumnID id;
            Cell value;
        public:
            
            QueryFilter(ColumnID, const Cell& s);
            
            std::vector<Row> execute(const Row&);           
            void reset();
        };
        
        class QueryLimit :public UnaryQuery
        {
        protected:
            
            RowID crow;
            
            RowID minrow;
            RowID maxrow;
            
        public:
            
            QueryLimit(RowID,RowID);
            
            std::vector<Row> execute(const Row&);
            void reset();
        };
        
    }
    
    
}


#endif /* TABLEQUERY_H */

