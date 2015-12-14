#include <BitSequenceRGK.h>
#include <Timer.h>
#include <algorithm>
#include <map>
#include <random>
#include <WaveletTreeNoptrs.h>


using std::map;
using namespace cds_static;
using namespace std;


int main() {
    uint len = 10;
    uint sigma = 10;
    Array a(len, sigma );
    vector<uint> values = {1,2,3,4,5,1,6,3,4,5};
    for (uint i = 0; i < len; i++) {
        a.setField(i,values[i]);
    }
    Mapper *mapper = new MapperNone();
    mapper->use();
    WaveletTreeNoptrs wt(a, new BitSequenceBuilderRRR(32), mapper);
    uint res = 0;
    uint x1 = 5;
    uint x2 = 7;
    uint y1 = 1;
    uint y2 = 3;
    wt.range_sum(x1,x2,y1,y2,res);
    cout << "res = " << res << endl;
    res = 0;
    wt.range_sum(6,7,6,6,res);
    cout << "res = " << res << endl;
}