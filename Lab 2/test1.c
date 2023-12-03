#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float A;
    float omega;
    float sigma;
    int duration;
} asignal;

float analog_signal_generator(asignal signal, int t) {
    return signal.A * sin(signal.omega * t + signal.sigma);
}

void sampler(float *samples, int interval, asignal signal) {
    int t;
    for (t = 0; t < 1 + signal.duration / interval; t++) {
        float a = analog_signal_generator(signal, t * interval);
        samples[t+1] = a;
    }
    samples[0] = t;
}

void quantizer(float *samples, int *pcmpulses, int levels, float A) {
    int size = (int)samples[0];
    printf("%d\n", size);
    
    int i ;
    for (i = 1; i <= size; i++) {
        float x = samples[i];
        int q;
        q = (int)floor((x + A) / (2 * A) * levels);
        pcmpulses[i] = q;
    }
    pcmpulses[0] = size;
}

void quantizer1(float *samples, int *pcmpulses, int levels) {
  float Amin, Amax;
  int size = (int)samples[0];
  printf("%d\n", size);

  // Get the minimum and maximum sample values.
  Amin = samples[1];
  Amax = samples[1];
  for (int i = 1; i <= size; i++) {
    if (samples[i] < Amin) {
      Amin = samples[i];
    } else if (samples[i] > Amax) {
      Amax = samples[i];
    }
  }
  Amax = (int)ceil(Amax);
  Amin = (int)floor(Amin);
  printf("%f\n", Amax);
  printf("%f\n",Amin);
  
  // Quantize the samples.
  int i ;
  for (i = 1; i <= size; i++) {
    float x = samples[i];
    int q;
    q = (int)floor((x - Amin) / (Amax - Amin) * levels);
    pcmpulses[i] = q;
  }
  pcmpulses[0] = size;
}

void encoder(int *pcmpulses, int *dsignal, int encoderbits) {
    int size = (int)pcmpulses[0];
    int i;
    for (i = 0; i <= size; i++) {
        int pulse = pcmpulses[i+1];
        for (int bit = encoderbits - 1; bit >= 0; bit--) {
            int a = pulse % 2;
            dsignal[i * encoderbits + bit] = a;
            pulse /= 2;
        }
    }
}



void run(asignal * inputsignal) {
  // Define the analog signal parameters
  float A, omega, sigma;
  int duration, interval, encoderbits;

  // Get the input from the user
  char inp[100];
  fgets(inp, sizeof(inp), stdin);

  // Scan the string for the values
  sscanf(inp, "%f %f %f %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);
  int levels = pow(2,encoderbits);
  
  // Generate the analog signal
  inputsignal -> A = A;
  inputsignal -> omega = omega;
  inputsignal -> sigma = sigma;
  inputsignal -> duration = duration;

  asignal signal = {A, omega, sigma, duration};
  float *samples = (float *)malloc(sizeof(float) * (2 + duration / interval));
  sampler(samples, interval, signal);
  
  // Print the samples array
  for (int i = 0; i < 2 + duration / interval; i++) {
    printf("%f", samples[i]);
    printf("%s", " ");
  }
  printf("\n");
  
  // Quantize the samples
  int *pcmpulses = (int *)malloc(sizeof(int) * (2 + duration / interval));
  quantizer(samples, pcmpulses, levels, A);
  
  // Print the pcmpulses array
  for (int i = 0; i < 2 + duration / interval; i++) {
    printf("%d", pcmpulses[i]);
    printf("%s", " ");
  }
  printf("\n");

  // Encode the quantized values
  int a = encoderbits * (1 + duration / interval);

  int list[a];
  int *dsignal;
  dsignal = list;

  encoder(pcmpulses, dsignal, encoderbits);

  for (int i = 0; i < a; i++) {
    printf("%d", dsignal[i]);
  }

  // Free allocated memory
  free(samples);
  free(pcmpulses);
  //free(dsignal);
}

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}