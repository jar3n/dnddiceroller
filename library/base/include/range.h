#ifndef _RANGE_H_
#define _RANGE_H_

#include <cstdint>

class RangeConverter {
    private:
        class Range{
            private:
                int32_t _min;
                int32_t _max;
            
            public:
                Range(int32_t min, int32_t max);
                ~Range();

                int32_t computeMaxDiff();
                int32_t getMin();
        };
        Range r_old;
        Range r_new;

    
    public:
        RangeConverter(int32_t min1, int32_t max1, int32_t min2, int32_t max2);
        ~RangeConverter();

        int32_t convertVal(int32_t val);

};

#endif
