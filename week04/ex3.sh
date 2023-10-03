gcc ex3.c -o ex3
./ex3 3 &
pstree -p $!
sleep 30
pstree -p $!
killall ex3

./ex3 5 &
pstree -p $!
sleep 60
pstree -p $!
killall ex3
