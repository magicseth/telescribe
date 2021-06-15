# # SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# # SPDX-License-Identifier: MIT

# import ipaddress
# import ssl
# import wifi
# import socketpool
# import adafruit_requests


# import time
# import board
# import adafruit_icm20x

# i2c = board.I2C()  # uses board.SCL and board.SDA
# icm = adafruit_icm20x.ICM20948(i2c)


# icm.accelerometer_data_rate_divisor = 0
# i = 0

# while True:
#     #print("Acceleration: X:%.2f, Y: %.2f, Z: %.2f m/s^2" % (icm.acceleration))
#     #print("Gyro X:%.2f, Y: %.2f, Z: %.2f rads/s" % (icm.gyro))
#     #print("Magnetometer X:%.2f, Y: %.2f, Z: %.2f uT" % (icm.magnetic))
#     i += 1

#     if (i % 100000 == 0):
#         print(time.monotonic())
#     print(icm.acceleration)

# #    print("(%.6f, %.6f, %.6f )" % (icm.acceleration))
# #    time.sleep(0.5)


# # URLs to fetch from
# TEXT_URL = "http://wifitest.adafruit.com/testwifi/index.html"
# JSON_QUOTES_URL = "https://www.adafruit.com/api/quotes.php"
# JSON_STARS_URL = "https://api.github.com/repos/adafruit/circuitpython"

# # Get wifi details and more from a secrets.py file
# try:
#     from secrets import secrets
# except ImportError:
#     print("WiFi secrets are kept in secrets.py, please add them there!")
#     raise

# print("ESP32-S2 WebClient Test")

# print("My MAC addr:", [hex(i) for i in wifi.radio.mac_address])

# print("Available WiFi networks:")
# for network in wifi.radio.start_scanning_networks():
#     print("\t%s\t\tRSSI: %d\tChannel: %d" % (str(network.ssid, "utf-8"),
#                                              network.rssi, network.channel))
# wifi.radio.stop_scanning_networks()

# print("Connecting to %s" % secrets["ssid"])
# wifi.radio.connect(secrets["ssid"], secrets["password"])
# print("Connected to %s!" % secrets["ssid"])
# print("My IP address is", wifi.radio.ipv4_address)

# ipv4 = ipaddress.ip_address("8.8.4.4")
# print("Ping google.com: %f ms" % (wifi.radio.ping(ipv4)*1000))

# pool = socketpool.SocketPool(wifi.radio)
# requests = adafruit_requests.Session(pool, ssl.create_default_context())

# print("Fetching text from", TEXT_URL)
# response = requests.get(TEXT_URL)
# print("-" * 40)
# print(response.text)
# print("-" * 40)

# print("Fetching json from", JSON_QUOTES_URL)
# response = requests.get(JSON_QUOTES_URL)
# print("-" * 40)
# print(response.json())
# print("-" * 40)

# print()

# print("Fetching and parsing json from", JSON_STARS_URL)
# response = requests.get(JSON_STARS_URL)
# print("-" * 40)
# print("CircuitPython GitHub Stars", response.json()["stargazers_count"])
# print("-" * 40)

# print("done")
