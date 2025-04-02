import sys
import datetime
import time
import os

name=sys.argv[1]
nupper=name.upper()
ver=sys.argv[2]
out=sys.argv[3]


buildDate=datetime.date.today().strftime("%A %b %d")
buildDateNum=datetime.date.today().strftime("%x")
buildTime=datetime.datetime.now().strftime("%X")


content = f"""#ifndef {nupper}_VERSION_H
#define {nupper}_VERSION_H

#define {nupper}_VERSION_STRING \"{ver}\"
#define {nupper}_BUILD_DATE \"{buildDate}\"
#define {nupper}_BUILD_DATE_NUM \"{buildDateNum}\"

#endif
"""

print(f"-> {out}")

def get_last_write_time(path):
  timestamp = os.path.getmtime(path)
  return time.localtime(timestamp)

if not os.path.exists(out) or datetime.date.today().day != get_last_write_time(out).tm_mday:
  os.makedirs(os.path.dirname(out), exist_ok=True)
  with open(out, "w") as fi:
    fi.write(content)
