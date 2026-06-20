#include "esp_camera.h"
#include <WiFi.h>

// ======================================================
// MODELO DE CÁMARA
// Para Seeed Studio XIAO ESP32S3 Sense / Plus con cámara
// ======================================================
#define CAMERA_MODEL_XIAO_ESP32S3

// ======================================================
// DATOS DEL WIFI QUE CREA EL ESP32
// El celular/PC debe conectarse a esta red
// ======================================================
const char* ssid = "FPVCAR_ESP32";
const char* password = "12345678";  // Mínimo 8 caracteres

// ======================================================
// PINES DE LA CÁMARA PARA XIAO ESP32S3 SENSE
// ======================================================
#if defined(CAMERA_MODEL_XIAO_ESP32S3)

#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1

#define XCLK_GPIO_NUM     10
#define SIOD_GPIO_NUM     40
#define SIOC_GPIO_NUM     39

#define Y9_GPIO_NUM       48
#define Y8_GPIO_NUM       11
#define Y7_GPIO_NUM       12
#define Y6_GPIO_NUM       14
#define Y5_GPIO_NUM       16
#define Y4_GPIO_NUM       18
#define Y3_GPIO_NUM       17
#define Y2_GPIO_NUM       15

#define VSYNC_GPIO_NUM    38
#define HREF_GPIO_NUM     47
#define PCLK_GPIO_NUM     13

#define LED_GPIO_NUM      21

#else
#error "Camera model not selected"
#endif

// ======================================================
// PINES DEL CARRO
// En XIAO se pueden usar D1, D2, D3, etc.
// Cambia estos pines si tu puente H está conectado diferente
// ======================================================
int gpLb = 1;   // Motor izquierdo hacia atrás (GPIO1 / D1)
int gpLf = 2;   // Motor izquierdo hacia adelante (GPIO2 / D2)
int gpRb = 3;   // Motor derecho hacia atrás (GPIO3 / D3)
int gpRf = 4;   // Motor derecho hacia adelante (GPIO4 / D4)
int gpLed = 9;  // Luz / LED (GPIO9 / D9)

// Esta variable la usa app_httpd.cpp para formar la URL del stream
String WiFiAddr = "";

// Función que está definida en app_httpd.cpp
void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("Iniciando FPV Car...");

  // ======================================================
  // CONFIGURACIÓN DE PINES DE MOTORES Y LED
  // ======================================================
  pinMode(gpLb, OUTPUT);
  pinMode(gpLf, OUTPUT);
  pinMode(gpRb, OUTPUT);
  pinMode(gpRf, OUTPUT);
  pinMode(gpLed, OUTPUT);

  // Apagar motores y LED al iniciar
  digitalWrite(gpLb, LOW);
  digitalWrite(gpLf, LOW);
  digitalWrite(gpRb, LOW);
  digitalWrite(gpRf, LOW);
  digitalWrite(gpLed, LOW);

  // ======================================================
  // CONFIGURACIÓN DE LA CÁMARA
  // ======================================================
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  // En algunas versiones antiguas se usa pin_sscb_sda / pin_sscb_scl
  // En otras se usa pin_sccb_sda / pin_sccb_scl
  // Si te da error de compilación aquí, te explico abajo cómo cambiarlo.
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Configuración recomendada para ESP32-S3 con PSRAM
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

  // ======================================================
  // RESOLUCIÓN INICIAL
  // Se usa QVGA para probar estabilidad.
  // Luego puedes subir a VGA, SVGA, XGA, etc.
  // ======================================================
  if (psramFound()) {
    Serial.println("PSRAM detectada");
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  } else {
    Serial.println("PSRAM NO detectada");
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 15;
    config.fb_count = 1;
  }

  // ======================================================
  // INICIAR CÁMARA
  // ======================================================
  esp_err_t err = esp_camera_init(&config);

  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    Serial.println("Revisa el flex de la cámara, PSRAM y modelo de placa.");
    return;
  }

  Serial.println("Camara iniciada correctamente");

  // Ajustar tamaño del frame después de iniciar
  sensor_t *s = esp_camera_sensor_get();

  if (s != NULL) {
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

  // ======================================================
  // CREAR WIFI DEL ESP32 EN MODO ACCESS POINT
  // ======================================================
  WiFi.mode(WIFI_AP);

  bool ap_ok = WiFi.softAP(ssid, password, 6, 0, 4);

  if (!ap_ok) {
    Serial.println("ERROR: No se pudo crear el WiFi AP");
    return;
  }

  delay(1000);

  IPAddress IP = WiFi.softAPIP();
  WiFiAddr = IP.toString();

  Serial.print("Red WiFi creada: ");
  Serial.println(ssid);

  Serial.print("Password: ");
  Serial.println(password);

  Serial.print("AP IP address: http://");
  Serial.println(IP);

  // ======================================================
  // INICIAR SERVIDOR WEB Y SERVIDOR DE STREAM
  //
  // IMPORTANTE:
  // NO usar WiFiServer server(81);
  // NO usar server.begin();
  //
  // startCameraServer() ya crea:
  // - Servidor web en puerto 80
  // - Stream de video en puerto 81
  // ======================================================
  startCameraServer();

  Serial.println();
  Serial.println("Servidor listo.");
  Serial.print("Abre en el navegador: http://");
  Serial.println(IP);
  Serial.print("Stream directo: http://");
  Serial.print(IP);
  Serial.println(":81/stream");
}

void loop() {
  // No hace falta poner nada aquí.
  // El servidor web funciona en segundo plano.
  delay(10000);
}
