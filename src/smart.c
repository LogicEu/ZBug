#include <ZBug.h>

void zbug_smart_init(const char* fp, unsigned int self_check)
{
    zbug_init(fp, self_check);
    zbug_manager_init();
}

void* zbug_smart_malloc(const char* _file_, unsigned int _line_, const char* func, size_t size)
{
    zbug_log("malloc(%zu) | %u / %s / %s | ", size, _line_, _file_, func);
    void* data = malloc(size);
    zbug_manager_push(data, size);
    zbug_log("(%p) [%zu] %zu\n", data, zbug_allocated(), zbug_index());
    return data;
}

void* zbug_smart_calloc(const char* _file_, unsigned int _line_, const char* func, size_t count, size_t size)
{
    zbug_log("calloc(%zu, %zu) | %u / %s / %s | ", count, size, _line_, _file_, func);
    void* data = calloc(count, size);
    zbug_manager_push(data, size * count);
    zbug_log("(%p) [%zu] %zu\n", data, zbug_allocated(), zbug_index());
    return data;
}

void* zbug_smart_realloc(const char* _file_, unsigned int _line_, const char* func, void* ptr, size_t size)
{
    zbug_log("realloc(%p, %zu) | %u / %s / %s | ", ptr, size, _line_, _file_, func);
    void* data = realloc(ptr, size);
    zbug_manager_realloc(ptr, size, ptr);
    zbug_log("(%p) [%zu]\n", data, zbug_allocated());
    return data;
}

void zbug_smart_free(const char* _file_, unsigned int _line_, const char* func, void* ptr)
{
    zbug_log("free(%p) | %u / %s / %s | ", ptr, _line_, _file_, func);
    free(ptr);
    zbug_manager_free(ptr);
    zbug_log("(%p) [%zu]\n", ptr, zbug_allocated());
}

void zbug_smart_exit()
{
    zbug_manager_exit();
    zbug_log("Total allocated left: %zu\n", zbug_allocated());
    zbug_exit();
}