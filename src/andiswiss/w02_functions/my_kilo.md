# Analysis of my_kilo.c

- Hint for analysing: First, look at `int main(..)`. Then go through each function-call:
- First the editor is initialized, with the `initEditor()`-function
- Then the style of the syntax-highlighting is selecting with the `editorSelectSyntaxHighlight(..)`-function
  - Already implemented file-extensions are listed here: `char *C_HL_extensions[] = {".c",".cpp",NULL};`
  - And the already implemented keywords which get automatically colored are defined here: `char *C_HL_keywords[] = {..}`
  - try this out with `make my_kilo && ./out/my_kilo my_code.c` -> compiles my_kilo to ./out, executes it and opens or
    creates the file my_code.c
- Next, the file is created or opened (if it already existed) - with `editorOpen(..)`
  - `E` actually holds the **editorConfig**
  - as you can see in `struct editorConfig {..}`, each row is saved in `erow *row;`
  - and as you can see in `typedef struct erow {..}`, the actual content is saved in `char *chars;`
- in the `while(1) { editorRefreshScreen(); editorProcessKeypress(STDIN_FILENO); }`:
  - `editorRefreshScreen();` always paints a new version of the full screen
  - `editorProcessKeypress(STDIN_FILENO);` processes all keystrokes, including "ctrl + s" or "ctr + q", ...

 
