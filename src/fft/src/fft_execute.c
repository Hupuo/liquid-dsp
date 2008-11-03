//
// fft : inefficient but effective
//

#include <math.h>
#include "fft_internal.h"

void fft_execute(fftplan _p)
{
    if (_p->n <= FFT_SIZE_TWIDDLE)
        fft_execute_twiddle_table(_p);
    else
        fft_execute_dft(_p);
}

void fft_execute_dft(fftplan _p)
{
    unsigned int k, n, N=_p->n;
    float phi, d = (_p->direction==FFT_FORWARD) ? -1 : 1;
    for (k=0; k<N; k++) {
        _p->y[k] = 0.0f;
        for (n=0; n<N; n++) {
            phi = 2*M_PI*d*((float)n)*((float)k) / (float) (N);
            _p->y[k] += _p->x[n] * cexpf(_Complex_I*phi);
        }
    }
}

void fft_execute_twiddle_table(fftplan _p)
{
    unsigned int k, n, N=_p->n;
    for (k=0; k<N; k++) {
        _p->y[k] = 0.0f;
        for (n=0; n<N; n++) {
            // _p->y[k] = dot_prod_cc(_p->x, &_p->twiddle[k*N]);
            _p->y[k] += _p->x[n] * _p->twiddle[k*N + n];
        }
    }
}

