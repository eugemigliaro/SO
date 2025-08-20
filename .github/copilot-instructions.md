# Instrucciones para GitHub Copilot

## Estilo de código
- Genera código limpio y conciso sin comentarios excesivos
- Solo incluye comentarios cuando sean estrictamente necesarios para explicar lógica compleja
- Evita comentarios obvios que describan lo que hace el código
- Prefiere código autodocumentado con nombres de variables y funciones descriptivos

## Formato de respuesta
- Proporciona explicaciones breves y directas
- No repitas información que ya está clara en el código
- Mantén las respuestas concisas y al punto

## Ejemplos de lo que NO hacer:
```c
// Incrementar el contador en 1
contador++;

// Verificar si el número es mayor que 10
if (numero > 10) {
    // Imprimir mensaje
    printf("Número es mayor que 10\n");
}
```

## Ejemplos de lo que SÍ hacer:
```c
contador++;

if (numero > 10) {
    printf("Número es mayor que 10\n");
}

// Solo comentarios cuando agreguen valor real:
// Usar PID como semilla para evitar que todos los procesos generen la misma secuencia
srand(time(NULL) + getpid());
```
