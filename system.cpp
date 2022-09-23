#include "system.h"
#include "fileHandler.h"
#include <random>
#include <chrono>
#include <iostream>
typedef unsigned char uint8;

void System::encoder()
{
    System::data.clear();
    uint8 k = 0;
    for (uint8 i = 0; i < 21; i++)
    {
        if (System::data21[i] == 1)
        {
            for (uint8 j = 0; j < 3; j++)
            {
                System::data64.set(k + j, 1);
            }
        }
        else
        {
            for (uint8 j = 0; j < 3; j++)
            {
                System::data64.set(k + j, 0);
            }
        }
        k += 3;
    }
    System::data64 <<= 1; // garbage bit at least significant bit
    System::data.push_back(System::data64.to_string());
}

void System::decoder()
{
    System::data.clear();
    uint8 k = 0;
    // starting from 1 to neglect garbage bit
    for (uint8 i = 1; i < 64; i++)
    {
        if (System::data64[i] == 1)
        {
            System::data21.set(k, 1);
        }
        else
        {
            System::data21.set(k, 0);
        }
        i += 2;
        k++;
    }
    System::data.push_back(System::data21.to_string());

    string s1 = FileHandler::getInstance().data[0];
    string s2 = System::data[0];

    uint16 counter = 0;

    for (uint16 i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
        {
            counter++;
        }
    }

    System::data.push_back("Changed bits: " + to_string(counter));
}

void System::mapper()
{
    System::data.clear();
    uint8 k = 0;
    string line;
    for (uint8 i = 0; i < 8; i++)
    {
        line = "";
        vector<bitset<1>> bits_row;
        for (uint8 j = 0; j < 8; j++)
        {
            bits_row.insert(bits_row.begin(), bitset<1>(System::data64[k]));
            line = bitset<1>(System::data64[k]).to_string() + line;
            k++;
        }
        System::data.insert(System::data.begin(), line);
        System::data8x8.insert(System::data8x8.begin(), bits_row);
    }
}

void System::demapper()
{
    System::data.clear();
    uint8 k = 63;
    for (uint8 i = 0; i < 8; i++)
    {
        for (uint8 j = 0; j < 8; j++)
        {
            if (System::data8x8[i][j] == 1)
            {
                System::data64[k] = 1;
            }
            else
            {
                System::data64[k] = 0;
            }
            k--;
        }
    }
    System::data.push_back(System::data64.to_string());
}

void System::scrambler()
{
    System::data.clear();
    string line;
    for (uint8 i = 0; i < 8; i++)
    {
        line = "";
        vector<bitset<1>> bits_row;
        for (uint8 j = 0; j < 8; j++)
        {
            bits_row.push_back(System::data8x8[j][i]);
            line += System::data8x8[j][i].to_string();
        }
        System::data.push_back(line);
        System::data_8x8_transpose.push_back(bits_row);
    }
}

void System::descrambler()
{
    System::data.clear();
    System::data8x8.clear();
    string line;
    for (uint8 i = 0; i < 8; i++)
    {
        line = "";
        vector<bitset<1>> bits_row;
        for (uint8 j = 0; j < 8; j++)
        {
            bits_row.push_back(System::data_8x8_transpose[j][i]);
            line += System::data_8x8_transpose[j][i].to_string();
        }
        System::data.push_back(line);
        System::data8x8.push_back(bits_row);
    }
}

/*
 * modulator gray code
 * 00 ->  0.707+0.707i
 * 01 ->  0.707-0.707i
 * 10 -> -0.707-0.707i
 * 11 -> -0.707+0.707i
 */

void System::modulator()
{
    for (uint8 i = 0; i < 8; i++)
    {
        uint8 k = 0;
        for (uint8 j = 0; j < 4; j++)
        {
            complex<float> comp;
            if (System::data_8x8_transpose[i][k] == 0)
            {
                // 00 ->  0.707+0.707i
                if (System::data_8x8_transpose[i][k + 1] == 0)
                {
                    comp.real(0.707);
                    comp.imag(0.707);
                    sample.push_back(comp);
                }
                // 01 ->  0.707-0.707i
                else
                {
                    comp.real(0.707);
                    comp.imag(-0.707);
                    sample.push_back(comp);
                }
            }
            else
            {
                // 10 -> -0.707-0.707i
                if (System::data_8x8_transpose[i][k + 1] == 0)
                {
                    comp.real(-0.707);
                    comp.imag(-0.707);
                    sample.push_back(comp);
                }
                // 11 -> -0.707+0.707i
                else
                {
                    comp.real(-0.707);
                    comp.imag(0.707);
                    sample.push_back(comp);
                }
            }
            k += 2;
        }
    }
}

