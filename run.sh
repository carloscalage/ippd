echo "Compiling $1"

/usr/local/opt/llvm/bin/clang -fopenmp -L/usr/local/opt/llvm/lib $1 -o $2

echo "Executing $2"

./$2 $3