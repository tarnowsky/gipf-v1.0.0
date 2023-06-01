RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

exe_path=$(find . -name "$1.exe")
if [ -z "$exe_path" ]; then
    echo "Nie znaleziono pliku $1.exe"
    exit 1
fi

tests_path="./testy/*.in"
if [[ -n "$2" ]]; then
    tests_path=$(find . -type d -name "$2")
    if [ -z "$tests_path" ]; then
        echo "Nie znaleziono katalogu $2"
        exit 1
    fi
    tests_path=$tests_path"/*in"
fi

for filename in $tests_path; do
    "$exe_path" < "$filename" > tmp
    output="${filename%.in}.out"
    index=$(echo "$filename" | awk -F/ '{print substr($NF, 1, length($NF)-3)}')
    if diff -B -w "./tmp" "$output" >/dev/null; then
        echo -e "${GREEN}test $index: \tpassed"
    else
        echo -e "${RED}test $index: \tfailed"
    fi
done

echo -e "${NC}"
rm tmp
