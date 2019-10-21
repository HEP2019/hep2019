import numpy as np
from random import shuffle

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  num_classes = W.shape[1]
  num_train = X.shape[0]
  for i in range(num_train):
    scores = X[i].dot(W)
    scores -= scores.max()#make numbers smaller
    #softmax
    score_exp = np.exp(scores[y[i]])
    score_exp_sum = np.sum(np.exp(scores))
    #loss function
    loss -= np.log(score_exp/score_exp_sum)
    dW[:, y[i]] -= (score_exp_sum - score_exp)/score_exp_sum*X[i]
    for j in range(num_classes):
          if j != y[i]:
            dW[:, j] += np.exp(scores[j]) / score_exp_sum * X[i]
  loss /= num_train
  dW = dW / num_train
  #regularization
  loss += reg * np.sum(W * W)
  dW += reg * 2 * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  num_classes = W.shape[1]
  num_train = X.shape[0]
  scores = X.dot(W)
  scores -= scores.max()

  scores = np.exp(scores)
  scores_sums = np.sum(scores, axis=1)
  cors = scores[range(num_train), y]
  loss = cors / scores_sums
  loss = -np.sum(np.log(loss))/num_train + reg * np.sum(W * W)

  s = np.divide(scores, scores_sums.reshape(num_train, 1))
  s[range(num_train), y] = - (scores_sums - cors) / scores_sums
  dW = X.T.dot(s)
  dW /= num_train
  dW += 2 * reg * W#regularization
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

