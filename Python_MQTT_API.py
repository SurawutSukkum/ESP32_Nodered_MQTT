import paho.mqtt.client as mqtt
from fastapi import FastAPI
from flask import Flask, jsonify
from flask_cors import CORS
import time
import uvicorn 
import threading
from datetime import datetime
import json

app = Flask(__name__)
CORS(app)  # This will allow your React app to connect to this Flask API

# MQTT broker details
broker = "broker.hivemq.com"

port = 1883
publish_topic = "python/testTar"
subscribe_topic = "test/topicTar"

temp = 0 

@app.route('/temp', methods=['GET'])
def get_data():
    # Simulate a data response
    return jsonify({"message": "temp"+str(temp)})
  
# Callback when a message is received
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")

# Callback when connected to the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe(subscribe_topic)
    else:
        print(f"Connection failed with code {rc}")

# Create MQTT client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Connect to broker
print("Connecting to broker...")
client.connect(broker, port)

# Publish a message periodically
import time
if __name__ == "__main__":
    app.run(host='127.0.0.1', port=3001)
    try:
        while True:
            message = "Hello from Python!"
            client.publish(publish_topic, message)
            print(f"Message published: {message}")
            time.sleep(5)
            client.loop(0.1)  # Handle incoming messages
    except KeyboardInterrupt:
        print("Disconnecting...")
        client.disconnect()
