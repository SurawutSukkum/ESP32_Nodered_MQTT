# ESP32_Nodered_MQTT

ESP32 send data to noedred via MQTT

Install Nodered

$ sudo apt-get updat

$ wget https://nodejs.org/dist/v12.13.0/node-v12.13.0-linux-arm64.tar.xz

$ tar -xJf node-v18.2.0-linux-x64.tar.xz

$ cd node-v12.13.0-linux-arm64

$ sudo cp -R * /usr/local/

$ node -v

$ sudo apt-get install npm

$ sudo npm install -g --unsafe-perm node-red 

$ npm -v

Install MQTT

$ sudo apt-get updat

$ sudo apt-get install mosquitt

$ sudo apt-get install mosquitto-clients

$ pip install paho-mqtt

Test command 

$ mosquitto_sub -h 127.0.0.1 -t test

$ mosquitto_pub -h 127.0.0.1 -t test -m "hello"

 
