## Minishell

**Minishell** es un proyecto desarrollado en **42 Madrid** cuyo objetivo es implementar un shell propio, simulando un pequeño Bash. Es una oportunidad para aprender sobre **procesos**, **file descriptors**, **señales**, y **pipes**, controlando todo desde bajo nivel con C.

![Logo 42 Madrid](42-Madrid.jpeg)

### 🏛️ Descripción del Proyecto

Minishell es una aplicación que interpreta comandos escritos por el usuario en un entorno de línea de comandos interactivo. Soporta comandos encadenados con pipes, redirecciones de entrada/salida, variables de entorno, y varios built-ins, siguiendo el comportamiento de Bash.

#### Características Principales

- **Gestión de procesos** con `fork`, `execve`, `wait`, y `signal`.
- **Soporte de redirecciones**: `<`, `>`, `>>`, `<<`.
- **Interpretación de variables de entorno**, incluido `$?`.
- **Gestión de señales** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
- **Historial y lectura interactiva** con `readline`.
- **Comandos built-in**: `cd`, `echo`, `env`, `export`, `exit`, `pwd`, `unset`.
- **Pipelines** para conectar comandos (`ls | grep x`).
- **Manejo de errores y código de salida coherente**.
- **Ejecución de comandos incluso sin variables de entorno** (`env -i ./minishell`).

### 🎬 Vídeo explicativo

![Demo](minishell.gif)

### 📁 Archivos Incluidos

- **`Makefile`** → Compila el proyecto con reglas estándar (`all`, `clean`, `fclean`, `re`). También incluye reglas personalizadas como `make print` para visualizar lo que se almacena en las estructuras del lexer y el parser.
- **`main.c`** → Punto de entrada de la shell, inicializa estructuras y entra en el bucle de ejecución.
- **`main_utils.c`** → Funciones auxiliares utilizadas por `main.c`, como validaciones o inicializaciones.
- **`free_structs.c`** → Libera estructuras y recursos dinámicos para evitar memory leaks.
- **`signals.c`** → Manejo de señales como `SIGINT` (Ctrl-C), `SIGQUIT` (Ctrl-\) y su impacto en la shell.
- **`minishell.h`** → Archivo de cabecera principal con prototipos, estructuras y macros compartidas.

#### Carpetas de implementación:

- **`built-ins/`** → Implementación de comandos internos (`cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`) según especificación del proyecto.
- **`exec/`** → Gestión de la ejecución de comandos, incluyendo creación de procesos, pipes y duplicación de descriptores.
- **`gnl/`** → Implementación de `get_next_line`, útil para lecturas personalizadas o heredoc.
- **`heredoc/`** → Lógica del heredoc (`<<`) y control de su comportamiento en combinación con señales.
- **`lexer/`** → Tokenización de la línea de comandos: división de palabras, gestión de comillas, metacaracteres, etc.
- **`parser/`** → Construcción de estructuras de comandos a partir de los tokens generados por el lexer.
- **`print/`** → Código de depuración. Contiene un `main` especial para imprimir y analizar estructuras (`make print`).
- **`redirections/`** → Módulo que gestiona las redirecciones de entrada y salida (`<`, `>`, `>>`, `<<`).
- **`text_visualizer/`** → Contiene el comando `jp`, un visualizador de texto desarrollado para representar visualmente estructuras como árboles sintácticos.
- **`utils/`** → Funciones auxiliares utilizadas en distintas partes del código (manejo de errores, strings, validaciones, etc.).
- **`libft/`** → Funciones de la librería.

### 🚀 Cómo Usarlo

1. **Compilación:**
   ```bash
   make
   ```

2. **Ejecución:**
   ```bash
   ./minishell
   ```

3. **Salida esperada:**
   - Un prompt interactivo.
   - Comandos ejecutados como en Bash.
   - Soporte para redirecciones, pipes y variables de entorno.

Otra forma de usarlo sería haciendo:
   ```bash
   make print
   ```
para visualizar lo que se almacena en las estructuras del lexer y el parser.

### 🔧 Comandos Implementados

#### Built-ins
- `echo [-n]`
- `cd [dir]`
- `pwd`
- `export [VAR=VAL]`
- `unset VAR`
- `env`
- `exit [status]`

#### Redirecciones
- `>`: salida.
- `<`: entrada.
- `>>`: append.
- `<<`: heredoc.

#### Pipes
- Soporte completo de múltiples pipes: `ls | grep .c | wc -l`.

### 🧪 Casos de Prueba Recomendados

#### Compilación
- `cc *.c -Wall -Wextra -Werror` sin `-g` ni `sanitize`
- `make -r` para ver flags del Makefile

#### Valgrind
- `valgrind ./minishell` (¡cuidado con `readline`!)

#### Comprobación de códigos de error
```bash
echo $?          # Verifica salida anterior
commandnotfound  # Debe dar 127
.                # Da 2
./folder         # Da 126
cd notadir       # Da 1
```

#### Comportamiento de `echo`
- `echo $$$$`
- `echo -nnnn hola`, `echo -nnnnp hola`
- `echo "$USER '$USER'"`, `echo "'$USER'"`, etc.
- Comillas, variables, espacios, combinaciones raras.

#### Export, unset y env
- Manejo de valores vacíos, duplicados, export dinámico y ejecución de variables como comandos.

#### `cd` y actualización de `PWD`, `OLDPWD`
- `cd`, `cd -`, `cd ~`, `cd ..`, etc.

#### `exit` y sus errores
- Combinaciones con varios argumentos, valores no numéricos, negativos.

#### Redirecciones y combinaciones locas
- `ls > a > b > c`
- `cat < 1 < 2 > 3`
- `sleep 2 | ls` y comprobaciones de ejecución simultánea

#### Heredocs
- `<<`, uso de pipes, Ctrl+C, delimitadores estrictos

#### Cosas raras pero posibles
- Comillas sin cerrar
- Comandos con caracteres especiales o inválidos
- Expresiones raras como `ec'h''o'` o `ls '-la'`

### ⚠️ Reglas de Evaluación

- **Sin memory leaks** (salvo los conocidos de `readline`).
- **Sin "seg faults"**.
- **Manejo correcto de señales** en modo interactivo.
- **Ejecuta comandos internos y externos** con y sin `PATH`.
- **Salida coherente del programa** tras errores.
- **`SHLVL` actualizado** si se lanza una minishell desde otra.
- Seguir la **norma de 42**.
