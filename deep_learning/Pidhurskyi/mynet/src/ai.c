#include "ai/ai.h"
#include <libconfig.h>
#include <limits.h>
#include <float.h>

#define AI_DEFINE_PROPAGATION(name, activation_expr)                           \
  void                                                                         \
  name(ai_layer *layer)                                                        \
  {                                                                            \
    double *out = layer->x;                                                    \
    size_t nout = layer->size;                                                 \
                                                                               \
    double *bias = layer->b;                                                   \
                                                                               \
    double *in = layer->input->x;                                              \
    size_t nin = layer->input->size;                                           \
                                                                               \
    for (size_t iout = 0; iout < nout; ++iout) {                               \
      /* calculate weighted sum of inputs */                                   \
      double *w = al_layer_get_weights(layer, iout);                           \
      double sum = 0;                                                          \
      for (size_t iin = 0; iin < nin; ++iin)                                   \
        sum += in[iin] * w[iin];                                               \
                                                                               \
      /* apply activation */                                                   \
      double s = sum + bias[iout];                                             \
      out[iout] = activation_expr;                                             \
    }                                                                          \
  }
static
AI_DEFINE_PROPAGATION(forward_sigmoid, ai_sigmoid(s));
static
AI_DEFINE_PROPAGATION(forward_relu, ai_relu(s));
static
AI_DEFINE_PROPAGATION(forward_sqrt,
    (s > 0)
      ? +sqrt(s + 0.25) - 0.5
      : -sqrt(-s + 0.25) + 0.5
);

void
ai_layer_forward(ai_layer *layer)
{
  /*layer->forward(layer);*/
  switch (layer->activation) {
    case AI_SIGMOID:
      forward_sigmoid(layer);
      break;

    case AI_RELU:
      forward_relu(layer);
      break;

    case AI_SQRT:
      forward_sqrt(layer);
      break;

    default:
      assert(!"undefined activation");
  }
}

static void
start_backward_sigmoid(ai_layer *layer, double *dEdo, double lr)
{
  // i (input layer) -> j (output layer)
  //
  // Δw_ij = -η * δ_j * x_i
  // where
  //   δ_j = dE/do_j * do_j/dS_j

  double *input_x = layer->input->x;
  double *this_x = layer->x;
  double *this_d = layer->d;
  double *this_b = layer->b;
  size_t ni = layer->input->size;
  size_t nj = layer->size;

  for (size_t j = 0; j < nj; ++j) {
    double dodS = 2 * this_x[j] * (1. - this_x[j]);
    double dj = this_d[j] = dEdo[j] * dodS;

    double *w_j = al_layer_get_weights(layer, j);
    for (size_t i = 0; i < ni; ++i) {
      double dwij = -lr * this_d[j] * input_x[i];
      w_j[i] += dwij;
    }

    double dbj = -lr * dj;
    this_b[j] += dbj;
  }
}

void
ai_layer_start_backward(ai_layer *layer, double *dEdo, double lr)
{
  switch (layer->activation) {
    case AI_SIGMOID:
      start_backward_sigmoid(layer, dEdo, lr);
      break;

    default:
      assert(!"undefined activation");
  }
}

#define AI_DEFINE_BACKPROPAGATION(name, dxdS_expr)                             \
  void                                                                         \
  name(ai_layer *layer, double lr)                                             \
  {                                                                            \
    /* i (input layer) -> j (this layer) -> k (output layer) */                \
    /* */                                                                      \
    /* Δw_ij = -η * δ_j * x_i */                                               \
    /* where */                                                                \
    /*   δ_j = dx_j/dS_j * Σ_k δ_k ω_jk */                                     \
                                                                               \
    size_t ni = layer->input->size;                                            \
    size_t nj = layer->size;                                                   \
    size_t nk = layer->next->size;                                             \
                                                                               \
    double *x_input = layer->input->x;                                         \
    double *x_this = layer->x;                                                 \
    double *d_this = layer->d;                                                 \
    double *b_this = layer->b;                                                 \
    double *d_out = layer->next->d;                                            \
                                                                               \
    for (size_t j = 0; j < nj; ++j) {                                          \
      double *wj = al_layer_get_weights(layer, j);                             \
                                                                               \
      double xj = x_this[j];                                                   \
      double dxdS = dxdS_expr; /* dx_j/dS_j */                                 \
                                                                               \
      double sum = 0; /* Σ_k δ_k ω_jk */                                       \
      for (size_t k = 0; k < nk; ++k) {                                        \
        double wjk = al_layer_get_weights(layer->next, k)[j]; /* w_jk */       \
        double dk = d_out[k]; /* δ_k */                                        \
        sum += dk * wjk;                                                       \
      }                                                                        \
      double dj = d_this[j] = dxdS * sum; /* δ_j */                            \
                                                                               \
      for (size_t i = 0; i < ni; ++i) {                                        \
        double xi = x_input[i]; /* x_i */                                      \
        double dwij = -lr * dj * xi; /* Δω_ij */                               \
        wj[i] += dwij;                                                         \
      }                                                                        \
                                                                               \
      double dbj = -lr * dj; /* Δb_j */                                        \
      b_this[j] += dbj;                                                        \
    }                                                                          \
  }
