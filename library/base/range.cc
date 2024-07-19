#include "range.h"

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