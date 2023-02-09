# ShakeCpp
## A C++ web program using a microservice to search for wods in shakespeare
## Uses cpp-httplib for the microservice
 - ```https://github.com/yhirose/cpp-httplib```
 
## Install SSL and compression services
 - ```sudo apt-get install libz-dev```
 - ```sudo apt-get install libssl-dev```
 
## Set Javascript IP address to your VM address
 - Edit ```shake.js``` so that ```baseUrl``` is your VM's IP address

## Set up App
 - ```sudo mkdir /var/www/html/shakeCpp/```
 - ```sudo chown ubuntu /var/www/html/shakeCpp/```

## Make and run
 - ```make```
 - ```./shakeAPI```

## Go to your VM URL/shakeCpp/shake.html

