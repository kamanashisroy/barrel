
The doorlock is connected to gpio hackable pin 4
===================================================

And to activate the pin you can execute the following commands,
echo "4" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction
echo "1" > /sys/class/gpio/gpio4/value
echo "0" > /sys/class/gpio/gpio4/value
