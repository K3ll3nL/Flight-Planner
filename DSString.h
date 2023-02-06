#ifndef S20_PA01_SENTIMENTANALYSIS_DSString_H
#define S20_PA01_SENTIMENTANALYSIS_DSString_H

#include <string>
#include <cstring>
#include <iostream>


class DSString {
public:

    //Constructor
    DSString();

    //Overloaded constructor
    DSString(const char* word);



    //Rule of 3


    DSString& operator=(const DSString &);
    DSString& operator=(const char*);
    ~DSString();
    DSString(const DSString& copy);


    //Other functions
    int getSize() const;
    char* getString() const;
    void setString(char *a);
    void print() const;
    void Lower();
    void Capitalize();
    char operator[](int i) const{
        if (0 < i || i >= size) {
            return data[i];
        }
    }
    bool operator==(const DSString& x) const{
        //return size == x.size && getString() == x.getString();
        return strcmp(data, x.data) == 0;
    }

    bool operator!=(const DSString& x) const{
        return strcmp(data,x.data) != 0;
    }
    bool operator>(const DSString& x) const{
        return data > x.data;
    }
    bool operator<(const DSString& x) const {
        return data < x.data;
    }
    bool operator>=(const DSString& x) const{
        return data >= x.data;
    }
    bool operator<=(const DSString& x) const{
        return data <= x.data;
    }
    DSString operator+=(const char* word){
        data = strcat(this->getString(),word);
        return *this;
    }
    std::ostream& operator<<(std::ostream& out)
    {
        for(int i=0; i <size; i++)
        {
            std::cout<<data[i];
        }
        return out;
    }







private:
    int size{};
    char *data;
};

namespace std
{
    template<> struct hash<DSString>
    {
        std::size_t operator()(DSString const& s) const noexcept
        {
            return hash<string>()(s.getString());
//            auto ret = 0;
//            int temp = s.getSize();
//            for(int i = 0; i< temp; i++){
//                ret = 100*ret + (int)s[i];
//            }
//            return ret;
        }
    };
}




#endif
