#ifndef AI_H
#define AI_H

#include "codeine/vec.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define ai_min(x, y) ((x) < (y) ? (x) : (y))
#define ai_max(x, y) ((x) > (y) ? (x) : (y))

static inline double
ai_sigmoid(double x)
{ return 1. / (1. + exp(-2 * x)); }

static inline double
ai_relu(double x)
{ return x < 0 ? 0 : x; }

typedef struct ai_layer ai_layer;
typedef struct ai_dnn   ai_dnn;

enum {
  AI_SIGMOID = 1,
  AI_RELU,
  AI_SQRT,
};

struct ai_layer {
  ai_layer *input;
  ai_layer *next;
  size_t size;
  double *x;  // x: values of the nodes after forward propagation
  double *d;  // δ
  double *w;  // ω: weights between this and input layer
  /*double *dw; // Δω: dE/dω on previous step*/
  double *b;  // b: bias
  /*double *db; // Δb: dE/db on brevious step*/

  char activation;
  /*void (*forward)(ai_layer *self);*/
  /*void (*backward)(ai_layer *layer, double lr);*/
};

ai_layer*
ai_new_input_layer(size_t size);

ai_layer*
ai_new_layer(ai_layer *input, size_t size, int activation);

void
ai_delete_layer(ai_layer *layer);

static inline double*
al_layer_get_weights(ai_layer *layer, size_t nodeidx)
{
  /*assert(layer->input);*/
  return layer->w + nodeidx * layer->input->size;
}

/*static inline double**/
/*ai_get_weights_delta(ai_layer *layer, size_t nodeidx)*/
/*{*/
  /*assert(layer->input);*/
  /*return layer->dw + nodeidx * layer->input->size;*/
/*}*/

void
ai_layer_forward(ai_layer *layer);

void
ai_layer_start_backward(ai_layer *layer, double *dEdo, double lr);

void
ai_layer_backward(ai_layer *layer, double lr);

void
ai_layer_randomize_weights(ai_layer *layer, double amplitude);

typedef cod_vec(ai_layer*) ai_layers_t;
typedef cod_vec(ai_layers_t) ai_grid_t;
struct ai_dnn {
  ai_grid_t grid;
  ai_layers_t outputs;
};

ai_dnn*
ai_new_dnn(void);

void
ai_delete_dnn(ai_dnn *dnn);

void
ai_dnn_add_layer(ai_dnn *dnn, size_t row, size_t col, ai_layer *layer);

void
ai_dnn_add_output_layer(ai_dnn *dnn, ai_layer *layer);

void
ai_dnn_eval(ai_dnn *dnn);

void
ai_dnn_fit(ai_dnn *dnn, double lr);

#endif
