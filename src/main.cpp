#include <iostream>
#include "GrawEditor.h"
#include "Shape.h"

int main() {
    GrawEditor& editor = GrawEditor::GetEditor();

    // Créez quelques formes
    auto circle = editor.GetNew<Circle>();
    auto rectangle = editor.GetNew<Rectangle>();

    // Ajoutez les formes à l'éditeur
    editor.Add(circle);
    editor.Add(rectangle);

    // Imprime les formes dans l'éditeur
    editor.Print();

    // Exporte les formes au format SVG
    editor.ExportSVG("output.svg");

    return 0;
}
