#include "Arduino-ICM20948.h"
#include <Wire.h>
#include <WiFi.h>

#include "esp_http_server.h"
const char* ssid = "Wiphael";
const char* password = "sethlovesme";


ArduinoICM20948 icm20948;
ArduinoICM20948Settings icmSettings =
{
  .i2c_speed = 400000,                // i2c clock speed
  .is_SPI = false,                    // Enable SPI, if disable use i2c
  .cs_pin = 10,                       // SPI chip select pin
  .spi_speed = 7000000,               // SPI clock speed in Hz, max speed is 7MHz
  .mode = 1,                          // 0 = low power mode, 1 = high performance mode
  .enable_gyroscope = true,           // Enables gyroscope output
  .enable_accelerometer = true,       // Enables accelerometer output
  .enable_magnetometer = true,        // Enables magnetometer output // Enables quaternion output
  .enable_gravity = true,             // Enables gravity vector output
  .enable_linearAcceleration = true,  // Enables linear acceleration output
  .enable_quaternion6 = false,         // Enables quaternion 6DOF output
  .enable_quaternion9 = true,         // Enables quaternion 9DOF output
  .enable_har = false,                 // Enables activity recognition
  .enable_steps = false,               // Enables step counter
  .gyroscope_frequency = 225,           // Max frequency = 225, min frequency = 1
  .accelerometer_frequency = 225,       // Max frequency = 225, min frequency = 1
  .magnetometer_frequency = 70,        // Max frequency = 70, min frequency = 1 
  .gravity_frequency = 225,             // Max frequency = 225, min frequency = 1
  .linearAcceleration_frequency = 225,  // Max frequency = 225, min frequency = 1
  .quaternion6_frequency = 225,        // Max frequency = 225, min frequency = 50
  .quaternion9_frequency = 255,        // Max frequency = 225, min frequency = 50
  .har_frequency = 50,                // Max frequency = 225, min frequency = 50
  .steps_frequency = 50               // Max frequency = 225, min frequency = 50
  
};

const uint8_t number_i2c_addr = 2;
uint8_t poss_addresses[number_i2c_addr] = {0X69, 0X68};
uint8_t ICM_address;
bool ICM_found = false;


void i2c_scan(){
    uint8_t error;
    for(uint8_t add_int = 0; add_int < number_i2c_addr; add_int++ ){
        Serial.printf("Scanning 0x%02X for slave...", poss_addresses[add_int]);
        Wire.beginTransmission(poss_addresses[add_int]);
        error = Wire.endTransmission();
        if (error == 0){
            Serial.println("found.");
            if(poss_addresses[add_int] == 0x69 || poss_addresses[add_int] == 0x68){
                Serial.println("\t- address is ICM.");
                ICM_address = poss_addresses[add_int];
                ICM_found = true;
            }
        }
    }
}
void run_icm20948_quat6_controller(bool inEuler = false)
{
    float quat_w, quat_x, quat_y, quat_z;
    float roll, pitch, yaw;
    char sensor_string_buff[128];
    if (inEuler)
    {
        if (icm20948.euler6DataIsReady())
        {
            icm20948.readEuler6Data(&roll, &pitch, &yaw);
            sprintf(sensor_string_buff, "Euler6 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
            Serial.println(sensor_string_buff);
        }
    }
    else
    {
        if (icm20948.quat6DataIsReady())
        {
            icm20948.readQuat6Data(&quat_w, &quat_x, &quat_y, &quat_z);
            sprintf(sensor_string_buff, "Quat6 w, x, y, z (deg): [%f,%f,%f,%f]", quat_w, quat_x, quat_y, quat_z);
            Serial.println(sensor_string_buff);
        }
    }
    
}
void run_icm20948_quat9_controller(bool inEuler = false)
{
    float quat_w, quat_x, quat_y, quat_z;
    float roll, pitch, yaw;
    char sensor_string_buff[128];
    if (inEuler)
    {
        if (icm20948.euler9DataIsReady())
        {
            icm20948.readEuler9Data(&roll, &pitch, &yaw);
            sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
            Serial.println(sensor_string_buff);
        }
    }
    else
    {
        if (icm20948.quat9DataIsReady())
        {
            icm20948.readQuat9Data(&quat_w, &quat_x, &quat_y, &quat_z);
            sprintf(sensor_string_buff, "qW:%f,qX:%f,qY:%f,qZ:%f", quat_w, quat_x, quat_y, quat_z);
            printOrChunk(sensor_string_buff);
        }
    }
    
}
void run_icm20948_accel_controller()
{
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.accelDataIsReady())
    {
        icm20948.readAccelData(&x, &y, &z);
        sprintf(sensor_string_buff, "AccX:%f, AccY:%f,AccZ:%f", x, y, z);
        printOrChunk(sensor_string_buff);
    }
    
}
void run_icm20948_gyro_controller()
{
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.gyroDataIsReady())
    {
        icm20948.readGyroData(&x, &y, &z);
        sprintf(sensor_string_buff, "gyrX:%f,gyrY:%f,gyrZ:%f", x, y, z);
        printOrChunk(sensor_string_buff);
    }
    
}
void run_icm20948_mag_controller()
{
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.magDataIsReady())
    {
        icm20948.readMagData(&x, &y, &z);
        sprintf(sensor_string_buff, "Magnetometer x, y, z (mT): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }
    
}
void run_icm20948_linearAccel_controller()
{
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.linearAccelDataIsReady())
    {
        icm20948.readLinearAccelData(&x, &y, &z);
        sprintf(sensor_string_buff, "linX:%f, linY:%f ,linZ:%f", x, y, z);
        printOrChunk(sensor_string_buff);
    }
    
}
void run_icm20948_grav_controller()
{
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.gravDataIsReady())
    {
        icm20948.readGravData(&x, &y, &z);
        sprintf(sensor_string_buff, "Gravity Vector x, y, z (g): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }
    
}
void run_icm20948_har_controller()
{
    char activity;
    char sensor_string_buff[128];
    if (icm20948.harDataIsReady())
    {
        icm20948.readHarData(&activity);
        sprintf(sensor_string_buff, "Current Activity : %c", activity);
        Serial.println(sensor_string_buff);
    }
    
}
void run_icm20948_steps_controller()
{
    unsigned long steps;
    char sensor_string_buff[128];
    if (icm20948.stepsDataIsReady())
    {
        icm20948.readStepsData(&steps);
        sprintf(sensor_string_buff, "Steps Completed : %lu", steps);
        Serial.println(sensor_string_buff);
    }
    
}










////////////////////////////////////////


static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace";
void closedsocket(void *ctx) {
  Serial.println("closed");
}
static httpd_req_t *staticReq ;
httpd_handle_t stream_httpd = NULL;
static esp_err_t stream_handler(httpd_req_t *req){
  staticReq = req;
  char * part_buf[64];

  esp_err_t res = ESP_OK;

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);

  res = httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  res = httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "*");
  res = httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "*");

  if(res != ESP_OK){
    return res;
  }

