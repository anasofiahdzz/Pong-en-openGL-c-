# Pong en openGL/C++

## Características
- Está pensado para dos jugadores
- Tiene marcadores de puntuación
- Física de la pelota con variación de ángulo (El ángulo de la pelota cambia según dónde impacta la paleta)
## Requisitos previos
Para compilar y ejecutar:
- Compilador de C++
- OpenGL
- GLUT
## Instalación (necesario para Fedora)
1. Instala las dependencias necesarias:
sudo dnf install freeglut-devel
sudo dnf5 install '@development-tools' (herramientas de desarrollo)
sudo dnf5 install gcc-c++ freeglut-devel (bibliotecas específicas)
2. Compilación:
g++ -o openGL Example2_4.cpp -lGL -lGLU -lglut -lm
3. Ejecición:
./openGL

## Para jugar
### Controles
- Paleta izquierda:
- Tecla 'A': Subir
- Tecla 'Z': Bajar
- Paleta derecha:
- Tecla 'K': Subir
- Tecla 'M': Bajar
### Reglas del juego
- La pelota rebota entre las dos paletas
- Se agrega un punto cuando el oponente falla la pelota
- El primer jugador en alcanzar la mayor puntuación gana
### Funciones de las teclas
- `display()`: Función principal de renderizado
- `keyboard()`: Entrada del jugador (teclas)
- `timer()`: Controla la actualización de la puntuación del juego
- `init()`: Inicializa el estado del juego
- `paletas()`: Renderiza las paletas
- `draw_ball()`: Renderiza la pelota



