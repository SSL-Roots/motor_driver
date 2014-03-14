#!/usr/bin/ruby

begin	#Ctrl-cによる例外処理のため

require	'serialport'
require	'msgpack'

class	MotorDriver
	def	initialize(com, baud)
		@sp	= SerialPort.new(com, baud)
		@sp.read_timeout	= 1
	end

	def	printMessage
		until	(message = @sp.gets) == nil do
			p	message
		end
	end

	def	rotateOpenloop(voltage)
		send_data	= [3, [voltage]].to_msgpack
		@sp.write	send_data
	end

	def	rotateCloseloop(rad_per_sec)
		send_data	= [4, [rad_per_sec]].to_msgpack
		@sp.write	send_data
	end
end


########################################


########################################
class	Test
	NUM_CYCLE	= 100.0
	TIME_CYCLE	= 2.0

	def	doTriangleTest
		0.0.step(1.0, 1/NUM_CYCLE) do |i|
			yield	i
			sleep(TIME_CYCLE / NUM_CYCLE / 4)
		end
		1.0.step(-1.0, -1.0/NUM_CYCLE) do |i|
			yield	i
			sleep(TIME_CYCLE / NUM_CYCLE / 4)
		end
		-1.0.step(0.0, 1.0/NUM_CYCLE) do |i|
			yield	i
			sleep(TIME_CYCLE / NUM_CYCLE / 4)
		end
	end
end
########################################

md	= MotorDriver.new("/dev/ttyUSB0", 57600);
test	= Test.new


md.rotateOpenloop(0)

max_millivolt	= 12000
max_rad_per_sec	= 6.28 * 60;

p	"openloop test will start"
test.doTriangleTest do |i|
	voltage	= (i * max_millivolt).to_i
	md.rotateOpenloop(voltage);
end
p	"openloop test ended"

p	"closeloop test will start"
test.doTriangleTest do |i|
	rad_per_sec	= (i * max_rad_per_sec).to_i
	md.rotateCloseloop(rad_per_sec);
end
p	"closeloop test ended"

p	"--test finished--"


rescue	Interrupt
	p	'excec Ctrl-C!'
	md.rotateOpenloop(0)
end
