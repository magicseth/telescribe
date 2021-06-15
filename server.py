from flask import Flask, request, send_from_directory
import serial

import glob

app = Flask(__name__)


@app.route("/")
def hello_world():
    return send_from_directory('', 'index.html')


@app.route('/large.csv')
def generate_large_csv():
    def generate():
        i = 0
        while(i < 1000):
            i += 1

            usbname = glob.glob("/dev/tty.usbmodem*")[0]

            with serial.Serial(usbname, 230400, timeout=1) as ser:
                print(ser.name)
                while (True):
                    line = ser.readline()   # read a '\n' terminated line
                    if (len(line) > 3):
                        yield line
    return app.response_class(generate(), mimetype='text/csv')


@app.route('/js/<path:path>')
def send_js(path):
    return send_from_directory('js', path)


if __name__ == "__main__":
    app.run()
