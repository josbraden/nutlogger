#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "nutlogger.h"
using namespace std;

//Function to sort and unique the UPS device list
void configobj::upslist_sortUnique() {
    sort(upslist.begin(), upslist.end());
    vector<string>::iterator it;
    it = unique(upslist.begin(), upslist.end());
    upslist.resize(distance(upslist.begin(),it));
}
