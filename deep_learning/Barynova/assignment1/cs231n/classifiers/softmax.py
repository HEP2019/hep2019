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
  loss = 0.0
  for i in range(num_train):
    scores = X[i].dot(W)
    lim_scores = scores - np.max(scores)  
    loss += - lim_scores[y[i]] + np.log(np.sum(np.exp(lim_scores)))      
    for j in range(num_classes):
        softmax = np.exp(lim_scores[j]) / np.sum(np.exp(lim_scores))
        if j == y[i]:
            dW[:,j] += (softmax - 1) * X[i]
        else:
            dW[:,j] += softmax * X[i]        
  
  loss /= num_train  # Normalize
  dW /= num_train  # Normalize
  
  loss += 0.5 * reg * np.sum(W * W)  # Regularize
  dW += reg * W   # Regularize

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
  lim_scores = scores - np.max(scores) # Limit scores
  
  correct_scores = lim_scores[np.arange(num_train), y]
  
  loss_array = - correct_scores + np.log(np.sum(np.exp(lim_scores), axis=1))
  loss = np.sum(loss_array)

  softmaxes = np.exp(lim_scores) / np.sum(np.exp(lim_scores), axis=1)[:,None]

  A = np.zeros([num_train, num_classes]) 
  A[np.arange(num_train), y] = -1
  A += softmaxes
  
  dW = X.T.dot(A) # Compute gradient
  
  loss /= num_train # Normalize
  dW /= num_train # Normalize
  loss += 0.5 * reg * np.sum(W * W) # Regularize
  dW += reg * W  # Regularize

  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

