import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import matplotlib.animation as animation
import numpy as np
import time
import json

from sklearn.cluster import DBSCAN
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import normalize
from sklearn.decomposition import PCA
from sklearn import metrics
from sklearn.datasets import make_blobs
from sklearn import decomposition
from sklearn import datasets

import paho.mqtt.client as mqtt
# variable de comptage pour getMesure
nbValues = 0

# Successful Connection Callback
def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe('\showroom\Lidar')

tab=[]
# Message delivery callback
def on_message(client, userdata, msg):
    global nbValues
    print(nbValues)
    message = str(msg.payload.decode("utf-8"))
    #print(message)
    json_msg = json.loads(message)
    to_append=[]
    for json_obj in json_msg:
        keys = list(json_obj.keys())
        to_append.append(json_obj.get(keys[0]))
    tab.append(to_append)
    nbValues = nbValues + 1

def append_limit(value, list):
    if(len(list)>=15):
        del list[0]
    list.append(value)

def getMesure(n): # n= nombre de mesure à mettre dans res
    # on ne prends les valeurs que lors de l'appel de la fonction
    global nbValues
    client.loop_start()
    while True:
        if n==nbValues :
            break
    client.loop_stop()
    return tab # tab = [ [angle, distance],......., [angle, distance], [angle, distance],] de sorte que len (res)=n


"""         Traitement des données         """
def PolarToCart(angle,distance):
    x = distance*np.cos(angle*((2*np.pi)/360))
    y = distance*np.sin(angle*((2*np.pi)/360))
    return [x,y]

def animate(i, xs, ys):
    # Limit x and y lists to 20 items
    #xs = xs[-20:]
    #ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.scatter(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Lidar')
    plt.ylabel('Distance')



##########################################################################################################
client = mqtt.Client()

# Set callback handler
client.on_connect = on_connect
client.on_message = on_message

# Set up connection
client.connect('10.100.100.117', 443, 60)
# Publish message
client.publish('\showroom\Lidar',payload='SUR',qos=0)


# valeur en continu
#client.loop_forever()

#print(getMesure(10))


t=time.time()


# initialisation, détection des centres des murs
# mesure de la pièce vide
# mise en liste des coordonnées des clusters de chaque murs

# mesure à vide
clusters = getMesure(10)
# le premier cluster est forcement un mur
posMurs=[clusters[0]] # cluster[0] = [angleMoyen] et clusters[1] = [distanceMoyenne]
# on parcours l'ensemble des clusters
for i in clusters:
    # ajout des autres murs
    for j in posMurs:
        # en parcourant la liste des clusters si pas déja présent 
        # dans la liste des murs on l'ajoute (+- une marge)
        # sinon on l'ignore
        if not(j[0]-10 < i[0] < j[0] + 10 and j[1]-200 < i[1] < j[1] + 200):
            posMurs.append(i)

print("position des murs à vide", posMurs)

# détection des personnes en continue
posPers = []
while True:
    nbValues = 0 # compteur pour visualiser l'avancé
    clusters = getMesure(2) # on récupère quelques clusters
    # on parcours les derniers clusters acquis
    for i in clusters:
        # on parcours les clusters des murs
        for j in posMurs:
            # en parcourant la liste des nouveaux clusters si il N'ESt PAS 
            # dans la liste des murs on l'ajoute (+- une marge)  à la liste des personnes
            # sinon on l'ignore
            if not(j[0]-10 < i[0] < j[0] + 10 and j[1]-200 < i[1] < j[1] + 200):
                posPers.append(i)

    print("position des personnes", posPers)


