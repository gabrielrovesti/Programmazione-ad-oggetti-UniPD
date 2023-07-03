#include <algorithm>

// all è il vector<const Allenamento*>

int conta(double lmt) const {
    int cnt = 0;
    for_each(all.begin(), all.end(), [&cnt, &lmt] (const Allenamento* a) { 
        if(a->getDurata() > lmt) cnt++;
    });
    return cnt;
}