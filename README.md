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

