#pragma once
#include <string>
#include <variant>

enum Priority {
    urgentImportant,
    urgent,
    important,
    normal
};

std::string priorityToString(Priority priority);


struct Range {
    unsigned begin;

    std::variant<unsigned, bool> end;

    explicit Range(const unsigned _begin = 0, const std::variant<unsigned, bool> _end = true): begin(_begin),
        end(_end) {}

    static Range zero;

    bool operator!=(const Range& r) const { return begin != r.begin || end != r.end; }
};


enum Sort { asc, desc };
