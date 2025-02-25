#include <cstdlib>
#include <fstream>
#include <ctime>
#include "api.hpp"
#include "NetHost/NetHost.hpp"

namespace fs = std::filesystem;
using string = std::string;
using path   = fs::path;

static string        Error = "";
static std::ofstream Log;
static bool          noLog = false;

void Storm_SetError (std::string err) {
  Error = err;
}

void Storm_Free (void* ptr) {
  free (ptr);
}

char const* Storm_GetError() {
  char* buf = new char[Error.length() + 1];
  memcpy (buf, Error.c_str(), Error.length() + 1);
  return buf;
}

static bool Storm_PreLog() {
  if (!Log.is_open() && !noLog) {
    path lpath = Storm_ExecutableDir() / "storm.log";
    Log.open (lpath.string());
    noLog = !Log.is_open();
  }
  return !noLog;
}

static void Storm_Log (char const* source, char const* severity,
  char const* msg, char const* trace) {
  if (!Storm_PreLog())
    return;
  time_t t  = time (NULL);
  tm*    tm = std::localtime (&t);
  Log << std::put_time (tm, "[%H:%M:%S]");
  Log << " [" << source << "/" << severity << "]: ";
  if (msg)
    Log << msg;
  if (trace) {
    Log << std::endl;
    Log << trace;
  }
  Log << std::endl;
}

void Storm_LogInfo (char const* source, char const* msg, char const* trace) {
  Storm_Log (source, "INFO", msg, trace);
}

void Storm_LogWarn (char const* source, char const* msg, char const* trace) {
  Storm_Log (source, "Warn", msg, trace);
}

void Storm_LogError (char const* source, char const* msg, char const* trace) {
  if (msg)
    Storm_SetError (msg);
  Storm_Log (source, "ERROR", msg, trace);
}

path Storm_ExecutablePath() {
#ifdef _WIN32
  char buf[MAX_PATH + 1];
  memset (buf, 0, sizeof (buf));
  GetModuleFileName (NULL, buf, MAX_PATH);
#endif
  fs::path ed = buf;
  return ed;
}

path Storm_ExecutableDir() {
  return Storm_ExecutablePath().parent_path();
}
