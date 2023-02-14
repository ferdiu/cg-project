
#ifdef FERDIU_ENGINE_BUILD
// Building the library
#ifdef _WIN32
// Use the Windows-specific export attribute
#define FERDIU_ENGINE_EXPORT __declspec(dllexport)
#elif __GNUC__ >= 4
// Use the GCC-specific export attribute
#define FERDIU_ENGINE_EXPORT __attribute__((visibility("default")))
#else
// Assume that no export attributes are needed
#define FERDIU_ENGINE_EXPORT
#endif
#else
// Using (including) the library
#ifdef _WIN32
// Use the Windows-specific import attribute
#define FERDIU_ENGINE_EXPORT __declspec(dllimport)
#else
// Assume that no import attributes are needed
#define FERDIU_ENGINE_EXPORT
#endif
#endif