void System::demodulator()
{
    System::data_8x8_transpose.clear();
    System::data.clear();

    // complex<float> comp00( 0.707, 0.707);
    // complex<float> comp01( 0.707,-0.707);
    // complex<float> comp10(-0.707,-0.707);
    // complex<float> comp11(-0.707, 0.707);

    uint8 k = 0;
    string line;
    for (uint8 i = 0; i < 8; i++)
    {
        line = "";
        vector<bitset<1>> bits_row;

        for (uint8 j = 0; j < 4; j++)
        {

            bool comp00 = real(System::sample_cp[k]) >= 0 && imag(System::sample_cp[k]) >= 0;
            bool comp01 = real(System::sample_cp[k]) >= 0 && imag(System::sample_cp[k]) < 0;
            bool comp10 = real(System::sample_cp[k]) < 0 && imag(System::sample_cp[k]) < 0;
            bool comp11 = real(System::sample_cp[k]) < 0 && imag(System::sample_cp[k]) >= 0;

            // cout << comp00 << endl;
            // cout << comp01 << endl;
            // cout << comp10 << endl;
            // cout << comp11 << endl;

            // 0.707+0.707i -> 00
            if (comp00)
            {
                bits_row.push_back(0);
                bits_row.push_back(0);
                line += "00";
            }
            // 0.707-0.707i -> 01
            if (comp01)
            {
                bits_row.push_back(0);
                bits_row.push_back(1);
                line += "01";
            }
            // -0.707-0.707i -> 10
            if (comp10)
            {
                bits_row.push_back(1);
                bits_row.push_back(0);
                line += "10";
            }
            // -0.707+0.707i -> 11
            if (comp11)
            {
                bits_row.push_back(1);
                bits_row.push_back(1);
                line += "11";
            }
            k++;
        }
        System::data.push_back(line);
        System::data_8x8_transpose.push_back(bits_row);
    }
}

// # cp samples = 8 samples
void System::cyclicPrefixAdder()
{
    System::sample_cp = System::sample;
    for (uint8 i = 31; i >= 24; i--)
    {
        System::sample_cp.insert(System::sample_cp.begin(), System::sample[i]);
    }
}

void System::cyclicPrefixRemover()
{
    vector<complex<float>>::iterator it;
    it = System::sample_cp.begin();

    for (uint8 i = 0; i < 8; i++)
    {
        System::sample_cp.erase(it);
    }
    System::sample.clear();
    System::sample = System::sample_cp;
}

/*
 * snr -> signal to noise ratio power
 * snr[db] = signalPower[db] – noisePower[db]
 * noisePower[db] = signalPower[db] - snr[db]
 * signalPower = I^2 + Q^2 -> linear scale
 * I = Q = sqrt(noisePower/2) -> linear scale
 * w[n] = N(0,1)*I + (N(0,1)*Q)j
 */

void System::awgnChannel(uint8 snr)
{
    System::noiseGenerator();
    // noise_power[db] = signal_power[db] - snr[db]
    float noise_power_db = 10 * log10(pow(abs(System::sample_cp[0]), 2)) - snr;
    // linear to db -> 10log10(linear)
    // db to linear -> 10^(db/20)
    float noise_power_linear = pow(10, noise_power_db / 10); // conversion to linear scale
    float i_noise, q_noise;

    i_noise = sqrt(noise_power_linear / 2);
    q_noise = sqrt(noise_power_linear / 2);
    for (uint8 i = 0; i < 40; i++)
    {
        complex<float> w(i_noise * System::random_noise[i], q_noise * System::random_noise[i]);
        System::sample_cp[i].real(real(System::sample_cp[i]) + real(w));
        System::sample_cp[i].imag(imag(System::sample_cp[i]) + imag(w));
    }
}

void System::noiseGenerator()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<float> distribution(0.0, 1.0); // mean = 0, standard deviation = 1
    for (uint8 i = 0; i < 40; i++)
    {
        System::random_noise.push_back(distribution(generator));
    }
}