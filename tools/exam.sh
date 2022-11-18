for i in `seq 0 9`
do
cargo run --release --bin tester ../main < ./in/000$i.txt > out.txt
done
# for i in `seq 10 99`
# do
# cargo run --release --bin tester ../main < ./in/00$i.txt > out.txt
# done