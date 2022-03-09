import index
import api

with open('index.txt') as index_file:
    print(" ".join([l.rstrip() for l in index_file]))