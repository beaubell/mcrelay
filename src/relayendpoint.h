#pragma once

#include <cstring>

class RelayEndpoint {
public:
    RelayEndpoint* rEP;
    void setRelay(RelayEndpoint* rep) { rEP = rep; }

    virtual void do_send(void* data, size_t size) = 0;

};
