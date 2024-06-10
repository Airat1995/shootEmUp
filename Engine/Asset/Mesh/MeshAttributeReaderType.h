#pragma once

#include "Format.h"

class MeshAttributeReaderType {
public:
    MeshAttributeReaderType(char *name, const Format format) : _name(name), _format(format) {
    }

    char *GetAttributeName() const noexcept {
        return _name;
    }

    Format GetAttributeFormat() const noexcept {
        return _format;
    }

private:
    char *_name;
    Format _format;
};
