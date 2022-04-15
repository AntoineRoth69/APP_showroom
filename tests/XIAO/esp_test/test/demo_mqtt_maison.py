import paho.mqtt.client as mqtt


# Successful Connection Callback
def on_connect(client, userdata, flags, rc):
    client.username_pw_set(username="sam",password="app")
    print('Connected with result code '+str(rc))
    client.subscribe('/showroom/PIR')

# Message delivery callback
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()

# Set callback handler
client.on_connect = on_connect
client.on_message = on_message

# Set up connection
client.connect('192.168.1.37', 1883, 60)
# Publish message
client.publish('/showroom/PIR',payload='nice',qos=0)

client.loop_forever()
