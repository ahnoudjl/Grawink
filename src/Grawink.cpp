#include "GrawEditor.h"
#include <iostream>
#include <fstream>

GrawEditor& GrawEditor::GetEditor() {
    static GrawEditor instance;
    return instance;
}

GrawEditor::GrawEditor() : selectedShapes_(ShapeType::All), canvasWidth_(1000), canvasHeight_(1000) {}

GrawEditor& GrawEditor::Add(ShapePtr shape) {
    ShapeType type = shape->GetType();      
    shapes_[type].push_back(shape);        
    undoStack_.push_back(shape);           
    return *this;                          
}

GrawEditor& GrawEditor::Delete(ShapePtr shape) {
    ShapeType type = shape->GetType();
    auto& container = shapes_[type];        
    container.erase(std::remove(container.begin(), container.end(), shape), container.end());
    return *this;
}

GrawEditor& GrawEditor::Undo() {
    if (!undoStack_.empty()) {
        ShapePtr shape = undoStack_.back();
        undoStack_.pop_back();
        Delete(shape);
        redoStack_.push_back(shape);
    }
    return *this;
}

GrawEditor& GrawEditor::Redo() {
    if (!redoStack_.empty()) {
        ShapePtr shape = redoStack_.back();
        redoStack_.pop_back();
        Add(shape);
    }
    return *this;
}

GrawEditor& GrawEditor::Resize(double newWidth, double newHeight) {
    double scaleX = newWidth / canvasWidth_;
    double scaleY = newHeight / canvasHeight_;

    for (auto& shapeCategory : shapes_) {
        for (auto& shape : shapeCategory.second) {
            shape->scale(scaleX, scaleY);
        }
    }

    canvasWidth_ = newWidth;
    canvasHeight_ = newHeight;

    return *this;
}

GrawEditor& GrawEditor::Crop(double x, double y, double width, double height) {
    for (auto& shapeCategory : shapes_) {
        ShapeContainer& container = shapeCategory.second;
        container.erase(std::remove_if(container.begin(), container.end(),
                          [x, y, width, height](const ShapePtr& shape) {
                              // Vérifier si le centre de la forme est en dehors du rectangle de rognage
                              double centerX = shape->x();
                              double centerY = shape->y();
                              return (centerX < x || centerX > x + width || centerY < y || centerY > y + height);
                          }),
                        container.end());
    }
    canvasWidth_ = width;
    canvasHeight_ = height;

    return *this;
}


GrawEditor& GrawEditor::Print() {
    for (const auto& entry : shapes_) {
        if (static_cast<uint64_t>(selectedShapes_) & static_cast<uint64_t>(entry.first)) {
            for (const auto& shape : entry.second) {
                std::cout << shape->ToString() << std::endl;
            }
        }
    }
    return *this;
}

GrawEditor& GrawEditor::ExportSVG(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "<svg width=\"" << canvasWidth_ << "\" height=\"" << canvasHeight_ << std::endl;
        for (const auto& entry : shapes_) {
            if (static_cast<uint64_t>(selectedShapes_) & static_cast<uint64_t>(entry.first)) {
                for (const auto& shape : entry.second) {
                    file << shape->ToSVG() << std::endl;
                }
            }
        }
        file << "</svg>" << std::endl;
        file.close();
    }
    return *this;
}

template <typename T>
std::shared_ptr<T> GrawEditor::GetNew() {
    return std::make_shared<T>();
}

template std::shared_ptr<Rectangle> GrawEditor::GetNew<Rectangle>();
template std::shared_ptr<Triangle> GrawEditor::GetNew<Triangle>();
template std::shared_ptr<Stroke> GrawEditor::GetNew<Stroke>();
template std::shared_ptr<Ellipsis> GrawEditor::GetNew<Ellipsis>();
template std::shared_ptr<Hexagon> GrawEditor::GetNew<Hexagon>();
template std::shared_ptr<Heptagon> GrawEditor::GetNew<Heptagon>();
template std::shared_ptr<Octogon> GrawEditor::GetNew<Octogon>();
template std::shared_ptr<Pentagon> GrawEditor::GetNew<Pentagon>();

// $ g++ -std=c++11 -Wall -Wextra -Werror -pedantic -o Grawink Grawink.cpp

// $ ./Grawink