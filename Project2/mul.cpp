#include <iostream>
#include <string>
#include "f.h"

using namespace std;

string mul_positive_integers(string a,string b)  //compute the product of two positive integers (may be large numbers)
{
    int data_a[a.size()];  //store the first large number
    int data_b[b.size()];  //store the second large number
    int data_c[a.size()+b.size()];  //store the result

    for(int i = 0; i < a.size(); i++)
    {
        data_a[a.size()-i-1] = a[i]-'0';
    }

    for(int i = 0; i < b.size(); i++)
    {
        data_b[b.size()-i-1] = b[i]-'0';
    }

    for(int i=0;i<a.size()+b.size();i++)
    {
        data_c[i]=0;
    }

    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<b.size();j++)
        {
            data_c[i+j]=data_c[i+j]+data_a[i]*data_b[j];
        }
    }

    for(int i=0;i<a.size()+b.size();i++)
    {
        if(data_c[i]>9)
        {
            data_c[i+1]=data_c[i+1]+data_c[i]/10;
            data_c[i]=data_c[i]%10;
        }
    }

    string result="";
    int flag=0;
    for(int i=a.size()+b.size()-1;i>=0;i--)
    {
        if(data_c[i]!=0)
        {
            flag=i;
            break;
        }
    }
    for(int i=flag;i>=0;i--)
    {
        result=result+to_string(data_c[i]);
    }

    return result;
}

string mul_positive(string a,string b)  //compute the product of two positive numbers which have normal/decimal/SCM formal
{
    string aa="";
    string bb="";
    string e_of_a="";
    string e_of_b="";

    if(isNum(a)==true)
    {
        aa=a;
        e_of_a="0";
    }

    if(isDecimal(a)==true)
    {
        int loc_of_dot=0;
        for(int i=0;i<a.size();i++)
        {
            int t = (int)a[i];
            if(t==46)
            {
                loc_of_dot=i;
            }
            else
            {
                aa=aa+a[i];
            }
        }
        e_of_a="-"+std::to_string(a.size()-loc_of_dot-1);
    }

    if(isScientific_counting_method(a)==true)
    {
        string a1="";  //before E/e
        string a2="";  //after E/e
        int loc_of_e=0;
        for(int i=0;i<a.size();i++)
        {
            int t = (int)a[i];
            if(t!=69 and t!=101)
            {
                a1=a1+a[i];
            }
            else
            {
                loc_of_e=i;
                break;
            }
        }

        for(int i=loc_of_e+1;i<a.size();i++)
        {
            a2=a2+a[i];
        }

        if(isNum(a1)==true)
        {
            aa=a1;
            e_of_a=a2;
        }

        if(isDecimal(a1)==true)
        {
            int loc_of_dot__=0;
            string aa__="";
            for(int i=0;i<a1.size();i++)
            {
                int t = (int)a1[i];
                if(t==46)
                {
                    loc_of_dot__=i;
                }
                else
                {
                    aa__=aa__+a1[i];
                }
            }
            string e_of_a1="-"+std::to_string(a1.size()-loc_of_dot__-1);
            aa=aa__;
            e_of_a=std::to_string(std::stoi(e_of_a1)+std::stoi(a2));
        }
    }

    if(isNum(b)==true)
    {
        bb=b;
        e_of_b="0";
    }

    if(isDecimal(b)==true)
    {
        int loc_of_dot=0;
        for(int i=0;i<b.size();i++)
        {
            int t = (int)b[i];
            if(t==46)
            {
                loc_of_dot=i;
            }
            else
            {
                bb=bb+b[i];
            }
        }
        e_of_b="-"+std::to_string(b.size()-loc_of_dot-1);
    }

    if(isScientific_counting_method(b)==true)
    {
        string b1="";  //before E/e
        string b2="";  //after E/e
        int loc_of_e=0;
        for(int i=0;i<b.size();i++)
        {
            int t = (int)b[i];
            if(t!=69 and t!=101)
            {
                b1=b1+b[i];
            }
            else
            {
                loc_of_e=i;
                break;
            }
        }

        for(int i=loc_of_e+1;i<b.size();i++)
        {
            b2=b2+b[i];
        }

        if(isNum(b1)==true)
        {
            bb=b1;
            e_of_b=b2;
        }

        if(isDecimal(b1)==true)
        {
            int loc_of_dot__=0;
            string bb__="";
            for(int i=0;i<b1.size();i++)
            {
                int t = (int)b1[i];
                if(t==46)
                {
                    loc_of_dot__=i;
                }
                else
                {
                    bb__=bb__+b1[i];
                }
            }
            string e_of_b1="-"+std::to_string(b1.size()-loc_of_dot__-1);
            bb=bb__;
            e_of_b=std::to_string(std::stoi(b2)+std::stoi(e_of_b1));
        }
    }

    if ((isNum(a)==1 or isDecimal(a)==1 or isScientific_counting_method(a)==1)&&(isNum(b)==1 or isDecimal(b)==1 or isScientific_counting_method(b)==1))
    {
        string ans1=mul_positive_integers(aa,bb);
        string ans2=std::to_string(std::stoi(e_of_a)+std::stoi(e_of_b));
            
        return ans1+"E"+ans2;
    }
    else 
    {
        return "Sorry! This is illegal input!";
    }
}

string mul(string a,string b)  //compute the product of two numbers which have normal/decimal/SCM formal and use the standard form
{
    int sign_a=1;
    int sign_b=1;

    string aa=a.c_str();
    string bb=b.c_str();

    if((int)a[0]==43)  //"+"
    {
        a.erase(0, 1);
    }
    if((int)a[0]==45)  //"-"
    {
        a.erase(0, 1);
        sign_a=-1;
    }
    if((int)b[0]==43)  //"+"
    {
        b.erase(0, 1);
    }
    if((int)b[0]==45)  //"-"
    {
        b.erase(0, 1);
        sign_b=-1;
    }

    int sign=sign_a*sign_b;
    string word=mul_positive(a,b);

    if((int)word[0]==83)  //S
    {
        return word;
    }
    else
    {
        if(sign==1)
        {
            return normalization(word).c_str();
        }
        else
        {
            std::string str=normalization(word);
            std::string re="-"+str;
            return re;
        }
    }
}