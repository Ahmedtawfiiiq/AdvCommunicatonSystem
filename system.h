#pragma once
#include <vector>
#include <bitset>
#include <complex>
#include <string>
using namespace std;
typedef unsigned char uint8;

// singleton class
class System
{
public:
    vector<string> data;
    bitset<21> data21;
    bitset<64> data64;
    vector<vector<bitset<1>>> data8x8;
    vector<vector<bitset<1>>> data_8x8_transpose;
    vector<complex<float>> sample;    // 32 samples -> after modulator
    vector<complex<float>> sample_cp; // 40 samples -> after cyclic prefix [cp length = 8 samples]
    vector<float> random_noise;       // contain 40 random values follow normal distribution [mean=0, variance=1]

private:
    System() = default;

public:
    void encoder();
    void decoder();
    void mapper();
    void demapper();
    void scrambler();
    void descrambler();
    void modulator();
    void demodulator();
    void cyclicPrefixAdder();
    void cyclicPrefixRemover();
    void noiseGenerator();
    void awgnChannel(uint8);

    static System &getInstance()
    {
        static System instance;
        return instance;
    }
    // delete copy constructor -> className newInstanceName(oldInstanceName);
    System(const System &) = delete;
    // delete copy assignment operator -> className newInstanceName = oldInstanceName;
    System &operator=(const System &) = delete;
    // delete move constructor
    System(System &&) = delete;
    // delete move assignment operator
    System &operator=(System &&) = delete;
};
