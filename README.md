# Mini Spy Car — XIAO ESP32-S3

> Proyecto de Fundamentos de Mecatrónica · Universidad Americana · 2026

---

## Integrantes

- Ivan Coronado
- Angel Angulo
- Gabriel Davila
- Nicolas Castillo
- Diego Gonzales

---

## Descripción del proyecto

Este proyecto consiste en un carro de control remoto de tamaño reducido, construido con chasis impreso en 3D y controlado de forma inalámbrica mediante el microcontrolador XIAO ESP32-S3. El carro utiliza un driver L298N para controlar dos motores DC y cuenta con un módulo de cámara integrado al ESP32-S3 que permite la transmisión de video en tiempo real al operador, convirtiéndolo en un vehículo tipo FPV (First Person View).

---

## Problema identificado

Los carros de control remoto comerciales con capacidad de transmisión de video son costosos y no permiten modificaciones técnicas. Este proyecto busca construir un vehículo RC de bajo costo con piezas impresas en 3D y componentes electrónicos accesibles, que permita aprender sobre control inalámbrico, manejo de motores DC y transmisión de video en tiempo real, aplicando conocimientos de mecatrónica.

---

## Objetivo general

Diseñar e implementar un carro de control remoto compacto con transmisión de video en tiempo real, usando el microcontrolador XIAO ESP32-S3 como unidad central de control inalámbrico y un driver L298N para el manejo de los motores DC.

---

## Objetivos específicos

- Construir el chasis del carro mediante piezas impresas en 3D con cuatro ruedas y dos motores DC.
- Integrar el driver L298N para controlar la velocidad y dirección del carro mediante señales PWM desde el ESP32-S3.
- Establecer comunicación inalámbrica vía WiFi entre el XIAO ESP32-S3 y el dispositivo de control remoto.
- Conectar el módulo de cámara integrado al XIAO ESP32-S3 para transmitir video en tiempo real al operador.
- Alimentar el sistema de forma autónoma con una batería LiPo de 3.7V – 500 mAh.
- Programar la lógica de control remoto y validar el funcionamiento del carro mediante pruebas físicas.

---

## Componentes utilizados

| Componente                  | Cantidad | Función                                          |
|-----------------------------|:--------:|--------------------------------------------------|
| XIAO ESP32-S3 Sense         | 1        | Microcontrolador principal con WiFi y cámara integrada |
| Batería LiPo 3.7V 500 mAh  | 1        | Fuente de alimentación autónoma del carro        |
| Motor DC 3V 1200 RPM        | 2        | Actuadores de tracción (ruedas)                  |
| Driver L298N (módulo)       | 1        | Control de velocidad y dirección de los motores  |
| Chasis impreso en 3D        | 1        | Estructura, ruedas y soporte de componentes      |
| Cables Dupont               | Varios   | Conexiones entre módulos electrónicos            |

---

## Arquitectura del sistema

```
[Dispositivo de control remoto — Navegador web]
        │  WiFi (Access Point)
        ▼
  XIAO ESP32-S3
   │         │
   │         └──► Módulo Cámara (integrada) ──► Stream de video (puerto 81)
   │
   ▼
Driver L298N
   │         │
   ▼         ▼
Motor DC   Motor DC
Izquierdo  Derecho
      ▲
      │
Batería LiPo 3.7V 500 mAh
```

**Flujo de control:**

`Operador → Navegador web → WiFi → ESP32-S3 → L298N → Motores DC → Movimiento`

`Cámara integrada → ESP32-S3 → WiFi → Navegador (video en vivo)`

---

## Funcionamiento

1. El ESP32-S3 crea una red WiFi propia en modo Access Point con el nombre `FPVCAR_ESP32`.
2. El operador conecta su celular o PC a esa red e ingresa a `http://192.168.4.1` en el navegador.
3. Desde la interfaz web se visualiza el video en vivo de la cámara y se envían comandos de movimiento.
4. El ESP32-S3 recibe los comandos y los traduce en señales PWM hacia el driver L298N.
5. El L298N controla la velocidad y dirección de cada motor DC de forma independiente.
6. El movimiento se logra mediante tracción diferencial: variando la velocidad relativa de cada motor.

---

## Esquema de conexiones

> El diagrama de conexiones se encuentra en la carpeta `esquemas/`.

```
esquemas/
└── diagrama_conexion.png
```

**Descripción de conexiones principales:**

| Pin XIAO ESP32-S3 | Destino L298N | Descripción                        |
|:-----------------:|:-------------:|------------------------------------|
| D1 (GPIO2)        | IN1           | Motor izquierdo — hacia adelante   |
| D2 (GPIO3)        | IN2           | Motor izquierdo — hacia atrás      |
| D3 (GPIO4)        | IN3           | Motor derecho — hacia adelante     |
| D4 (GPIO5)        | IN4           | Motor derecho — hacia atrás        |
| D9 (GPIO9)        | —             | LED de iluminación frontal         |
| ENA / ENB         | Jumper cerrado | Velocidad controlada vía PWM en IN |
| BAT+              | L298N VCC     | Alimentación de potencia           |
| 3.3V              | VCC lógico    | Alimentación lógica del ESP32-S3   |
| CAM (integrada)   | —             | Interfaz de cámara interna del S3  |

> **Nota:** Los pines ENA y ENB del L298N están con el jumper cerrado. La velocidad se controla enviando PWM directamente a los pines IN mediante `analogWrite()`, sin necesidad de pines de habilitación separados.

