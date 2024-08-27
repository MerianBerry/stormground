---@diagnostic disable lowercase-global
local tab = stormground.getGamepad(1)

stormground.setScreen(288, 160)
local width, height = stormground.getScreen()
local currentParticle = 0
local currentBrush = 1 --sizes: 1, 3, 5, 8
local spawnChance = 0.8 --chance for particles to spawn
local reset = false
local anything = true
local physMult = 1
local colors = {
	{ 255,208,144 }, --sand1
	--{ 255,208,144 }, --sand2
	{ 32,48,208 }, --water1
	--{ 50, 86, 168 }, --water2
	{ 130,73,11 }, --wood
	--{ 130,73,11 }, --wood2
	{ 237, 16, 0 }, --fire1
	--{ 237, 186, 0 }, --fire2
	{ 59, 59, 59 }, --smoke1
	--{ 33, 33, 33 }, --smoke2
}

local particles = {
	{ --sand
		color = 1,
		color2 = 1,
		lifetime = -1,
		any = false,
	},
	{ --water
		color = 2,
		color2 = 3,
		lifetime = -1,
		any = false,
	},
	{ --wood
		color = 4,
		color2 = 4,
		lifetime = -1,
		any = false,
	},
	{ --fire
		color = 5,
		color2 = 6,
		lifetime = 300,
		any = false,
	},
	{ --smoke
		color = 7,
		color2 = 8,
		lifetime = 400,
		any = false,
	},
}

local numParticles = 0
local simParticles = 0
local numLines = 0
local cells = {}

for y = 0, height - 1, 1 do
	for x = 1, width-1, 1 do
		-- -1 is empty, 1 is sand, 2 is water, 3 is wood, etc
		cells[x + y * width] = -1
	end
end

