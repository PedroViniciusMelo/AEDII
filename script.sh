for file in *.txt; do
    echo "$file"
    time ./bst < "$file"
    echo "================================================"
done
