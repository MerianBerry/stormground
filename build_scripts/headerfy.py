import sys
import os

os.makedirs(os.path.dirname(sys.argv[2]), exist_ok=True)
with open(sys.argv[2],'w') as result_file:
  result_file.write('#pragma once\n\nstatic const char %s[] = {\n\t' % sys.argv[3])
  #print(f"Generating {sys.argv[2]}")
  for line in open(sys.argv[1], 'r').readlines():
      outline=""
      for c in line:
        if c=='\n' or c=='\r':
          continue
        if c == '\\':
          outline+="\\\\"
        elif c == '\"':
          outline+="\\\""
        else:
          outline+=c
      result_file.write(f"\"{outline}\\n\"\n\t")
  #for b in open(sys.argv[1], 'r').read():
  #  result_file.write(b)
  result_file.write('};\n')