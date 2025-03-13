#include "CustomDataStructures.h"


Range Range::zero = Range(0);


std::string priorityToString(const Priority priority) {
    switch (priority) {
        case urgentImportant:
            return "紧急且重要";
        case urgent:
            return "紧急不重要";
        case important:
            return "重要不紧急";
        case normal:
            return "不重要不紧急";
    }
    return "Error";
}