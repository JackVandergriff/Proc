#ifdef __cplusplus
extern "C" {
#endif

#include "process.h"

int16_t makeEntry(Pageref* pr, int16_t entry) {
    if (pr->current.entries[0] == 0) {
        pr->current.entries[0] = entry;
    } else if (pr->current.entries[1] == 0) {
        pr->current.entries[1] = entry;
    } else if (pr->current.entries[2] == 0) {
        pr->current.entries[2] = entry;
    } else if (pr->current.entries[3] == 0) {
        pr->current.entries[3] = entry;
        Sector page_out;
        page_out.page = pr->current;
        memset(pr->current.entries, 0, sizeof(pr->current.entries));
        pr->ref[pr->pages + 1 + pr->ref[0].header.buffers] = page_out;
        pr->pages++;
        assert(pr->pages < pr->ref[0].header.pages);
    } else {
        printf("NOPE\n");
        assert(false);
    }
}

Pageref createPageref(long IOR_map, int buffers) {
    Pageref pr;
    int sectors = pow(2, GETINPUTLEN(IOR_map)) / 4;
    pr.IOR_map = IOR_map;
    pr.max_pages = sectors;
    pr.pages = 0;
    pr.ref = malloc(sizeof(Sector) * (sectors + buffers + 2));
    memset(pr.current.entries, 0, sizeof(pr.current.entries));
    Sector header_out;
    header_out.header.pages = sectors;
    header_out.header.buffers = buffers;
    pr.ref[0] = header_out;
    return pr;
}

int main() {
    Pageref p = createPageref(4L, 0);
    makeEntry(&p, 0b0000);
    makeEntry(&p, 0b0001);
    makeEntry(&p, 0b0010);
    makeEntry(&p, 0b0011);
    return 0;
}

#ifdef __cplusplus
}
#endif