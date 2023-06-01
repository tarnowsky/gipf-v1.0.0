RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
for filename in ./testy/*.in; do
    "./x64/Debug/$1.exe" < "$filename" > tmp
    output="${filename%.in}.out"
    index=$(echo "$filename" | awk -F/ '{print substr($NF, 1, length($NF)-3)}')
    if diff -B -b -w "./tmp" "$output" >/dev/null; then
        echo -e "${GREEN}test $index: \tpassed"
    else
        echo -e "${RED}test $index: \tfailed"
    fi
done

echo -e "${NC}"
rm tmp
