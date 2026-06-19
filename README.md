# Mini-Spy-Car

# Carro Control Remoto con Cámara — XIAO ESP32-S3

> Proyecto de Mecatrónica · Universidad Americana · 2026

---

## Integrantes

- Ivan Coronado
- Angel Angulo
- Gabriel Davila
- Nicolas Castillo
- Diego Gonzales

---

## Descripción del proyecto

Este proyecto consiste en un carro de control remoto de tamaño reducido, construido con chasis impreso en 3D, controlado de forma inalámbrica mediante el microcontrolador XIAO ESP32-S3 (WiFi integrado). El carro utiliza un driver L298N para controlar dos motores DC de 3V a 1200 RPM, es alimentado por una batería LiPo de 3.7V – 500 mAh y cuenta con un módulo de cámara que permite la transmisión de video en tiempo real al operador remoto.

---

## Problema identificado

Los carros de control remoto comerciales con capacidad de transmisión de video son costosos y no permiten modificaciones técnicas. Este proyecto busca construir un vehículo RC de bajo costo con piezas impresas en 3D y componentes electrónicos accesibles, que permita aprender sobre control inalámbrico, manejo de motores DC y transmisión de video en tiempo real, aplicando conocimientos de mecatrónica.

---

## Objetivo general

Diseñar e implementar un carro de control remoto compacto con transmisión de video en tiempo real, usando el microcontrolador XIAO ESP32-S3 como unidad central de control inalámbrico y un driver L298N para el manejo diferencial de los motores DC.

---

## Objetivos específicos

- Construir el chasis del carro mediante piezas impresas en 3D con cuatro ruedas y dos motores DC.
- Integrar el driver L298N para controlar la velocidad y dirección del carro mediante señales PWM desde el ESP32-S3.
- Establecer comunicación inalámbrica vía WiFi entre el XIAO ESP32-S3 y el dispositivo de control remoto.
- Conectar el módulo de cámara al XIAO ESP32-S3 para transmitir video en tiempo real al operador.
- Alimentar el sistema de forma autónoma con una batería LiPo de 3.7V – 500 mAh.
- Programar la lógica de control remoto y validar el funcionamiento del carro mediante pruebas físicas.

---

## Componentes utilizados

| Componente                | Cantidad | Función                                          |
|---------------------------|:--------:|--------------------------------------------------|
| XIAO ESP32-S3             | 1        | Microcontrolador principal con WiFi y cámara     |
| Batería LiPo 3.7V 500 mAh | 1        | Fuente de alimentación autónoma del carro        |
| Motor DC 3V 1200 RPM      | 2        | Actuadores de tracción (ruedas)                  |
| Driver L298N PWM          | 1        | Control de velocidad y dirección de los motores  |
| Módulo de cámara OV       | 1        | Transmisión de video en tiempo real              |
| Chasis impreso en 3D      | 1        | Estructura, ruedas y soporte de componentes      |
| Cables Dupont             | Varios   | Conexiones entre módulos electrónicos            |
| Cinta aislante            | 1        | Aislamiento y fijación de conexiones             |

---

## Arquitectura del sistema

```
[Dispositivo de control remoto]
        │  WiFi
        ▼
  XIAO ESP32-S3
   │         │
   │         └──► Módulo Cámara OV ──► (stream de video)
   │
   ▼
Driver L298N
   │         │
   ▼         ▼
Motor DC   Motor DC
Izquierdo  Derecho
   │         │
   ▼         ▼
 Rueda     Rueda
   ▲
   │
Batería LiPo 3.7V 500 mAh
```

**Flujo de control:**

`Operador → WiFi → ESP32-S3 → L298N → Motores DC → Movimiento del carro`

`Cámara OV → ESP32-S3 → WiFi → Operador (video en vivo)`

---

## Código fuente

>  **El código del proyecto será publicado aquí próximamente.**

