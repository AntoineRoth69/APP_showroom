import numpy as np
import json
import time

import paho.mqtt.client as mqtt

import pygame
from pygame.locals import *

""" fonctionnement global : 

1 - le lidar mesure une centaine de points 
2 - ces points sont récupérés par la Rpi
3 - Un premier traitement est effectué sur la Rpi : clusterisation
4 - les clusters trouvés sont mis dans une liste pour être transmis au serveur MQTT
5 - Le script sur le PC recoit ces clusters depuis le serveur
6 - traitement côté PC:
initialisation => faire une mesure à vide et stocker les resultats, c'est les murs et le mobilier
main           => refaire une mesure comparer avec les murs, si différent => présence personne => maj carte pyGame

"""

""" récupération des coordonnées declusters détectés depuis le serveur MQTT """
# variable de comptage pour getMesure
nbValues = 0

# Successful Connection Callback
def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe('/showroom/Lidar')


# Message delivery callback
def on_message(client, userdata, msg):
    global nbValues
    global tab
    # print(nbValues)
    message = str(msg.payload.decode("utf-8"))
    # print(message)
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

def getMesure(n): # n = nombre de mesure à mettre dans res
    # on ne prends les valeurs que lors de l'appel de la fonction
    global nbValues
    nbValues = 0
    global tab
    tab = []
    client.loop_start()
    while n > nbValues:
        time.sleep(0.01)
    client.loop_stop()
    return tab # tab = [ [angle, distance],......., [angle, distance], [angle, distance],] de sorte que len (res)=n


"""         Traitement des données         """
def PolarToCart(angle,distance):
    x = distance*np.cos(angle*((2*np.pi)/360))
    y = distance*np.sin(angle*((2*np.pi)/360))
    return x,y



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

def estUnMur(cluster, murs):
    """ retourne Vrai si position est celle d'un mur présent dans murs Faux sinon
    l'idée c'est de faire :
    for cluster in clusters:
        if estUnMur(cluster, posMurs):
            redrawGameWindow(cluster[0], cluster[1]):
    """
    for mur in murs:
        if mur[0]-10 < cluster[0] < mur[0] + 10 and mur[1]-200 < cluster[1] < mur[1] + 200:
            return True
    return False

def getPersonnes(clusters):
    listePersonnes = []
    # on parcours les derniers clusters acquis
    for cluster in clusters:
        # si c'est pas un mur
        if not(estUnMur(cluster, posMurs)):
            listePersonnes.append(cluster)
    return listePersonnes
    
def redrawGameWindow(personnes, xLidar, yLidar):
    win.blit(bg, (0,0)) # commenter cette ligne pour visualiser la trace
    for personne in personnes:
        x, y = PolarToCart(personne[0], personne[1]/10)
        win.blit(pers, (x+xLidar, y+yLidar))
    pygame.display.update()

# initialisation, détection des centres des murs
# mesure de la pièce vide
# mise en liste des coordonnées des clusters de chaque murs

# mesure à vide
clusters = getMesure(10)
# le premier cluster est forcement un mur
posMurs=[clusters[0]] # cluster[0][0] = [angleMoyen] et clusters[1][0] = [distanceMoyenne]
# on parcours l'ensemble des clusters
for cluster in clusters:
    # ajout des autres murs sanchant que tout les clusters auront été traité quand i = len(clusters)
    # en parcourant la liste des clusters si pas déja présent 
    # dans la liste des murs on l'ajoute (+- une marge)
    # sinon on l'ignore
    if not(estUnMur(cluster, posMurs)):
        posMurs.append(cluster)

print("position des murs à vide", posMurs)

# détection des personnes en continue deux solutions:
# 1 -> à chaque getMesure on update la position (visu en temps réel)
# 2 -> on créer un historique des position trouvées (tracé de trajectoire)

posPers = []
# taille de la fenetre
pygame.init()
win = pygame.display.set_mode((1000, 1000), HWSURFACE | DOUBLEBUF | RESIZABLE)
pygame.display.set_caption("Carte de tracking")
# plan = image de la salle
# bg = pygame.image.load('plan.png')
# bg = pygame.transform.scale(bg, (700, 700))
bg = pygame.image.load('blanc8000.png')
bg = pygame.transform.scale(bg, (1000, 1000))
# pers = icone représentant la position d'une pers 
pers = pygame.image.load('pers.png')
pers = pygame.transform.scale(pers, (30, 30))




run = True
# positionner le lidar sur l'image en fonction de sa localisation dans la plièce
lidarPositionX = 500
lidarPositionY = 500
while run:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    nbValues = 0 # compteur pour visualiser l'avancé
    clusters = []
    clusters = getMesure(2) # on récupère quelques clusters

    #print(clusters)
    listePersonnes = getPersonnes(clusters)
    print(listePersonnes)
    redrawGameWindow(listePersonnes, lidarPositionX, lidarPositionY) 
    listePersonnes.clear()

    time.sleep(0.01)
            
pygame.quit()