local ticks = 0
local lastTime = stormground.getTime()
local lastTicks = 0
local fps = 0
function onTick()
  local time = stormground.getTime()
  local tickstart = os.clock()
  ticks = ticks + 1
  numParticles = 0
  simParticles = 0
  numLines = 0

  local pulse = stormground.getButton("left") == "pressed"
  local touch = stormground.getButton("left") == "held"

  local inputX, inputY = stormground.getCursor()
  currentBrush = (stormground.getKey("equal") == "held") and currentBrush + 1 or currentBrush
  currentBrush = (stormground.getKey("minus") == "held") and currentBrush - 1 or currentBrush

  currentBrush = clamp(currentBrush, 1, 50)

  if stormground.getKey("tab") == "pressed" then
	setDebug = not setDebug
  end
  if stormground.getKey("p") == "pressed" then
	pause = not pause
  end

  if touch then
	  --check to see if user has clicked the select boxes
	  if IsPointInRect(inputX, inputY, 272, 5, 10, 10) then --erase box
		  currentParticle = -1
	  elseif IsPointInRect(inputX, inputY, 272, 20, 10, 10) then --sand box
		  currentParticle = 0
	  elseif IsPointInRect(inputX, inputY, 272, 35, 10, 10) then --water box
		  currentParticle = 1
	  elseif IsPointInRect(inputX, inputY, 272, 50, 10, 10) then --wood box
		  currentParticle = 2
	  elseif IsPointInRect(inputX, inputY, 238, 5, 10, 10) then --erase box
		  reset = true
	  else
		  anything = true
		  --hasnt clicked any ui, place a particle
		  if currentParticle == -1 then
			  --say, this is empty
			  if currentBrush == 1 then
				  cells[inputX + inputY * width] = -1
			  else
				  for x = inputX - currentBrush, inputX + currentBrush, 1 do
					  for y = inputY - currentBrush, inputY + currentBrush, 1 do
						  if math.sqrt((x - inputX) ^ 2 + (y - inputY) ^ 2) <= currentBrush then
							  cells[x + y * width] = -1
						  end
					  end
				  end
			  end
		  elseif currentParticle == 0 then
			  --set every cell in the brush to sand
			  particles[1].any = true
			  if currentBrush == 1 then
				  if cells[inputX + inputY * width] == -1 then
					  cells[inputX + inputY * width] = 1
				  end
			  else
				  for x = inputX - currentBrush, inputX + currentBrush, 1 do
					  for y = inputY - currentBrush, inputY + currentBrush, 1 do
						  if math.sqrt((x - inputX) ^ 2 + (y - inputY) ^ 2) <= currentBrush then
							  if cells[x + y * width] == -1 then
								  if math.random() > spawnChance then
									  cells[x + y * width] = 1
								  end
							  end
						  end
					  end
				  end
			  end
		  elseif currentParticle == 1 then
			  --set every cell in the brush to water
			  particles[2].any = true
			  if currentBrush == 1 then
				  if cells[inputX + inputY * width] == -1 then
					  cells[inputX + inputY * width] = 2
				  end
			  else
				  for x = inputX - currentBrush, inputX + currentBrush, 1 do
					  for y = inputY - currentBrush, inputY + currentBrush, 1 do
						  if math.sqrt((x - inputX) ^ 2 + (y - inputY) ^ 2) <= currentBrush then
							  if cells[x + y * width] == -1 then
								  if math.random() > spawnChance then
									  cells[x + y * width] = 2
								  end
							  end
						  end
					  end
				  end
			  end
		  elseif currentParticle == 2 then
			  --set every cell in the brush to wood
			  particles[3].any = true
			  if currentBrush == 1 then
				  if cells[inputX + inputY * width] == -1 then
					  cells[inputX + inputY * width] = 3
				  end
			  else
				  for x = inputX - currentBrush, inputX + currentBrush, 1 do
					  for y = inputY - currentBrush, inputY + currentBrush, 1 do
						  if math.sqrt((x - inputX) ^ 2 + (y - inputY) ^ 2) <= currentBrush then
							  if cells[x + y * width] == -1 then
								  cells[x + y * width] = 3
							  end
						  end
					  end
				  end
			  end
		  end
	  end
  end

  --please lord help i want to die
  --for every type of particle, we loop through the table looking for that type, and run its update function
  if anything and not pause then
	  --physMult = fps/60
	  --physMult = tonumber(string.format("%.0f", 1/physMult))

	  for _, type in ipairs({1, 2, 3}) do
		  for c = #cells, 0, -1 do
			  if cells[c] == type then
				  UpdateParticle(c, type)
				  numParticles = numParticles + 1
			  end
		  end
	  end
  end

  --set entire stormground to empty
  if reset then
	  for y = 0, height, 1 do
		  for x = 0, width, 1 do
			  cells[x + y * width] = -1
		  end
	  end
	  reset = false
	  anything = false
	  particles[1].any = false
	  particles[2].any = false
	  particles[3].any = false
	  particles[4].any = false
	  particles[5].any = false
	end
	local timeTick = (os.clock() - tickstart) * 1000
	local drawstart = os.clock()
  --Drawing
  local timeDraw = stormground.getTime()

  --draw particles
  if anything then
	  local lines = {}  -- Table to store information about lines to draw
  
	  for type = 1, 3 do
		  -- Variables to track the start and end of a line
		  local lineStart = -1
		  local lineEnd = -1
		  
		  for ce = 0, #cells do
			  -- Get the value of the current cell
			  local cellValue = cells[ce]
			  
			  -- Check if the cell value matches the current type
			  if cellValue == type then
				  -- If this is the start of the line, record the position
				  if lineStart == -1 then
					  lineStart = ce
				  end
				  -- Update the end position as we traverse the line
				  lineEnd = ce
			  elseif lineStart ~= -1 then
				  -- If the current cell value is different and we were in a line, record the line
				  lines[#lines + 1] = { x1 = lineStart % width, x2 = (lineEnd % width) - (lineStart%width), y = lineStart // width, type = type }
				  -- Reset lineStart and lineEnd for the next potential line
				  lineStart = -1
				  lineEnd = -1
			  end
		  end
  
		  -- Check if the last line extends to the end
		  if lineStart ~= -1 then
			  lines[#lines + 1] = { x1 = lineStart % width, x2 = lineEnd % width, y = lineStart // width, type = type }
		  end
	  end

	  function getRandomColor()
		  return math.random(0, 255), math.random(0, 255), math.random(0, 255)
	  end
  
	  -- Draw the lines stored in the table
	  for _, line in ipairs(lines) do

		  -- Set color based on the line type
		  c(table.unpack(colors[line.type]))
		  if setDebug then
			  local r, g, b = getRandomColor()
			  c(r, g, b)
		  end

		  -- Draw the rectangle representing the line
		  stormground.drawRectangle(line.x1, line.y, line.x2 + 1, 1)
		  numLines = numLines + 1
	  end
  end

  --draw the brush
  if touch then
	  stormground.setColor(255, 255, 255)
	  if currentBrush == 1 then
		  stormground.drawRectangle(inputX, inputY, 0, 0)
	  else
		  stormground.drawCircle(inputX, inputY, currentBrush, currentBrush-1)
	  end
  end

  --erase select
  stormground.setColor(255, 50, 80)
  stormground.drawRectangle(272, 5, 9, 9)
  stormground.drawText(275, 7, 1, "X")
  if currentParticle == -1 then
	  stormground.setColor(255, 255, 255)
	  stormground.drawRectangle(271, 4, 11, 11)
  end

  --sand select
  c(table.unpack(colors[1]))
  stormground.drawRectangle(272, 20, 10, 10)
  if currentParticle == 0 then
	  stormground.setColor(214, 187, 161)
	  stormground.drawRectangle(271, 19, 11, 11)
  end

  --water select
  c(table.unpack(colors[2]))
  stormground.drawRectangle(272, 35, 10, 10)
  if currentParticle == 1 then
	  stormground.setColor(214, 187, 161)
	  stormground.drawRectangle(271, 34, 11, 11)
  end

  --wood select
  c(table.unpack(colors[3]))
  stormground.drawRectangle(272, 50, 10, 10)
  if currentParticle == 2 then
	  stormground.setColor(214, 187, 161)
	  stormground.drawRectangle(271, 49, 11, 11)
  end

  --reset button
  stormground.setColor(255, 255, 255)
  stormground.drawRectangle(238, 5, 10, 10)
  stormground.drawText(241, 8, 1, "R")

  
  --FPS shit
  if stormground.getTime() - lastTime > 0.1 then
	fps = (ticks - lastTicks) / (stormground.getTime() - lastTime)
	lastTicks = ticks
	lastTime = stormground.getTime()
  end
  stormground.setColor(255,255,255)
  timeDraw = (os.clock() - drawstart) * 1000
  stormground.drawText(1, 1, 1, string.format("fps:%.2f tick:%.0f draw:%.0f ttl:%.0f p:%d sim:%d ln:%d br:%d",
  fps, timeTick, timeDraw, timeTick+timeDraw, numParticles, simParticles, numLines, currentBrush))

end

function IsPointInRect(inputX, inputY, rectX, rectY, rectW, rectH)
  return inputX >= rectX and inputX <= rectX + rectW and inputY >= rectY and inputY <= rectY + rectH
end

function clamp(value, lower, upper)
  return math.min(math.max(value, lower), upper)
end

---@section helper functions

function InBounds(index)
  local x = index % width
  local y = index // width
  return x > 0 and x < width and y > 0 and y < height
end

function IsEmpty(index)
  return InBounds(index) and cells[index] == -1
end

function IsWater(index)
  return InBounds(index) and cells[index] == 2
end

function WillNotCollide(index, depth)
  local direction = depth > 0 and 1 or -1
  for i = 1, math.abs(depth) do
	  local checkIndex = index + i * direction
	  if not IsEmpty(checkIndex) then
		  return i * direction
	  end
  end

  return depth
end

function VertWillNotCollide(index, depth)
  local direction = depth > 0 and 1 or -1
  for i = 1, math.abs(depth) do
	  local checkIndex = index + (width * direction)
	  if not IsEmpty(checkIndex) then
		  return i * direction
	  end
  end
  return depth
end

function CompletelySurrounded(index)
  return not IsEmpty(index + width) and
		 not IsEmpty(index - width) and
		 not IsEmpty(index - 1) and
		 not IsEmpty(index + 1) and
		 not IsEmpty(index + width - 1) and
		 not IsEmpty(index + width + 1) and
		 not IsEmpty(index - width - 1) and
		 not IsEmpty(index - width + 1)
end

function IsInTable(value, table)
  for _, v in ipairs(table) do
	  if v == value then
		  return true
	  end
  end
  return false
end

function c(...) local _={...}
  --[[for i,v in pairs(_) do
   _[i]=_[i]^2.2/255^2.2*_[i]
  end]]
  stormground.setColor(table.unpack(_))
end

---@section update functions

function UpdateParticle(id, type)
  if type == 1 and not CompletelySurrounded(id) then
	  UpdateSand(id)
	  simParticles = simParticles + 1
  elseif type == 2 and not CompletelySurrounded(id) then
	  UpdateWater(id)
	  simParticles = simParticles + 1
  elseif type == 3 and not CompletelySurrounded(id) then
	  UpdateWood(id)
	  simParticles = simParticles + 1
  end
end

function MoveParticle(fromIndex, toIndex, particleType, replacedType)
  replacedType = replacedType or -1
  if toIndex < 46080 then
	  cells[fromIndex] = replacedType
	  cells[toIndex] = particleType
  end
end

function UpdateSand(index)
  local down = index + width
  local downLeft = index + width - 1
  local downRight = index + width + 1
  local airFloatChance = 0.8 -- Chance to move left or right when going down, represents floating in air
  
  --check down first
  local maxDown = VertWillNotCollide(index, physMult)
  if IsEmpty(down) then
	  --lil' chance to move left or right
	  if math.random() > airFloatChance then
		  local moveOptions = {0, 0}
		  moveOptions[1] = IsEmpty(downLeft) and downLeft or index
		  moveOptions[2] = IsEmpty(downRight) and downRight or index

		  MoveParticle(index, moveOptions[math.random(2)], 1)
		  return true
	  end

	  MoveParticle(index, index + (width * maxDown), 1)
	  return true
  end

  --now that the fun part is over, we check downleft and downright and move if can
  if IsEmpty(downLeft) then
	  MoveParticle(index, downLeft, 1)
	  return true
  end
  if IsEmpty(downRight) then
	  MoveParticle(index, downRight, 1)
	  return true
  end

  return false -- Did not move
end

function UpdateWater(index)
  local down = index + width
  local downLeft = index + width - 1
  local downRight = index + width + 1
  local left = index - 1
  local right = index + 1
  local maxMove = 8
  
  
  --check down first
  if IsEmpty(down) then
	  MoveParticle(index, down, 2)
	  return true
  end

  --now that the fun part is over, we check downleft and downright and move if can
  if IsEmpty(downLeft) then
	  MoveParticle(index, downLeft, 2)
	  return true
  end

  if IsEmpty(downRight) then
	  MoveParticle(index, downRight, 2)
	  return true
  end

  --and then as last resort, check left and right
  if IsEmpty(left) or IsEmpty(right) then
	  local maxPossibleMove = {0, 0}
  
	  local maxLeft = WillNotCollide(index, maxMove)
	  local maxRight = WillNotCollide(index, -maxMove)
  
	  maxPossibleMove[1] = maxLeft < 0 and maxLeft or 0
	  maxPossibleMove[2] = maxRight > 0 and maxRight or 0
  
	  local chosenOption = math.random(maxPossibleMove[1], maxPossibleMove[2])
	  if chosenOption ~= 0 then
		  MoveParticle(index, index + chosenOption, 2)
		  return true
	  end
  end

  return false -- Did not move
end

function UpdateWood(index)
  --wood is pretty simple for now. it isnt affected by gravity, so its stationary.
  --however, it is flamable (fire lmao)
end

--- draws an arc around pixel coords [x], [y]
--- @Param x number The X coordinate of the center of the arc
--- @Param y number The Y coordinate of the center of the arc
--- @Param outer_rad number The distance from the outer edge of the arc to the center of the arc. AKA Radius
--- @Param inner_rad number The distance from the inner edge of the arc to the center of the arc. Set to 0 to make a circle
--- @Param step number The amount of triangles to draw the entire arc. Step size does not stay constant, and may vary with arc_ang
--- @Param begin_ang number Beginning angle of the arc in radians
--- @Param arc_ang number Angle of the entire arc in radians
--- @Param dir number Direction of the arc. Default 1, -1 for reverse.
function drawCircle(x,y,outer_rad, inner_rad, step, begin_ang, arc_ang, dir)
  dir = dir or 1
  sin=math.sin cos=math.cos pi=math.pi pi2=math.pi*2
  step_s=pi2/step*-dir
  ba=begin_ang*dir
  ora=outer_rad
  ira=inner_rad
  for i=0, math.floor(arc_ang / (pi2 / step))-1 do
	step_p=ba+step_s*i
	step_n=ba+step_s*(i+1)
	stormground.drawTriangle(x+sin(step_p)*ora, y+cos(step_p)*ora, x+sin(step_n)*ora, y+cos(step_n)*ora, x+sin(step_p)*ira, y+cos(step_p)*ira)
	stormground.drawTriangle(x+sin(step_n)*ora, y+cos(step_n)*ora, x+sin(step_n)*ira, y+cos(step_n)*ira, x+sin(step_p)*ira, y+cos(step_p)*ira)
  end
end
