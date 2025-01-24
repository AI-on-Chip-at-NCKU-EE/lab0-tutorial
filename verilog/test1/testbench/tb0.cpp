#include <verilated.h>  // Include common routines

#include <cassert>
#include <fstream>
#include <iostream>

#include "Vfull_adder.h"
#include "verilated_vcd_c.h"

using namespace std;

#define MAX_CYCLE 100000
#define CYCLE 10

#define step(dut, fp, time) \
    (fp)->dump(time);       \
    (time) += CYCLE / 2;    \
    (dut)->eval();

#define set_signal(dut, signal, value) \
    (signal) = (value);                \
    (dut)->eval();

int main(int argc, char** argv) {
    int time = 0;
    bool pass = true;

    Verilated::traceEverOn(true);
    VerilatedVcdC* fp = new VerilatedVcdC();

    auto dut = new Vfull_adder;
    dut->trace(fp, 99);
    fp->open("build/full_adder_wave.vcd");

    // Test all possible input combinations for a full adder
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            for (int cin = 0; cin < 2; cin++) {
                set_signal(dut, dut->a, a);
                set_signal(dut, dut->b, b);
                set_signal(dut, dut->cin, cin);

                step(dut, fp, time);
                dut->eval();

                // Calculate expected results
                int expected_sum = (a ^ b ^ cin);
                int expected_cout = (a & b) | (b & cin) | (cin & a);

                // Compare with golden reference
                cout << "a: " << a << " b: " << b << " cin: " << cin << " -> ";
                if (dut->sum == expected_sum && dut->cout == expected_cout) {
                    cout << "Simulation pass!" << endl;
                } else {
                    cout << "sum: " << (int)dut->sum << " cout: " << (int)dut->cout
                         << " (expected sum: " << expected_sum << " expected cout: " << expected_cout << ")" << endl;
                    pass = false;
                }
            }
        }
    }
    cout << "---------------------------------" << endl;
    if (pass) {
        ifstream inFile("../art/pass.txt");
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        ifstream inFile("../art/fail.txt");
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }

    fp->close();
    dut->final();
    delete dut;
    return 0;
}
