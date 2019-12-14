#!/bin/env python
import gensim
import json
import getopt
import sys
from sklearn.manifold import TSNE
import numpy as np
import matplotlib.pyplot as plt

import logging
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

def display_closestwords_tsnescatterplot(model, word):

    arr = np.empty((0,100), dtype='f')
    word_labels = [word]

    # get close words
    close_words = model.wv.most_similar(word, topn=20)

    # add the vector for each of the closest words to the array
    arr = np.append(arr, np.array([model.wv[word]]), axis=0)
    for wrd_score in close_words:
        wrd_vector = model[wrd_score[0]]
        word_labels.append(wrd_score[0])
        arr = np.append(arr, np.array([wrd_vector]), axis=0)

    # find tsne coords for 2 dimensions
    tsne = TSNE(n_components=2, random_state=0)
    np.set_printoptions(suppress=True)
    Y = tsne.fit_transform(arr)

    x_coords = Y[:, 0]
    y_coords = Y[:, 1]
    # display scatter plot
    plt.scatter(x_coords, y_coords)

    for label, x, y in zip(word_labels, x_coords, y_coords):
        plt.annotate(label, xy=(x, y), xytext=(0, 0), textcoords='offset points')
    plt.xlim(x_coords.min()+0.00005, x_coords.max()+0.00005)
    plt.ylim(y_coords.min()+0.00005, y_coords.max()+0.00005)
    plt.show()

DATA_PATH = "/home/pidhii/studystaff/w2v/data/articleliterals_db.json"
N_ARTICLES = 500000

LOAD = None
TRAIN = None
SKIP = 0
N_THREADS = 4
EPOCHS = 1

opts, args = getopt.getopt(sys.argv[1:], "hl:t:n:s:j:e:")
for o, a in opts:
    if o in ("-h"):
        print("usage: " + sys.argv[0] + " [OPTIONS]")
        print("")
        print("OPTIONS:")
        print("  -l <path> Load pretrained model.")
        print("  -t <path> Train model and save to given path.")
        print("  -n <int>  Number of articles to train with.")
        print("  -s <int>  Number of texts to skip.")
        print("  -j <int>  Number of CPU threads to use.")
        print("  -e <int>  Epochs to train.")
        quit(0)
    elif o in ("-l"):
        LOAD = a
    elif o in ("-t"):
        TRAIN = a
    elif o in ("-n"):
        N_ARTICLES = int(a)
    elif o in ("-s"):
        SKIP = int(a)
    elif o in ("-j"):
        N_THREADS = int(a)
    elif o in ("-e"):
        EPOCHS = int(a)
    else:
        print("Error: undefined commandline-option, " + o)
        quit(1)

def readData(path):
    with open(path) as dataFile:
        for line in dataFile:
            yield json.loads(line)

def loadArticles(path):
    for article in readData(path):
        yield article[1]

def take(n, l):
    for _, x in zip(range(n), l): yield x

def skip(n, l):
    # skip firt n elements
    for _, _ in zip(range(n), l): pass
    # yield the rest of elements
    for x in l: yield x

def buildModel(path=None, j=4):
    if path:
        print("loading model from '" + path + "'")
        return gensim.models.word2vec.Word2Vec.load(path)
    else:
        print("bulding fresh model")
        return gensim.models.word2vec.Word2Vec(window=1000000, workers=j, sg=1)

def trainModel(model, ntake, nskip=0, epochs=10):
    # print("updating vocabulary")
    # articles = take(ntake, skip(nskip, loadArticles(DATA_PATH)))
    # model.build_vocab(articles, update=True)
    print("training model")
    articles = take(ntake, skip(nskip, loadArticles(DATA_PATH)))
    model.train(sentences=articles, total_examples=ntake, report_delay=60., epochs=epochs)

model = buildModel(LOAD, j=N_THREADS)
print(model.wv)

if TRAIN:
    trainModel(model, ntake=N_ARTICLES, nskip=SKIP, epochs=EPOCHS)
    print("saving model to '" + TRAIN + "'")
    model.save(TRAIN)
    # articles = list(take(N_ARTICLES, loadArticles(DATA_PATH)))
    # model = gensim.models.word2vec.Word2Vec(sentences=articles, window=1000000, workers=3, iter=10)
    # model.save(TRAIN)
else:
    print("entering interactive mode")
    print("enter 'quit' or 'exit' to finish")
    # print(model.wv.most_similar
    while True:
        print()
        words = input("Enter words: ")
        if words in ("quit", "exit"):
            break

        words = list(words.split())
        if words[0] == "plot":
            display_closestwords_tsnescatterplot(model, words[1])
        else:
            sign = '+'
            positive = []
            negative = []
            try:
                for word in words:
                    if sign == '+':
                        positive += [word]
                        sign = ''
                    elif sign == '-':
                        negative += [word]
                        sign = ''
                    else:
                        sign = word
                        if sign not in ('-', '+'):
                            print("Error: sign expected, got '" + word + "'")
                            raise RuntimeError("invalid input")
            except:
                print("Please try again")
                continue
            print("positive: ", positive)
            print("negative: ", negative)
            try:
                for x in model.wv.most_similar(positive, negative):
                    print(x)
            except KeyError as e:
                print("Error: " + str(e))
