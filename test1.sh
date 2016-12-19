#./print 1

./consumer 0 &
./consumer 0 &
./consumer 0 &

./consumer 1 &
./consumer 1 &
./consumer 1 &

./consumer 2 &
./consumer 2 &
./consumer 2 &

./producer 0 1 &

./producer 1 1 &

./producer 2 1 &
#./producerS 1 0 &
