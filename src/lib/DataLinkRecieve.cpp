#include <stdio.h>
#include "inc/DataLinkRecive.hpp"

void DataLinkReceive::flush() {
    this->arrayIndex = 0;
    this->escaped = false;
    this->in_progress = false;
}

bool DataLinkReceive::read(u_int8_t data) {
    if (this->escaped) {
        this->escaped = false;
        return false;
    }

    if (data == ESCAPE) {
        this->escaped = true;
        return false;
    }

    if (data == START) {
        if (this->in_progress) {
            this->flush();
            printf("Error: There was multiple start conditions\n, data: %d", data);
            return false;
        }
        this->in_progress = true;
        return false;
    }

    if (data == END) {
        if (!this->in_progress) {
            this->flush();
            printf("Error: There was an end condition without a start\n");
            return false;
        }
        this->in_progress = false;
        return true;
    }

    if (!this->in_progress) {
        this->flush();
        printf("Error: There must be a start condition before a transmission can occour\n");
        return false;
    }

    this->buffer[this->arrayIndex] = data;
    this->arrayIndex++;
    return false;
}
