#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H
#include "cuda.h"
#include "math.h"



typedef enum{
    LOGISTIC, RELU, RELIE, LINEAR, RAMP, TANH, PLSE, LEAKY, ELU, LOGGY
}ACTIVATION;

ACTIVATION get_activation(char *s);

char *get_activation_string(ACTIVATION a);
float activate(float x, ACTIVATION a);
float gradient(float x, ACTIVATION a);
void gradient_array(const float *x, const int n, const ACTIVATION a, float *delta);
void activate_array(float *x, const int n, const ACTIVATION a);
#ifdef GPU
void activate_array_ongpu(float *x, int n, ACTIVATION a);
void gradient_array_ongpu(float *x, int n, ACTIVATION a, float *delta);
#endif


static float linear_activate(float x){ return x; }
static float logistic_activate(float x){ return 1. / (1. + exp(-x)); }
static float loggy_activate(float x){ return 2. / (1. + exp(-x)) - 1; }
static float relu_activate(float x){ return x*(x>0); }
static float elu_activate(float x){ return (x >= 0)*x + (x < 0)*(exp(x) - 1); }
static float relie_activate(float x){ return x*(x>0); }
static float ramp_activate(float x){ return x*(x>0) + .1*x; }
static float leaky_activate(float x){ return (x>0) ? x : .1*x; }
static float tanh_activate(float x){ return (exp(2 * x) - 1) / (exp(2 * x) + 1); }
static float plse_activate(float x)
{
    if(x < -4) return .01 * (x + 4);
    if(x > 4)  return .01 * (x - 4) + 1;
    return .125*x + .5;
}

static float linear_gradient(float x){ return 1; }
static float logistic_gradient(float x){ return (1 - x)*x; }
static float loggy_gradient(float x)
{
    float y = (x+1.)/2.;
    return 2*(1-y)*y;
}
static float relu_gradient(float x){ return (x>0); }
static float elu_gradient(float x){ return (x >= 0) + (x < 0)*(x + 1); }
static float relie_gradient(float x){ return (x>0) ? 1 : .01; }
static float ramp_gradient(float x){ return (x>0) + .1; }
static float leaky_gradient(float x){ return (x>0) ? 1 : .1; }
static float tanh_gradient(float x){ return 1 - x*x; }
static float plse_gradient(float x){ return (x < 0 || x > 1) ? .01 : .125; }

#endif

