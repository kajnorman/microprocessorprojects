import paho.mqtt.client as mqtt
# Module Import
import mariadb
import sys

# Instantiate Connection
try:
   conn = mariadb.connect(
      user="connpy_meassurement",
      password="passwd",
      host="localhost",
      port=3306,
      database = "measurement",
      autocommit = True)
except mariadb.Error as e:
   print(f"Error connecting to MariaDB Platform: {e}")
   sys.exit(1)

cur = conn.cursor()

def add_measurement_to_database(cur, t,p):
   cur.execute("INSERT INTO measurement.temperature(temperature,position) "
               "VALUES (?, ?)",(t,p))

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("trek/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    if (msg.topic.find('cat') == -1):  #no cat found just insert
        add_measurement_to_database(cur, float(msg.payload), msg.topic )
    else:
        print("the cat is around")
        cur.execute("INSERT INTO measurement.catposition(tag,gps) "
               "VALUES (?, ?)",(msg.payload,msg.topic))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("test.mosquitto.org", 1883, 60)
client.loop_forever()
