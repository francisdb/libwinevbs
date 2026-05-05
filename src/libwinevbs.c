#include "libwinevbs.h"

static libwinevbs_callbacks_t g_callbacks = { 0 };

void libwinevbs_init(const libwinevbs_callbacks_t* callbacks)
{
   if (callbacks)
      g_callbacks = *callbacks;
}

void libwinevbs_shutdown(void)
{
   memset(&g_callbacks, 0, sizeof(g_callbacks));
}

void external_log_info(const char* format, ...)
{
   if (g_callbacks.log) {
      va_list args;
      va_start(args, format);
      g_callbacks.log(LIBWINEVBS_LOG_INFO, format, args);
      va_end(args);
   }
}

void external_log_debug(const char* format, ...)
{
   if (g_callbacks.log) {
      va_list args;
      va_start(args, format);
      g_callbacks.log(LIBWINEVBS_LOG_DEBUG, format, args);
      va_end(args);
   }
}

void external_log_error(const char* format, ...)
{
   if (g_callbacks.log) {
      va_list args;
      va_start(args, format);
      g_callbacks.log(LIBWINEVBS_LOG_ERROR, format, args);
      va_end(args);
   }
}

HRESULT external_create_object(const WCHAR* progid, IClassFactory* cf, IUnknown** obj)
{
   if (g_callbacks.create_object)
      return g_callbacks.create_object(progid, cf, obj);

   external_log_error("Creating an object is not supported");
   return CLASS_E_CLASSNOTAVAILABLE;
}