static
AI_DEFINE_BACKPROPAGATION(backward_sigmoid,
    2. * xj * (1. - xj)
)
static
AI_DEFINE_BACKPROPAGATION(backward_relu,
    xj < 0. ? 0. : 1.
)
static
AI_DEFINE_BACKPROPAGATION(backward_sqrt,
    (xj > 0)
      ? +0.5 / (xj + 0.5)
      : -0.5 / (xj - 0.5)
)

void
ai_layer_backward(ai_layer *layer, double lr)
{
  switch (layer->activation) {
    case AI_SIGMOID:
      backward_sigmoid(layer, lr);
      break;

    case AI_RELU:
      backward_relu(layer, lr);
      break;

    case AI_SQRT:
      backward_sqrt(layer, lr);
      break;

    default:
      assert(!"undefined activation");
  }
}

ai_layer*
ai_new_input_layer(size_t size)
{
  ai_layer *layer = calloc(1, sizeof(ai_layer));
  layer->size = size;
  layer->x = malloc(sizeof(double) * size);
  return layer;
}

ai_layer*
ai_new_layer(ai_layer *input, size_t size, int activation)
{
  ai_layer *layer = calloc(1, sizeof(ai_layer));

  layer->input = input;
  input->next = layer;

  layer->size = size;
  layer->x = malloc(sizeof(double) * size);

  layer->b = calloc(size, sizeof(double));
  /*layer->db = malloc(sizeof(double) * size);*/
  layer->d = malloc(sizeof(double) * size);

  layer->w = input ? malloc(sizeof(double) * size * input->size) : NULL;
  /*layer->dw = input ? calloc(size * input->size, sizeof(double)) : NULL;*/

  layer->activation = activation;
  /*switch (activation) {*/
    /*case AI_SIGMOID:*/
      /*layer->forward = forward_sigmoid;*/
      /*layer->backward = backward_sigmoid;*/
      /*break;*/

    /*case AI_RELU:*/
      /*layer->forward = forward_relu;*/
      /*layer->backward = backward_relu;*/
      /*break;*/

    /*case AI_SQRT:*/
      /*layer->forward = forward_sqrt;*/
      /*layer->backward = backward_sqrt;*/
      /*break;*/

    /*default:*/
      /*assert(!"undefined activation");*/
  /*}*/
  return layer;
}

void
ai_delete_layer(ai_layer *layer)
{
  free(layer->x);
  free(layer->d);
  if (layer->b)
    free(layer->b);
  /*free(layer->db);*/

  if (layer->w)
    free(layer->w);
  /*if (layer->dw)*/
    /*free(layer->dw);*/

  free(layer);
}

void
ai_layer_randomize_weights(ai_layer *layer, double amplitude)
{
  assert(layer->input);
  size_t nw = layer->size * layer->input->size;
  double *w = layer->w;
  for (size_t i = 0; i < nw; ++i)
    w[i] = 2 * amplitude * drand48() - 1;
}

ai_dnn*
ai_new_dnn(void)
{
  ai_dnn *dnn = malloc(sizeof(ai_dnn));
  cod_vec_init(dnn->grid);
  cod_vec_init(dnn->outputs);
  return dnn;
}

void
ai_delete_dnn(ai_dnn *dnn)
{
  for (size_t irow = 0; irow < dnn->grid.len; ++irow) {
    ai_layers_t row = dnn->grid.data[irow];
    for (size_t ilayer = 0; ilayer < row.len; ++ilayer)
      ai_delete_layer(row.data[ilayer]);
    cod_vec_destroy(row);
  }
  cod_vec_destroy(dnn->grid);

  for (size_t i = 0; i < dnn->outputs.len; ++i)
    ai_delete_layer(dnn->outputs.data[i]);
  cod_vec_destroy(dnn->outputs);

  free(dnn);
}

void
ai_dnn_add_layer(ai_dnn *dnn, size_t row, size_t col, ai_layer *layer)
{
  while (dnn->grid.len <= row) {
    cod_vec_push(dnn->grid, ((ai_layers_t) { 0, 0, 0 }));
    cod_vec_init(cod_vec_back(dnn->grid));
  }
  cod_vec_push(dnn->grid.data[row], layer);
}

void
ai_dnn_add_output_layer(ai_dnn *dnn, ai_layer *layer)
{
  cod_vec_push(dnn->outputs, layer);
}

void
ai_dnn_eval(ai_dnn *dnn)
{
  for (size_t irow = 0; irow < dnn->grid.len; ++irow) {
    ai_layers_t layers = dnn->grid.data[irow];
    for (size_t ilayer = 0; ilayer < layers.len; ++ilayer) {
      ai_layer_forward(layers.data[ilayer]);
    }
  }

  for (size_t i = 0; i < dnn->outputs.len; ++i)
    ai_layer_forward(dnn->outputs.data[i]);
}

void
ai_dnn_fit(ai_dnn *dnn, double lr)
{
  for (int irow = dnn->grid.len - 1; irow >= 0; --irow) {
    ai_layers_t layers = dnn->grid.data[irow];
    for (size_t ilayer = 0; ilayer < layers.len; ++ilayer) {
      ai_layer_backward(layers.data[ilayer], lr);
    }
  }
}

