//
//  CustomClass.h
//  custom_class
//
//  Created by 文野 卢 on 3/5/19.
//

#pragma once
class CustomClass{
public:
    CustomClass();
    ~CustomClass();
    int add(int first, int second);
};

//constructor definition
inline CustomClass::CustomClass(){}
inline CustomClass::~CustomClass(){}
inline int  CustomClass::add(int first, int second){
    int sum = first + second;
    return sum;
}
