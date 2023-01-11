#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {

   std::ofstream _filtered_output_file("_filtered_output");
   std::ofstream _original_signal_file("_original_signal");

   // Parameters
   const int samples = 200;
   const int N = samples; // Filter length
   double mu = 0.05; //Adjustment

   // Sine Parameters & Values
   double A = 1;
   double f = 5;
   double d[samples];
   double x[samples] = {0.0};
   double a = 2;
   double t;

   // Filter Variables
   double y;
   double h[N] = {0.0};
   double e;

   // Get Sine-Values
   for(int n=0; n<samples; n++){
      t = n/double(samples);
      d[n] = A * sin(2 * M_PI * f * t);
      x[n] = A * sin(2 * M_PI * f * t) * pow(M_E, -a * f * t);
   }
   
   // LMS Algorithm

   for (int n = 0; n < samples; n++) {
        //Calculate Filter Output
        y = 0;
        for (int k = 0; k < n; k++) {
            y += h[k] * x[n - k - 1];
        }

        _filtered_output_file << n << " " << y << std::endl;
        _original_signal_file << n << " " << x[n] << std::endl;

        //LMS Implementation
        e = d[n] - y;
        for (int k = 0; k < N; k++) {
            h[k] += mu * e * x[n-k-1];
        }
    }


   _filtered_output_file.close();
   _original_signal_file.close();
   return 0;
}
