# Ejercicio 3 - Análisis de Procesos Zombie y Huérfanos

## Instrucciones de ejecución:
1. Compilar: `gcc -o ej3 ej3.c`
2. Ejecutar: `./ej3`
3. En otra terminal: `ps ax -O "%P"` para observar estados
4. Para matar el padre: `kill <PID_PADRE>`

## Respuestas a las preguntas:

### 1. ¿Qué imagina que va a pasar con los procesos hijos que terminaron? ¿Por qué cree que pasa?

**Respuesta**: Los hijos que terminan instantáneamente se convertirán en **procesos zombie** (estado Z).

**Por qué**: Cuando un proceso hijo termina, el SO preserva su información de salida en la tabla de procesos para que el padre pueda leerla con `waitpid()`. Como el padre está en loop infinito y NUNCA llama a `waitpid()`, estos hijos permanecen como zombies indefinidamente.

**Estado esperado**:
```
PID   PPID  STAT  CMD
1234  1233  S     ./ej3         (padre vivo)
1235  1233  Z     [ej3] <defunct> (zombie)
1236  1233  Z     [ej3] <defunct> (zombie)
1237  1233  S     ./ej3         (hijo en loop)
```

### 2. Mate el proceso padre (kill) ¿Qué sucede?

**Respuesta**: Cuando se mata al padre:
- Los **zombies desaparecen** inmediatamente (son recolectados por init)
- El **hijo en loop** continúa ejecutándose pero ahora es **adoptado por init** (PPID cambia a 1)

**Estado después de matar padre**:
```
PID   PPID  STAT  CMD
1237  1     S     ./ej3         (adoptado por init)
```

### 3. ¿Cambió algo para el proceso hijo que estaba en un loop luego de matar al padre?

**Respuesta**: SÍ, cambió:
- Su **PPID cambió de <PID_PADRE> a 1** (adoptado por init)
- Pero **sigue ejecutándose normalmente** su loop infinito
- **No afecta su funcionamiento**, solo cambió quién es su padre

### 4. ¿Qué es el proceso init?

**Respuesta**: 
- **init** es el **primer proceso** que inicia el sistema operativo (PID = 1)
- Es el **ancestro de todos los procesos** del sistema
- En sistemas modernos puede ser `systemd` en lugar de `init` tradicional
- **Función principal**: Adoptar procesos huérfanos y recolectar zombies automáticamente

### 5. ¿Qué pasa en los sistemas POSIX con los procesos huérfanos?

**Respuesta**: En sistemas POSIX:
- Cuando un padre muere, todos sus hijos **automáticamente son adoptados por init** (PID 1)
- **init automáticamente hace wait()** en todos sus hijos adoptivos
- Esto **previene zombies permanentes** en el sistema
- Los huérfanos pueden continuar ejecutándose normalmente bajo su nuevo padre (init)

## Comandos útiles para observar:

```bash
# Ver procesos con información del padre
ps ax -O "%P"

# Ver solo nuestros procesos
ps ax -O "%P" | grep ej3

# Ver estados detallados
ps aux | grep ej3

# Matar el proceso padre
kill <PID_PADRE>
```

## Estados de proceso importantes:
- **S**: Sleeping (dormido, esperando)
- **R**: Running (ejecutándose)
- **Z**: Zombie (terminado pero no recolectado)
- **T**: Stopped (detenido)
