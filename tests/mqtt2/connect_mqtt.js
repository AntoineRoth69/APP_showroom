//var
const mqtt = require('mqtt')
const host = '10.100.100.117'
const port = '443'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`
const connectUrl = `mqtt://${host}:${port}`

//connexion
const client = mqtt.connect(connectUrl, {
    clientId,
    clean: true,
    connectTimeout: 4000,
    username: '',
    password: '',
    reconnectPeriod: 1000,
    })


//sub topic
const topic = '/showroom/PIR'
//a la connexion
client.on('connect', () => {
console.log('Connected')
client.subscribe([topic], () => {
console.log(`Subscribe to topic '${topic}'`)
})

//publie un message a la connexion
client.publish(topic, 'nodejs mqtt test', { qos: 0, retain: false }, (error) => {
if (error) {
console.error(error)
}
})

})


//sub topic message recu
client.on('message', (topic, payload) => {
console.log('Received Message:', topic, payload.toString())
})

module.export = client