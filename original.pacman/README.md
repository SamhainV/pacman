# Pacman (SDL 1.2 + Restauración de Resolución con xrandr)

Este es un clon clásico de **Pacman** desarrollado en **C** usando **SDL 1.2**. Incluye soporte para restaurar la resolución y la disposición de pantallas en sistemas Linux con **X11**, gracias a `xrandr` y `GLFW`.

---

## 🧩 Características

* Motor basado en **SDL 1.2** para gráficos y audio.
* Restauración automática de la resolución original tras salir del juego.
* Compatibilidad con **varios monitores** y disposición extendida (`--pos`, `--primary`).
* Código optimizado para sistemas Linux con Makefile tradicional.

---

## 📦 Requisitos

### Librerías necesarias:

* `libsdl1.2-dev`
* `libsdl-image1.2-dev`
* `libglfw3-dev`
* `libmikmod-dev`
* `x11-utils` (para `xrandr`)

Puedes instalarlas en Debian/Ubuntu con:

```bash
sudo apt install libsdl1.2-dev libsdl-image1.2-dev libglfw3-dev libmikmod-dev x11-utils
```

---

## ⚙️ Compilación

1. Abre una terminal en la carpeta del proyecto.
2. Ejecuta:

```bash
make
```

Esto generará un ejecutable llamado `pacman`.

---

## ▶️ Ejecución

Puedes ejecutar el juego en modo **pantalla completa** o **ventana**:

```bash
./pacman -f   # Pantalla completa
./pacman -w   # Ventana
```

Durante el arranque:

* Se guarda la resolución del monitor principal con GLFW.
* Se genera un script en `/tmp/restaurar_xrandr.sh` que almacena:
  * La resolución de cada salida.
  * La posición relativa entre pantallas.
  * Cuál era la salida primaria.

Al cerrar el juego:

* Se ejecuta el script para restaurar el estado anterior del escritorio, incluyendo **modo extendido entre pantallas**.

---

## 📁 Estructura del proyecto

```
pacman/
├── Makefile
├── src/
│   ├── main.c
│   └── ... (otros módulos)
├── data/         # Recursos: sonidos, imágenes
└── sound         # Flag para activar audio
```

---

## 🛠 Sugerencias y observaciones

* La restauración puede tardar **1-2 segundos**, especialmente si tienes varios monitores.
* El script generado está en:

  ```
  /tmp/restaurar_xrandr.sh
  ```

  Puedes examinarlo o ejecutarlo manualmente si lo necesitas.

---

## 🚫 `.gitignore` personalizado

Se ha modificado el archivo `.gitignore` para ignorar archivos temporales y objetos generados durante la compilación:

```gitignore
*.o     # Archivos objeto generados por el compilador
*~      # Archivos temporales de editores como Emacs o Vim
pacman  # El ejecutable generado tras compilar
```

### ¿Por qué estos archivos?

- `*.o`: Son archivos intermedios que genera `gcc` al compilar. No es necesario almacenarlos en el repositorio.
- `*~`: Archivos de respaldo creados automáticamente por editores de texto.
- `pacman`: El binario final, que se puede regenerar fácilmente con `make`. No debe versionarse.

Esto ayuda a mantener el repositorio **limpio**, evitando subir archivos que no aportan al código fuente y que pueden variar según el entorno del desarrollador.

---

## 👤 Autor

Desarrollado por **amr** usando Debian Testing y herramientas clásicas de programación en C.

---

## 🕹 Licencia

Este proyecto es de libre distribución para fines educativos y personales.

---

Disfruta comiéndote fantasmas 👻 y restaurando tu resolución como un pro 😎.