int thing;
req->free_ctx = closedsocket;
req->sess_ctx = &thing;
  while(true){

    size_t recv_size = 1;
    char content[2];

//int httpd_socket_recv(req.handle, int sockfd, content, 1, int flags)
//
//    int ret = httpd_socket_recv(req, content, recv_size);
////          Serial.print(ret);
//
//    if (ret < 0) {  /* 0 return value indicates connection closed */
//      Serial.print("error on connection");
//        /* Check if timeout occurred */
//        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
//            /* In case of timeout one can choose to retry calling
//             * httpd_req_recv(), but to keep it simple, here we
//             * respond with an HTTP 408 (Request Timeout) error */
//            httpd_resp_send_408(req);
//        }
//        /* In case of error, returning ESP_FAIL will
//         * ensure that the underlying socket is closed */
//        return ESP_FAIL;
//    }

        icm20948.task();
    int myTime = millis();
  printOrChunk("(");
  printOrChunk("millis:");
  printOrChunk(myTime);


        printOrChunk(",");
    run_icm20948_linearAccel_controller();
        printOrChunk(",");
    run_icm20948_gyro_controller();
    printOrChunk(",");
    run_icm20948_quat9_controller(false);


   printOrChunk(",");
  run_icm20948_accel_controller();

    printOrChunk(")");
    int failed = printOrChunk("\n");
    if (failed) {
      return ESP_FAIL;
    }
    
    //run_icm20948_har_controller();
    //run_icm20948_steps_controller();

//      res = httpd_resp_send_chunk(req, "HELLO WORLD", 7);
    }
  
  return res;
}
void printOrChunk(int number) {


char cstr[16];
itoa(number, cstr, 10);

printOrChunk(cstr);
}

void printOrChunk(float number) {
  char result[10]; // Buffer big enough for 7-character float
dtostrf(number, 6, 8, result); // Leave room for too large numbers!

  printOrChunk(result);
}

int printOrChunk(const char * thestring) {
//Serial.print(thestring);
int res = httpd_resp_send_chunk(staticReq, thestring, strlen(thestring));
//Serial.println(res);
return res;

}

void printOrChunk(String thestring) {

printOrChunk(thestring.c_str());

}



void startServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };
  
  //Serial.printf("Starting web server on port: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
  }
}




void setup() 
{
  Serial.begin(230400);

  Wire.begin();
  Wire.setClock(400000);
  Serial.println("Starting ICM");
  delay(10);
  i2c_scan();
  if (ICM_found)
  {
      icm20948.init(icmSettings);
  }



  // Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  Serial.print("Camera Stream Ready! Go to: http://");
  Serial.print(WiFi.localIP());

  startServer();
}





void loop() 
{
  if (ICM_found)
  {
//    icm20948.task();
//    unsigned long myTime = millis();
//  Serial.print("(");
//  Serial.print("millis:");
//  Serial.print(myTime);
//
//
//        Serial.print(",");
//    run_icm20948_linearAccel_controller();
//        Serial.print(",");
//    run_icm20948_gyro_controller();
//    Serial.print(",");
//    run_icm20948_quat9_controller(false);
//
//
//   Serial.print(",");
//  run_icm20948_accel_controller();
//
//    Serial.println(")");
//    //run_icm20948_har_controller();
//    //run_icm20948_steps_controller();
  }

}
