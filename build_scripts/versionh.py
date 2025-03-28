import sys
import datetime
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
#define {nupper}_BUILD_TIME \"{buildTime}\"

#endif
"""

print(f"-> {out}")

os.makedirs(os.path.dirname(out), exist_ok=True)
with open(out, "w") as fi:
  fi.write(content)
