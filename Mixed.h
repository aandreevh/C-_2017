#ifndef MIXED_H
#define MIXED_H

#include<string>
#include<assert.h>
#include<iostream>


#include "Serializable.h"

namespace Api
{


class Mixed :public Serializable{

protected:

    std::string value;

public:



    Mixed();
    Mixed(const Mixed&);

    virtual ~Mixed(){}

    Mixed(const std::string&);
    Mixed(int);
    Mixed(float);

    Mixed& operator=(const Mixed&);

    void setValue(int);

    void setValue(float);

    void setValue(const std::string&);

    int getValInteger() const;

    float getValFloat() const;

    const std::string& getValString() const;

    explicit operator int() const;
    explicit operator float() const;
    explicit operator std::string() const;


    const std::string serialize() const;
    void deserialize(const std::string&);

};

    bool operator==(const Mixed&, const Mixed&);
    std::ostream& operator<<(std::ostream& ,const Api::Mixed&);
    std::istream& operator>>(std::istream&,Api::Mixed&);

}


#endif /* MIXED_H */
