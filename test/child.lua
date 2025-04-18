function drawArc(x, y, orad, irad, step, off, arc, dir)
  dir=dir or 1
  local m,o,i=math,orad,irad
  local sin,cos,pi,pi2=m.sin,m.cos,m.pi,m.pi*2
  local sa,ba=pi2/step,off
  arc=m.min(m.max(arc,-pi2),pi2)
  for j=0, math.floor(arc / (pi2 / step)) do
  local sc,sn=ba+sa*j*dir,ba+sa*(j+1)*dir
  local x0,y0,x1,y1=cos(sc),sin(sc),cos(sn),sin(sn)
  screen.drawTriangleF(x+x0*o,y-y0*o,x+x0*i,y-y0*i,x+x1*o,y-y1*o)
  screen.drawTriangleF(x+x0*i,y-y0*i,x+x1*o,y-y1*o,x+x1*i,y-y1*i)
  end
  end
  