#include "DatabaseManager.h"
#include <cstdlib>
#include <string>

using namespace Api;
using namespace std;



    Api::DatabaseManager::DatabaseManager()
    {
        
    }
    
  
    
    void Api::DatabaseManager:: printMenu() const
    {
        std::cout<<"1) Load"<<std::endl; //
	std::cout<<"2) Showtables"<<std::endl; //
	std::cout<<"3) Describe"<<std::endl; //
	std::cout<<"4) Print"<<std::endl; //
	std::cout<<"5) Save"<<std::endl; //
	std::cout<<"6) Select"<<std::endl; //
	std::cout<<"7) Add Column"<<std::endl; //
	std::cout<<"8) Update"<<std::endl; //
	std::cout<<"9) Delete"<<std::endl;//
	std::cout<<"10) Insert"<<std::endl;//
	std::cout<<"11) Inner Join"<<std::endl;//
	std::cout<<"12) Rename"<<std::endl;//
	std::cout<<"13) Count"<<std::endl;//
	std::cout<<"14) Aggregate"<<std::endl<<std::endl;
	std::cout<<"15) Create Table"<<std::endl<<std::endl;//
	std::cout<<"0) Quit"<<std::endl<<std::endl;//
    }
    void Api::DatabaseManager:: clearBuffer() const
    {
        std::system("clear");
    }
    
    void Api::DatabaseManager::pause() const
    {
    std::cout <<std::endl<< "Press enter to continue ..."; 
    std::cin.get(); 
    std::cin.get();
    std::cout <<std::endl;
  
    }
    UInput Api::DatabaseManager::requestInput() const
    {
        UInput input;
        std::cout<<"Input command: ";
     std::cin>>   input;
     
     return input;
    }
    bool Api::DatabaseManager::handleInput(UInput input)
    {
        try{
        switch(input)
	{
		case 1:
		{
                    
                    std::string filename; 
                    cout<<"Filename :";
                    cin>>filename;
                    
                    cout <<endl;
                        db.loadTable(filename);
                    
                    
                                                               
			return true;                       
		}
		case 2:
		{
                   std::vector<Table> tbls =  db.getTables();
                   
                   for(auto e = tbls.begin();e != tbls.end();e++)
                   {
                       cout<<(*e).getName()<<endl;
                   }
                   cout<<endl;
			return true;                 
		}
		case 3:
		{
                      std::string table; 
                    cout<<"Tablename :";
                    cin>>table;
                    
                    Table& tbl = db.getTable(table);
                    
                    for(ColumnID i=0;i<tbl.getSchema().size();i++)
                    {
                        switch(tbl.getSchema().getColumnType(i))
                        {
                            case CTYPE_FLOAT:
                                cout<<"FLOAT|";
                                break;
                                
                            case CTYPE_INT:
                                cout<<"INT|";
                                break;
                                
                            case CTYPE_STRING:
                                cout<<"STRING|";
                                break;
                        }
                    }
                    cout<<endl;
			
			return true;                 
		}
		case 4:
		{
                     std::string table; 
                    cout<<"Tablename :";
                    cin>>table;
                    cout<<endl;
                    const unsigned int PCOUNT = 10;
                     unsigned int page =0; 
                    
                    cout<<"Page :";
                    cin>>page;
			
                    
                    Queries::QueryLimit limit(page*PCOUNT,page*PCOUNT + PCOUNT);
                    Table tbl = db.getTable(table).query(limit);
                    
                    for(RowID index = 0; index < tbl.size();index++)
                    {
                        for(ColumnID cid = 0;cid < tbl.getSchema().size();cid++)
                        {
                            if(tbl[index][cid].isNull())cout<< "NULL |";
                            else cout<<tbl[index][cid].getValue()<<" |";
                        }
                            
                            cout<<endl;
                    }
                        
                        return true;                 
		}
		case 5:
		{
			
                    std::string table; 
                    cout<<"Tablename :";
                    cin>>table;
                    
                    std::string filename;
                    
                    cout<<endl<<"Filename: ";
                    cin>> filename;
                    
                    db.saveTable(filename,table);
                    
			return true;                 
		}
		case 6:
		{
                    std::string tablename;
                    ColumnID cid;
                    std::string value;
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    
                    cout<<endl<<"ColumnID: ";
                    cin>>cid;
                    
                    cout<<endl<<"Query value: ";
                    cin>>value;
                    
                    Queries::QueryFilter filter(cid,Cell(Mixed(value)));
                    Table bb = db.getTable(tablename).query(filter);
                    db.addTable(bb);
                    
			return true;                 
		}
		case 7:
		{
                    
                    std::string tablename;
                    ColumnType type;
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    cout<<"Column Type :";
                    cin>>type;
                    
                    db.getTable(tablename).addColumn(0,type);
			
			return true;                 
                }      
		case 8:
		{
			std::string tablename;
                        ColumnID id1;
                        ColumnID id2;
                        Cell cell1,cell2; 
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    cout<<endl<<"Filter ColumnID :";
                    cin>>id1;
                    
                    cout<<endl<<"Update ColumnID :";
                    cin>>id2;
                    
                    
                    std::string s;
                    cout<<endl<<"Filter Value:";
                    cin>>s;
                    
                    if(s != "NULL")cell1 = Cell(Mixed(s));
                    
                
                    cout<<endl<<"Update Value:";
                    cin>>s;
                    
                    if(s != "NULL")cell2 = Cell(Mixed(s));
                    
                    Queries::QueryUpdate query(id1,id2,cell1,cell2);
                    
                    db.getTable(tablename).update(query);
                    
                    
			return true;                 
		}
		case 9:
		{
                    
			std::string tablename;
                        ColumnID id1;
                        
                        Cell cell1; 
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    cout<<endl<<"Filter ColumnID :";
                    cin>>id1;
                    
                    
                    
                    std::string s;
                    cout<<endl<<"Filter Value:";
                    cin>>s;
                    
                    if(s != "NULL")cell1 = Cell(Mixed(s));
                    
                    Queries::QueryDelete query(id1,cell1);
                    
                    db.getTable(tablename).update(query);
			
			return true;                 
		}
		case 10:
		{
			std::string tablename;
                   
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    Table& tbl = db.getTable(tablename);
                    
                    
                    Row r;
                    for(ColumnID index =0 ;index<tbl.getSchema().size();index++)
                    {
                        std::string val;
                        cout<< "Insert value:";
                                cin>>val;
                                
                                if(val == "NULL")
                                {
                                    r.addCell(r.size());
                                }else
                                {
                                    r.addCell(r.size(),Cell(Mixed(val)));
                                }
                    }
                    
                    tbl.addRow(tbl.size(),r);
			return true;                 
		}
		case 11:
		{
                    std::string table1;
                    std::string table2;
                    ColumnID id1;
                    ColumnID id2;
                    
                    cout<<"Table 1: ";
                    cin>>table1;
                    
                    cout<<endl<<"Table 2: ";
                    cin>>table2;
                    
                    cout<<endl<<"Columns: ";
                    cin>>id1>>id2;
                    
                    Queries::QueryInnerJoin query(id1,id2);
                    
                    Table t = db.query(table1,table2,query);
                    
                    db.addTable(t);
                    
			return true;                 
		}
		case 12:
		{
                    
                    std::string tablename;
                    std::string ntablename;
                    
                     cout<<"Tablename: ";
                    cin>>tablename;
                    
                     cout<<"New tablename: ";
                    cin>>ntablename;
                    
                    db.renameTable(tablename,ntablename);
                    
			
			return true;                 
		}
		case 13:
		{
		std::string tablename;
                    ColumnID cid;
                    std::string value;
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    
                    cout<<endl<<"ColumnID: ";
                    cin>>cid;
                    
                    cout<<endl<<"Query value: ";
                    cin>>value;
                    
                    Queries::QueryFilter filter(cid,Cell(Mixed(value)));
                    Table bb = db.getTable(tablename).query(filter);
                    cout<<bb.size()<<endl;
                        return true;                 
		}
		case 14:
		{
                    cout<< "Not implemented !"<<endl;
			return true;                 
		}
		case 15:
		{
                    std::string tablename;
                    
                    cout<<"Tablename: ";
                    cin>>tablename;
                    
                    Table tbl(tablename);
                    db.addTable(tbl);
                        
			return true;                 
		}
		case 0: {return false;}
                
                default: return true;
	}
        
        }catch(...){
            return true;
        }
        
        return false;
        }
    
    void Api::DatabaseManager::run()
    {
        
        printMenu();  
        while(handleInput(requestInput()))
        {
            pause();
            clearBuffer();
            printMenu();
        }
    }
    