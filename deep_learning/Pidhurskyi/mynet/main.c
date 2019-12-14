#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "codeine/vec.h"
#include "ai/ai.h"

ai_layer *output_layer,
         *input_layer;

void
show_output(FILE *gp, ai_dnn *dnn, int stop)
{
  // Dump predictions
  size_t n = 50;
  double dx = 1. / n;
  double dy = 1. / n;
  fprintf(gp, "plot '-' u 1:2:3 with points palette pt 5 ps 4\n");
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      double x = -0.5 + dx * i + dx/2;
      double y = -0.5 + dy * j + dy/2;
      input_layer->x[0] = x;
      input_layer->x[1] = y;

      ai_dnn_eval(dnn);
      double pred = output_layer->x[0];

      fprintf(gp, "%lf\t%lf\t%lf\n", x, y, pred);
    }
  }

  fprintf(gp, "e\n");
  if (stop)
    fprintf(gp, "pause mouse close\n");

  fflush(gp);
}

static inline int
is_signal(double x, double y)
{
  return sqrt((x - 0.25)*(x - 0.25) + (y - 0.25)*(y - 0.25)) < 0.05
      || sqrt((x + 0.25)*(x + 0.25) + (y + 0.25)*(y + 0.25)) < 0.10
      || sqrt((x + 0.25)*(x + 0.25) + (y - 0.25)*(y - 0.25)) < 0.15
      || sqrt((x - 0.25)*(x - 0.25) + (y + 0.25)*(y + 0.25)) < 0.05
      || sqrt((x - 0.00)*(x - 0.00) + (y + 0.00)*(y + 0.00)) < 0.15;
}

