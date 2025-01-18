import paho.mqtt.client as mqtt
from fastapi import FastAPI, HTTPException
from flask import Flask, cli, jsonify
from flask_cors import CORS
import time
import uvicorn 
import threading
from datetime import datetime
import json
import threading


app = Flask(__name__)
CORS(app)  # This will allow your React app to connect to this Flask API

# MQTT broker details
broker = "broker.hivemq.com"

port = 1883
publish_topic = "python/testTar"
subscribe_topic = "test/topicTar"
subscribe_topic_temp = "test/topicTar/temp"
subscribe_topic_humi = "test/topicTar/humi"
temp = 0 
humi = 0
    
@app.route('/humi', methods=['GET'])
def get_data_humi():
    # Simulate a data response
    return jsonify({"humi": str(humi)})

@app.route('/temp', methods=['GET'])
def get_data_temp():
    # Simulate a data response
    return jsonify({"temp":str(temp)})
  
# Callback when a message is received
def on_message(client, userdata, msg):
    global temp
    global humi
    print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")
    if(msg.topic == subscribe_topic_temp):
       temp = msg.payload.decode()
    if(msg.topic == subscribe_topic_humi):
       humi = msg.payload.decode()
# Callback when connected to the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe(subscribe_topic)
        client.subscribe(subscribe_topic_temp)
        client.subscribe(subscribe_topic_humi)
    else:
        print(f"Connection failed with code {rc}")
def mqtt_thread():
    # Create MQTT client
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to broker
    print("Connecting to broker...")
    client.connect(broker, port)
    client.loop_forever()

mqtt_thread = threading.Thread(target=mqtt_thread)
mqtt_thread.start()
if __name__ == "__main__":
    app.run(host='127.0.0.1', port=3001)

