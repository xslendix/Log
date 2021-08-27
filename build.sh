#!/bin/sh

echo "Compiling tests..."
rm -rf tests/out
mkdir -p tests/out

cd tests
for f in *.cpp; do
	echo "Compiling $f..."
	g++ -I../ "$f" -o "out/$(basename -- $f .cpp).test" --std=c++17 -lstdc++fs
done
cd ..

echo "Running tests"

prev="$(pwd)"

cd tests/out

for f in *.test; do
	echo "Running $f"
	mkdir -p "$(basename -- $f .test)"
	cd "$(basename -- $f .test)"
	../$f
	cd ..
done

cd "$prev"

