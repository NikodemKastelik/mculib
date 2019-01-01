for file in *
do
    if [[ -d ${file} && "${file}" != "unity" ]]; then
        echo "============================"
        echo "Running ${file} test.."
        echo "============================"
        (cd $file && make)
        echo ""
    fi
done
