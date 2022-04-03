#include <stdlib.h>

class NetworkReceive {
    public:
        uint32_t can_id;
        uint16_t instance_id;
        uint16_t size;
        u_int8_t *data;

        void fromByteArray(u_int8_t *buff);
};
