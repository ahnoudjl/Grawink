#ifndef _GRAWEDITOR_H_
#define _GRAWEDITOR_H_

#include <memory>
#include <vector>
#include <map>
#include "Shape.h"

class GrawEditor {
public:
    using ShapePtr = std::shared_ptr<Shape>;
    using ShapeContainer = std::vector<ShapePtr>;

    enum class ShapeType : uint64_t {
        Stroke    = 1ULL << 0,
        Triangle  = 1ULL << 1,
        Rectangle = 1ULL << 2,
        Pentagon  = 1ULL << 3,
        Hexagon   = 1ULL << 4,
        Heptagon  = 1ULL << 5,
        Octogon   = 1ULL << 6,
        Ellipsis  = 1ULL << 7,
        All       = ~0ULL
    };

    static GrawEditor& GetEditor();

    GrawEditor& Add(ShapePtr shape);

    GrawEditor& Delete(ShapePtr shape);

    GrawEditor& Undo();

    GrawEditor& Redo();

    GrawEditor& Resize(double newWidth, double newHeight);

    GrawEditor& Crop(double x, double y, double width, double height);

    GrawEditor& Select(ShapeType shapeType);

    GrawEditor& Print();

    GrawEditor& ExportSVG(const std::string& filename);

    template <typename T>
    std::shared_ptr<T> GetNew();

private:
    GrawEditor();
    GrawEditor(const GrawEditor&) = delete;
    GrawEditor& operator=(const GrawEditor&) = delete;

    std::map<ShapeType, ShapeContainer> shapes_;
    ShapeContainer undoStack_;
    ShapeContainer redoStack_;
    ShapeType selectedShapes_;
    double canvasWidth_;
    double canvasHeight_;
};

#endif /* _GRAWEDITOR_H_ */
