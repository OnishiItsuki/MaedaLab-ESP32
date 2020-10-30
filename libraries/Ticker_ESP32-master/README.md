# Ticker_ESP32
A primitive library which makes use of the hardware timers in ESP32, to provide similar funtionality and interface akin to the "Ticker.h" library for ESP8266.

# Differences to "Ticker.h" for ESP8266
* Each Ticker instance must be provided with the id of the respective hw timer which should be employed. Valid ids can be in the range 0-3. (e.g. ```Ticker LED_Ticker_1(2);```)
* ESP32 has 4 hw timers, which means up to 4 Ticker instances can be instantiated, one for each timer.
* Unlike "Ticker.h", callback functions with arguments are not supported (yet).

# Usage
* Define a Ticker instance (e.g. on 4th hw timer):

```c++
Ticker myTicker(3);
```

* Define a callback function to be called when timer fires:

```c++
void myCallback(){
  // Do something interesting...
}
```

* Initiate the timer and attach our callback to be run at a certain interval (e.g. 1 sec):

```c++
myTicker.attach(1, myCallback); 

or

myTicker.attach_us(1000000, myCallback); // 1 second = 1000000 microseconds

```

* When desired, stop the timer and detach the callback:
```
myTicker.detach();
```

See the blinkLEDs sketch, for a full example.
