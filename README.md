# arduino_esp8266_notification_notify
The LED flusher as notification for smartphone notifications

## overview
    +-----------------+       +----------------+     +--------------------+
    | arduino/esp8266 |       | PHP/web server |     | android/smartphone |
    +--------+--------+       +--------+-------+     +----------+---------+
             |                         |                        |                --+
             +--------[HTTP GET]------>|                        :                  |
             |                         |                        :                  |
             |<-----[HTTP payload]-----+                        :                  |
             |                         |                        :                  |
        (time wait)                    :                        :                  | HTTP POLLING from arduino
             |                         |                        :                  |
             +--------[HTTP GET]------>|                        :                  |
             |                         |                        :                  |
             |<-----[HTTP payload]-----+                        :                  |
             |                         |                        :                  |
        (time wait)                    :                        :                --+
             :                         :                        :
             :                         :                        :
             :                         |                        |                --+
             :                         |<--[HTTP(set1 status)]--+                  | status update from smartphone
             :                         |                        |                --+
             :                         :                        :
             :                         :                        :
             +--------[HTTP GET]------>|                        :                --+
             |                         |                        :                  | arduino get the updated status
             |<-----[HTTP payload]-----+                        :                --+
             :                         :                        :
             :                         :                        :
             :                         |                        |
             :                         |<--[HTTP(set0 status)]--+
             :                         |                        |
             :                         :                        :
             :                         :                        :
             +--------[HTTP GET]------>|                        :
             |                         |                        :
             |<-----[HTTP payload]-----+                        :
             :                         :                        :
             :                         :                        :

## hardware
* ESP8266
* android smartphone
* php/web server

## software
* Arduino IDE
* ESP8266 core for Arduino
* Android OS
* MacroDroid
* php/web server

## how it work
1. polling from arduino to web server
1. if there is any notifications, the android will access to web server (MacroDroid useful)
1. arduino flashing the LED
1. polling from arduino to web server
1. if there is NOT notification, the android will access to web server (MacroDroid useful)
1. arduino stop the LED flash

## why not use the Bluetooth?
If it's easy to use, I'd love to use it too.
I wish the Android OS provided a way to get notifications from Bluetooth. :)
