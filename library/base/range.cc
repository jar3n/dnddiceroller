#include "range.h"
#include <cmath>

RangeConverter::Range::Range(int32_t min, int32_t max): _min(min), _max(max){}

RangeConverter::Range::~Range(){}

int32_t RangeConverter::Range::computeMaxDiff(){
    return _max - _min;
}

int32_t RangeConverter::Range::getMin(){
    return _min;
}

RangeConverter::RangeConverter(int32_t min_old, int32_t max_old, int32_t min_new, int32_t max_new): 
                                r_old(min_old, max_old), 
                                r_new(min_new, max_new){}

RangeConverter::~RangeConverter(){}

int32_t RangeConverter::convertVal(int32_t val){
    return (((val - r_old.getMin()) * r_new.computeMaxDiff())/r_old.computeMaxDiff()) + r_new.getMin();
}

AltRangeConverter::AltRangeConverter(int32_t central, int32_t divisor) :
_central(central),
_divisor(divisor){}


AltRangeConverter::~AltRangeConverter()
{
}

int32_t AltRangeConverter::convertVal(int32_t val)
{
    double initVal = ((double)(val) - (double)(_central))/(double)(_divisor);
    if (initVal < 0){
        return (int32_t)(floor(initVal));
    } else {
        return (int32_t)(ceil(initVal));
    }
}