---

## Código fuente

El código fuente se encuentra en la carpeta `codigo/programa_principal/` y está compuesto por tres archivos:

| Archivo                  | Descripción                                                  |
|--------------------------|--------------------------------------------------------------|
| `FPVCar.ino`             | Archivo principal: configuración de cámara, WiFi AP y motores |
| `app_httpd.cpp`          | Servidor web, rutas HTTP y lógica de control de motores      |
| `camera_index.h`         | Interfaz web embebida (HTML/JS servida desde el ESP32)       |

[Ver código fuente](codigo/programa_principal/)

---

## Evidencias del proceso

### Ensamble del carro

Vista general del carro ensamblado sobre el banco de trabajo, con el chasis impreso en 3D, los motores, el driver L298N y el módulo ESP32-S3 con cámara integrada.

![Carro ensamblado en banco de trabajo](evidencias/avances/Spy_Car_Soldado.jpg)

---

### Integración y pruebas eléctricas

Integrante del equipo realizando pruebas de continuidad y verificación de conexiones con multímetro directamente sobre el carro ensamblado.

![Pruebas eléctricas con multímetro](docs/avances/Soldando_Spy_Car.jpg)

---

### Sesión de trabajo en equipo

Integrantes del equipo trabajando en la integración del sistema y revisión del código de control.

![Equipo trabajando en el proyecto](docs/avances/Trabajando_Spy_Car.jpg)

---

## Video de funcionamiento

[Ver video de funcionamiento del Mini Spy Car](docs/pruebas/Mini_Spy_Car_Funcionamiento.mp4)

---

## Pruebas realizadas

| Prueba                  | Descripción                                                   | Resultado         |
|-------------------------|---------------------------------------------------------------|-------------------|
| Montaje del chasis      | Ensamble de ruedas, motores y electrónica en estructura 3D   | ✅ Completado     |
| Conexiones eléctricas   | Verificación de continuidad con multímetro                    | ✅ Completado     |
| Instalación batería     | Montaje y conexión de batería LiPo al sistema                 | ✅ Completado     |
| Integración de cámara   | Conexión y configuración del módulo de cámara del ESP32-S3   | ✅ Completado     |
| Control remoto WiFi     | Validación del control inalámbrico desde el navegador         | ✅ Completado     |
| Transmisión de video    | Verificación del stream de cámara en tiempo real              | ✅ Completado     |
| Prueba de movimiento    | Prueba completa de desplazamiento por control remoto          | 🔄 En ajuste      |

---

## Estado actual del proyecto

**En fase de ajuste final.**

El carro se encuentra ensamblado y operativo. La transmisión de video en tiempo real y el control remoto vía WiFi funcionan correctamente desde el navegador. Actualmente se está ajustando la lógica de control de los motores en el código, ya que al operar desde la interfaz web algunos comandos de dirección aparecen invertidos respecto al movimiento esperado.

---

## Dificultades encontradas

- El tamaño reducido del chasis dificultó el ruteo del cableado y la disposición de los componentes; se optimizó la distribución para evitar cortocircuitos.
- La verificación de conexiones en un espacio tan compacto requirió el uso de multímetro con puntas finas para confirmar continuidad.
- Al probar el control desde la interfaz web, se detectó que algunos comandos de movimiento de los motores aparecen invertidos, lo que se atribuye a un error en la lógica del código y se encuentra en proceso de corrección.

---

## Mejoras futuras

- Corregir y calibrar definitivamente la lógica de dirección de los motores en el código.
- Desarrollar una interfaz web mejorada con joystick virtual y visualización del nivel de batería.
- Implementar transmisión de video de mayor resolución y menor latencia.
- Integrar sensores ultrasónicos para detección de obstáculos y modo de conducción autónomo.
- Diseñar una versión mejorada del chasis con mejor distribución de peso y más espacio para componentes.

---

## Conclusiones

Este proyecto demostró que es posible construir un vehículo de control remoto tipo FPV con transmisión de video en tiempo real utilizando componentes de bajo costo y un chasis impreso en 3D, integrando de forma práctica conocimientos de mecatrónica, electrónica y programación embebida. El uso del XIAO ESP32-S3 resultó adecuado para centralizar el control inalámbrico vía WiFi y gestionar la cámara en una plataforma compacta.

El proceso de ensamble evidenció la importancia de planificar el espacio físico dentro del chasis y verificar cada conexión antes de energizar el sistema. Las dificultades encontradas, como el cableado en espacio reducido y el ajuste de la lógica de control, reforzaron habilidades prácticas del equipo y la capacidad de resolución de problemas en entornos reales.

Si bien la dirección de los motores requiere un ajuste final en el código, el sistema funciona en su conjunto: la conexión WiFi, la transmisión de video y el control remoto desde el navegador operan correctamente. Las mejoras futuras identificadas representan una línea clara de desarrollo para extender las capacidades del vehículo más allá del alcance académico inicial.

---

## Estructura del repositorio

```
README.md
Mini-Spy-Car/
│
├── docs/
│   ├── avances/
│   └── pruebas/
│
├── codigo/
│   └── programa_principal/
│       ├── FPVCar.ino
│       ├── app_httpd.cpp
│       └── camera_index.h
│
├── esquemas/
    └── diagrama_conexion.png

```

---

*Proyecto de Fundamentos de Mecatrónica · Universidad Americana · 2026*
