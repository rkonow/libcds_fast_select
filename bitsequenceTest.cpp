#include <BitSequenceRGK.h>
#include <Timer.h>
#include <algorithm>
#include <map>
#include <random>

using std::map;
using namespace cds_static;
using namespace std;


int main() {
    for (size_t n = 10000000; n < 35000000; n += 1000000) {
        BitString bs(n);
        size_t ones = n / 2;
        cout << "ones = " << ones << endl;
        std::default_random_engine generator;
        // std::geometric_distribution<> distribution(0.000001);
        std::uniform_int_distribution<> distribution(10);
        std::map<int, int> freqs;
        int ranges = n/10;
        for (size_t i = 1; i < ones; i++) {
            // cout << rand()%(n-2) << endl;
            double number = distribution(generator);
            size_t pos = int(number) % n;
            freqs[pos / ranges]++;
            // cout << pos << endl;
            bs.setBit(pos);
        }
        for (auto x : freqs) {
            cout << fixed << "[ " << x.first * ranges << " ]  -> " << x.second << endl;
        }
        cout << "Ss \t\t n \t new micro \t orig micro \t x fast \t space(\%) " << endl;
        cout << "---------------------------------------------" << endl;
        for (size_t block = 32; block < 1024 * 2; block = block + 8) {
            BitSequenceRGK *brk = 	(BitSequenceRGK::builder).
            					  	s1factor(block).
            						s0factor(block).
            						bitstring(bs).
            						rfactor(20).
            build();
            // BitSequenceRGK *brk = new BitSequenceRGK(bs, 20);
            BitSequenceRG *br = new BitSequenceRG(bs, 20);

            vector <size_t> queries(brk->countZeros());
            for (size_t i = 0; i < brk->countZeros(); i++) {
                size_t test = rand() % brk->countZeros();
                if (test == 0)
                    test = 1;
                queries[i] = test;
            }

            Timer *timer = new Timer();
            timer->Restart();
            for (size_t i = 0; i < queries.size(); i++) {
                size_t r = brk->select0_t(queries[i]);
            }
            timer->Stop();
            double t_version = timer->ElapsedTimeCPU();

            timer->Restart();
            for (size_t i = 0; i < queries.size(); i++) {
                size_t r = br->select0(queries[i]);
            }
            timer->Stop();
            double r_version = timer->ElapsedTimeCPU();
            cout << block << "\t" << n << std::fixed << "\t" <<
                    t_version * 1.0 / queries.size() * 1.0 << "\t"
                    << r_version * 1.0 / queries.size() * 1.0 << "\t"
                    << 1.0 / ((t_version * 1.0 / queries.size() * 1.0) / (r_version * 1.0 / queries.size() * 1.0)) << "\t"
                    << (brk->countZeros() / block) * 4.0 / (brk->getSize() * 1.0) * 100
                    << endl;
            // cout << "checking errors 0 = " << brk->countZeros() << endl;
            for (size_t i = 1; i < brk->countZeros(); i++) {
                // cout << "waza" << endl;
                size_t a = brk->select0_t(i);
                size_t b = br->select0(i);
                if (a != b) {
                    cout << "error at " << i << "(" << a << " != " << b << " ) " << endl;
                    exit(1);
                }
            }
            // cout << "checking errors 1 = " << brk->countOnes() << endl;
            for (size_t i = 1; i < brk->countOnes(); i++) {
                // cout << "waza" << endl;
                size_t a = brk->select1_t(i);
                size_t b = br->select1(i);
                if (a != b) {
                    cout << "error at " << i << "(" << a << " != " << b << " ) " << endl;
                    exit(1);
                }
            }

            // cout << "checking errors next 1 = " << brk->countOnes() << endl;
            for (size_t i = 1; i < brk->countOnes(); i++) {
                // cout << "waza" << endl;
                size_t a = brk->selectNext1(i);
                size_t b = br->selectNext1(i);
                if (a != b) {
                    cout << "error at " << i << "(" << a << " != " << b << " ) " << endl;
                    exit(1);
                }
            }

            // cout << "checking errors prev 1 = " << brk->countOnes() << endl;
            for (size_t i = brk->countOnes() / 2; i < brk->countOnes(); i++) {
                // cout << "waza" << endl;
                size_t a = brk->selectPrev1(i);
                size_t b = br->selectPrev1(i);
                if (a != b) {
                    cout << "error at " << i << "(" << a << " != " << b << " ) " << endl;
                    exit(1);
                }
            }
            ofstream f("test.out");
            brk->save(f);
            f.close();

            ifstream g("test.out");
            // cout << brk->getSize() << endl;
            BitSequenceRGK *brk2 = BitSequenceRGK::load(g);
            for (size_t i = 1; i < brk2->countZeros(); i++) {
                size_t a = brk->select0_t(i);
                size_t b = brk2->select0_s(i);
                if (a != b) {
                    cout << "error at " << i << "(" << a << " != " << b << " ) " << endl;
                    exit(1);
                }
            }
            delete brk2;
            delete brk;
        }
    }
}