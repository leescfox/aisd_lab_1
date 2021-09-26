#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <typeinfo>
#include <vector>
#include <malloc.h>
#include <fstream>
#define MAXLEN 128

struct Odnosv {
    std::string elem;
    struct Odnosv *next;
};

struct Golova {
    struct Odnosv *top;
};

typedef struct Odnosv List;
typedef struct Golova Head;

void push(Head* HEAD, std::string str);
std::string pop(Head* HEAD, List* verh);
Head* create_head();
void massivepush(std::vector<std::string> &mas, std::string str);
std::string massivepop(std::vector<std::string> &mas);

int main()
{
    Head *HEAD=NULL;
    std::string simbols[]={"+", "-", "*", "/", "^"};
    std::string functions[]={"sin", "cos", "ln", "tg", "ctg"};
    unsigned int i=0, n;
    int m,k,j,check_1,check_2,check_3,check_4;
    std::string temporary;
    std::string equation;

    std::vector<std::string> dmassive(0, "");

    std::cout << "Separate operands, operators, brackets, numbers and functions of your equation with spaces." << std::endl;
    std::cout << "Enter your equation: ";
    std::getline(std::cin, equation);
    std::cout << "Converted equation: ";
    while (i<equation.length()+1)
    {
        temporary="";
        check_1=0;
        check_2=0;
        while (equation[i]!=' ' && i<equation.length())
        {
            temporary=temporary+equation[i];
            i++;
        }
        for (n=0;n<(sizeof(functions)/sizeof(functions[0]))&&check_1==0;n++)
                    if (temporary==functions[n])
                        check_1=1;
                if (check_1==1)
                {
                    massivepush(dmassive,temporary);
                }
        else
        {
            for (j=0;(j<5 && check_2!=1);j++)
                if (temporary==simbols[j])
                {
                    check_2=1;
                }
            if (check_2==1)
            {
                if (dmassive.size()==0 || dmassive[dmassive.size()-1]=="(")
                {
                    massivepush(dmassive,temporary);
                }
                else
                {
                    check_3=0;
                    for (k=0;k<5&&check_3!=1;k++)
                    if (dmassive[dmassive.size()-1]==simbols[k])
                    {
                        check_3=1;
                    }
                    if (check_3==1&&j>2&&k<3)
                        massivepush(dmassive,temporary);
                    else if (check_3==1)
                    {
                        do
                        {
                            std::cout << massivepop(dmassive) << " ";
                            check_4=0;
                            if (dmassive.size()>0)
                                if (dmassive[dmassive.size()-1]!="(")
                                    for (m=0;m<5&&check_4!=1;m++)
                                        if (dmassive[dmassive.size()-1]==simbols[m])
                                            check_4=1;
                        } while((check_4==1)&& !(j>2&&m<3));
                        massivepush(dmassive,temporary);
                    }
                }
            }
            else if (temporary=="(")
                massivepush(dmassive,temporary);
            else if (temporary==")")
            {
                while (dmassive[dmassive.size()-1]!="(")
                std::cout << massivepop(dmassive) << " ";
                massivepop(dmassive);
                for (n=0;n<(sizeof(functions)/sizeof(functions[0]))&&(check_1==0)&&(dmassive.size()>0);n++)
                    if (dmassive[dmassive.size()-1]==functions[n])
                    {
                        check_1=1;
                        std::cout << massivepop(dmassive) << " ";
                    }
            }
            else std::cout << temporary << " ";
        }
        i++;
    }
    while (dmassive.size()>0)
        std::cout << massivepop(dmassive) << " ";
    std::cout << "\n";
    return 0;
}

Head* create_head()
{
    Head *HEAD=new Head;
    HEAD->top=NULL;
    return HEAD;
}

std::string pop(Head* HEAD, List* verh)
{
    std::string vivod;
    vivod=verh->elem;
    HEAD->top=verh->next;
    free(verh);
    return vivod;
}

void push(Head* HEAD, std::string str)
{
    List *verh=new List;
    verh->elem=str;
    verh->next=HEAD->top;
    HEAD->top=verh;
}

void massivepush(std::vector<std::string> &mas, std::string str)
{
    mas.resize(mas.size()+1);
    mas[mas.size()-1]=str;
}

std::string massivepop(std::vector<std::string> &mas)
{
    std::string retur;
    retur=mas[mas.size()-1];
    mas.resize(mas.size()-1);
    mas[mas.size()].clear();
    return retur;
}

