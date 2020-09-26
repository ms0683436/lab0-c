
# Demonstration of queue testing framework
# Use help command to see list of commands and options
# Initial queue is NULL.
show
# Create empty queue
new
# Fill it with some values.  First at the head
ih dolphin
ih bear
ih gerbil
# Now at the tail
it meerkat
it bear
# Sort it
sort
# Reverse it
reverse
# Remove at the head
rh meerkat
# See how long it is
size
# Delete queue.  Goes back to a NULL queue.
free
# Exit program
quit