int
main()
{
  srand48(time(NULL));

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Build DNN
  //
  // input layer
  input_layer = ai_new_input_layer(2);

  // hidden layers
  ai_layer *hidden_layer1 = ai_new_layer(input_layer, 8, AI_RELU);
  ai_layer_randomize_weights(hidden_layer1, 1);

  ai_layer *hidden_layer2 = ai_new_layer(hidden_layer1, 16, AI_RELU);
  ai_layer_randomize_weights(hidden_layer2, 1);

  ai_layer *hidden_layer3 = ai_new_layer(hidden_layer2, 16, AI_RELU);
  ai_layer_randomize_weights(hidden_layer3, 1);

  // output layer
  output_layer = ai_new_layer(hidden_layer3, 1, AI_SIGMOID);
  ai_layer_randomize_weights(output_layer, 1);


  ai_dnn *dnn = ai_new_dnn();
  ai_dnn_add_layer(dnn, 0, 0, hidden_layer1);
  ai_dnn_add_layer(dnn, 1, 0, hidden_layer2);
  ai_dnn_add_layer(dnn, 2, 0, hidden_layer3);
  ai_dnn_add_output_layer(dnn, output_layer);


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Generate data
  //
  typedef struct point { double x, y; } point;
  cod_vec(point) data_train;
  cod_vec_init(data_train);
  cod_vec(int) labels_train;
  cod_vec_init(labels_train);
  //
  cod_vec(point) data_test;
  cod_vec_init(data_test);
  cod_vec(int) labels_test;
  cod_vec_init(labels_test);

  size_t n = 1024*2;
  while (n--) {
    // train
    point pt = { .x = drand48() - 0.5, .y = drand48() - 0.5 };
    cod_vec_push(data_train, pt);
    cod_vec_push(labels_train, is_signal(pt.x, pt.y));
  }

  n = 512;
  while (n--) {
    // train
    point pt = { .x = drand48() - 0.5, .y = drand48() - 0.5 };
    cod_vec_push(data_test, pt);
    cod_vec_push(labels_test, is_signal(pt.x, pt.y));
  }

  // Dump data
  FILE *out = fopen("data.txt", "w");
  for (size_t i = 0; i < data_train.len; ++i) {
    fprintf(out, "%lf\t%lf\t%d\n", data_train.data[i].x, data_train.data[i].y,
        labels_train.data[i]);
  }
  fclose(out);

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // Train
  //
  FILE *gp_loss = popen("gnuplot &>/dev/null", "w");
  cod_vec(double) loss_train;
  cod_vec_init(loss_train);
  //
  cod_vec(double) loss_test;
  cod_vec_init(loss_test);

  FILE *gp_output = popen("gnuplot &>/dev/null", "w");

  size_t BATCH_SIZE = 1;
  size_t EPOCHS = 5000;
  int id = 0;
  for (size_t epoch = 1; epoch <= EPOCHS; ++epoch) {

    double mean_loss = 0;
    for (size_t idata = 0; idata < data_train.len; ++idata) {
      // load input features
      input_layer->x[0] = data_train.data[idata].x;
      input_layer->x[1] = data_train.data[idata].y;
      // evaluate DNN
      ai_dnn_eval(dnn);

#define CROSSENTROPY
#ifdef CROSSENTROPY
      // cross entropy
      double t = labels_train.data[idata];
      double o = output_layer->x[0];
      double loss = -(t * log(o + DBL_EPSILON) + (1. - t) * log(1. - o + DBL_EPSILON));
      mean_loss += loss;
      // dE/do
      double dEdo[] = { (o - t) / (o * (1. - o) + DBL_EPSILON) };
#else
      // calculate loss (sum of squares)
      double diff = output_layer->x[0] - labels_train.data[idata];
      double loss = 0.5 * diff * diff;
      mean_loss += loss;
      // calculate dEdo (E = sum of squares)
      double t = labels_train.data[idata];
      double o = output_layer->x[0];
      double dEdo[] = { (o - t) };
#endif

      double lr = 0.0001;
      ai_layer_start_backward(output_layer, dEdo, lr);
      ai_dnn_fit(dnn, lr);
    }
    mean_loss /= data_train.len;
    cod_vec_push(loss_train, mean_loss);

    mean_loss = 0;
    for (size_t idata = 0; idata < data_test.len; ++idata) {
      // load input features
      input_layer->x[0] = data_test.data[idata].x;
      input_layer->x[1] = data_test.data[idata].y;
      // evaluate DNN
      ai_dnn_eval(dnn);

#define CROSSENTROPY
#ifdef CROSSENTROPY
      // cross entropy
      double t = labels_test.data[idata];
      double o = output_layer->x[0];
      double loss = -(t * log(o + DBL_EPSILON) + (1. - t) * log(1. - o + DBL_EPSILON));
      mean_loss += loss;
#else
      // calculate loss (sum of squares)
      double diff = output_layer->x[0] - labels_test.data[idata];
      double loss = 0.5 * diff * diff;
      mean_loss += loss;
#endif
    }
    mean_loss /= data_test.len;
    cod_vec_push(loss_test, mean_loss);

    if (epoch % 100 == 0) {
      // show heat map
      show_output(gp_output, dnn, 0);

      // show loss history
      fprintf(gp_loss, "plot '-' title 'train loss' with points pt 1 ps 1,");
      fprintf(gp_loss, "     '-' title 'test loss' with points pt 1 ps 1\n");

      for (size_t i = 0; i < loss_train.len; ++i)
        fprintf(gp_loss, "%zu\t%lf\n", i, loss_train.data[i]);
      fprintf(gp_loss, "e\n");

      for (size_t i = 0; i < loss_test.len; ++i)
        fprintf(gp_loss, "%zu\t%lf\n", i, loss_test.data[i]);
      fprintf(gp_loss, "e\n");
    }

  }

  // final heat map
  show_output(gp_output, dnn, 1);

  // all loss history
  fprintf(gp_loss, "plot '-' with points pt 0\n");
  fprintf(gp_loss, "     '-' with points pt 0\n");

  for (size_t i = 0; i < loss_train.len; ++i)
    fprintf(gp_loss, "%zu\t%lf\n", i, loss_train.data[i]);
  fprintf(gp_loss, "e\n");

  for (size_t i = 0; i < loss_test.len; ++i)
    fprintf(gp_loss, "%zu\t%lf\n", i, loss_test.data[i]);
  fprintf(gp_loss, "e\n");

  fprintf(gp_loss, "pause mouse close\n");
  fflush(gp_loss);

  pclose(gp_loss);
  pclose(gp_output);

  ai_delete_dnn(dnn);
  ai_delete_layer(input_layer);

  cod_vec_destroy(data_train);
  cod_vec_destroy(labels_train);
}