```cpp
// =========================================================
//   CARRO CONTROL REMOTO — XIAO ESP32-S3
//   Archivo: programa_principal.ino
//   Descripción: Aquí va el código del proyecto
//   - Control de motores vía L298N con PWM
//   - Servidor WiFi para control remoto
//   - Transmisión de video con módulo de cámara OV
// =========================================================

// TODO: Pongan aquí el código del proyecto o lo pueden subir por aparte para que no quede tan largo el README
```

---

## Pruebas realizadas

| Prueba | Descripción | Resultado |
|--------|-------------|-----------|
| Soldadura de motores | Soldadura de cables de motor DC al driver L298N bajo lupa | ✅ Completado |
| Montaje del chasis | Ensamble de ruedas, motores y electrónica en estructura 3D | ✅ Completado |
| Instalación batería | Montaje y conexión de batería LiPo al sistema | ✅ Completado |
| Integración de cámara | Conexión del módulo de cámara al XIAO ESP32-S3 | 🔄 En progreso |
| Control remoto WiFi | Validación del control inalámbrico del carro | ⏳ Pendiente |
| Transmisión de video | Verificación del stream de cámara en tiempo real | ⏳ Pendiente |
| Prueba de movimiento | Prueba completa de desplazamiento por control remoto | ⏳ Pendiente |

---

## Estado actual del proyecto

 **En fase de ensamble e integración.**

El chasis y las ruedas ya están impresos e instalados. El driver L298N y la batería LiPo están montados y cableados. Las soldaduras de los motores han sido completadas exitosamente. Actualmente se trabaja en la integración del módulo de cámara y en el desarrollo del código de control remoto vía WiFi.

---

## Dificultades encontradas

- El tamaño reducido del carro dificultó la soldadura de los cables de motor; se resolvió usando una estación de soldadura con soporte de tercera mano y lupa de aumento.
- El espacio disponible en el chasis limita la disposición de los componentes electrónicos; se optimizó el ruteo del cableado para evitar cortocircuitos.

---

## Mejoras futuras

- Desarrollar una interfaz web o app móvil para el control remoto con joystick virtual.
- Implementar transmisión de video de mayor resolución y menor latencia.
- Integrar sensores ultrasónicos para detección de obstáculos y modo autónomo.
- Diseñar una versión mejorada del chasis con mejor distribución de peso y mayor espacio para componentes.
- Agregar un indicador de nivel de batería en tiempo real en la interfaz de control.

---

## Conclusiones

Este proyecto demostró que es posible construir un carro de control remoto con transmisión de video en tiempo real utilizando componentes de bajo costo y piezas impresas en 3D, aplicando de forma integrada conocimientos de mecatrónica, electrónica y programación embebida. El uso del microcontrolador XIAO ESP32-S3 resultó adecuado para centralizar el control inalámbrico vía WiFi y la gestión del módulo de cámara OV en una plataforma compacta.
El proceso de ensamble evidenció la importancia de la planificación del espacio físico dentro del chasis, así como de la precisión en las conexiones eléctricas, especialmente en componentes de tamaño reducido. Las dificultades encontradas durante la soldadura y el ruteo del cableado fueron resueltas con herramientas adecuadas y reforzaron habilidades prácticas del equipo.
Si bien algunas etapas del proyecto como la transmisión de video y el control remoto vía WiFi se encuentran aún en validación, la base mecánica y electrónica del sistema ha sido construida y verificada satisfactoriamente. Las mejoras futuras identificadas, como la integración de sensores de obstáculos y una interfaz de control más intuitiva, representan una línea de desarrollo clara para extender las capacidades del vehículo más allá del alcance académico inicial.

---

## Estructura del repositorio

```
carro-control-remoto-esp32s3/
│
├── README.md
├── docs/
│   ├── imagenes/
    └── videos/
│
├── codigo/
│   └── programa_principal/
│
├── esquemas/
│   └── diagrama_conexion.png
│
└── evidencias/
    ├── pruebas/
    └── avances/
```

---

*Proyecto de Mecatrónica · 2026*
