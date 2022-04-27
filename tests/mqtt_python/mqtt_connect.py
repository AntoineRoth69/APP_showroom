#install mqtt packages
#pip install paho.mqtt

from email import message
from operator import indexOf
import paho.mqtt.client as mqtt
import json

# Successful Connection Callback
def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe('/showroom/PIR')

# add new values to a list, delete old ones if too many values
def append_limit(value, list):
    nb_valeur=15
    if(len(list)>=nb_valeur):
        del list[0]
    list.append(value)

# moyennes des capteurs en paramètres 
# Capteurs : PIR1, PIR2, PIR3, PIR4, PIR5, PIR6, PIR7, PIR8, PIR9
def moys(list, capteurs = []):
    sums = {}
    for capteur in list:
        (capt_test, v) = capteur[0]
        if capt_test not in capteurs:
            continue
        sum = 0
        name = ''
        for k in capteur:
            (capt, val) = k
            name = capt
            sum+=val
        sums[name] = sum/len(capteur)
    return sums

capteurs_datas = []
# Message delivery callback
def on_message(client, userdata, msg):
    nb_capteurs=10
    message_json = json.loads(msg.payload.decode("utf-8"))
    for capteur in message_json:
        if(len(capteurs_datas)<nb_capteurs):
            capteurs_datas.append([])
        datas = capteurs_datas[message_json.index(capteur)]
        for value in capteur.items():
            append_limit(value, datas)
    # print(msg.topic+" "+str(msg.payload))
    print(moys(capteurs_datas, ['PIR0','PIR1', 'PIR2', 'PIR3', 'PIR4', 'PIR5','PIR6','PIR7','PIR8','PIR9']))
    

client = mqtt.Client()

# Set callback handler
client.on_connect = on_connect
client.on_message = on_message

# Set up connection
client.connect('10.100.100.117', 443, 60)
# Publish message
client.publish('/showroom/PIR',payload='SUR',qos=0)

client.loop_forever()
